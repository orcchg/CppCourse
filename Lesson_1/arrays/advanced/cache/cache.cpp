#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>
#include "logger.h"

#define SIZE 32  // in bytes
#define NUM_BANKS 4  // number of banks
#define BANK_SIZE 128  // number of chunks in bank

#define PAGE_SIZE 4096  // in bytes
#define NUM_PAGES 128  // total pages in memory

#define HEAD_SIZE 72  // total bytes to be printed
#define OBJECT_SIZE 28697  // Size of Object instance in bytes

#define LONG_OPERATION_SECONDS 1  // time in seconds

/* Memory organization */
// ----------------------------------------------------------------------------
/// @brief Memory is organized as a set of fixed-size pages.
struct Page {
  bool is_empty = true;
  int start_address;
  char data[PAGE_SIZE];
};

struct PageBlock {
  int size;
  Page** pages;
};

/* Cache structures */
// ----------------------------------------------------------------------------
/// @brief Chunk is a fixed-size memory cell in cache.
struct Chunk {
  char data[SIZE];
};

/// @brief Bank is an array of chunks.
struct Bank {
  int start_address;
  Chunk chunks[BANK_SIZE];
};

/* Cache */
// ----------------------------------------------------------------------------
class Cache {
public:
  /// @brief Constructor - initializes cache.
  Cache();

  void pushPage(Page* page);  //!< Push single memory page into cache.

  /// @brief Get page from cache by an address within it.
  /// @param address Address in memory the page contains.
  /// @return Page or nullptr in case of cache miss.
  Page* getPage(int address);

private:
  int m_bank_offset;
  int m_pages_allocated_offset;
  Bank m_banks[NUM_BANKS];
  Page* m_pages_allocated[NUM_BANKS];

  void fill(Page* page);  //!< Fills bank at offset with page data.
  Page* allocatePage();
};

Cache::Cache()
  : m_bank_offset(0)
  , m_pages_allocated_offset(0) {
  for (int i = 0; i < NUM_BANKS; ++i) {
    m_banks[i].start_address = -1;
    m_pages_allocated[i] = nullptr;
  }
}

void Cache::pushPage(Page* page) {
  m_bank_offset = m_bank_offset < NUM_BANKS ? m_bank_offset : 0;
  fill(page);
}

Page* Cache::getPage(int address) {
  if (address < 0) {
    ERR("Access violation at address %i: Cache error", address);
    return nullptr;
  }

  for (int i = 0; i < NUM_BANKS; ++i) {
    Bank& bank = m_banks[i];
    if (bank.start_address <= address && bank.start_address + SIZE * BANK_SIZE > address) {
      INF("Cache hit at address %i: on page starting from: %i", address, bank.start_address);
      Page* page = allocatePage();
      page->start_address = bank.start_address;

      for (int j = 0; j < BANK_SIZE; ++j) {
        Chunk& chunk = bank.chunks[j];
        memmove(&page->data[j * SIZE], chunk.data, SIZE);
      }
      return page;
    }
  }

  WRN("Cache miss: no such page for address %i", address);
  return nullptr;
}

void Cache::fill(Page* page) {
  Bank& bank = m_banks[m_bank_offset];
  bank.start_address = page->start_address;
  for (int i = 0; i < BANK_SIZE; ++i) {
    Chunk& chunk = bank.chunks[i];
    memmove(chunk.data, &page->data[i * SIZE], SIZE);
  }
  DBG("Pushed page [%i] to cache into bank %i", page->start_address, m_bank_offset);
  ++m_bank_offset;
}

Page* Cache::allocatePage() {
  m_pages_allocated_offset = m_pages_allocated_offset < NUM_BANKS ? m_pages_allocated_offset : 0;

  if (m_pages_allocated[m_pages_allocated_offset] != nullptr) {  // free old pages
    delete m_pages_allocated[m_pages_allocated_offset];
    m_pages_allocated[m_pages_allocated_offset] = nullptr;
  }

  Page* page = new Page();
  m_pages_allocated[m_pages_allocated_offset] = page;
  ++m_pages_allocated_offset;
  return page;
}

/* Memory */
// ----------------------------------------------------------------------------
class MemoryAllocator;

/// @class MemoryManager
/// @brief This class manages memory pages access.
class MemoryManager {
  friend class MemoryAllocator;
public:
  /// @brief Constructor - initializes memory manager.
  MemoryManager();

  /// @brief Get a page containing specified address.
  /// @param address Address in memory.
  /// @return Page containing the address of nullptr in case
  /// of fault address.
  /// @note This operation tries to get page from cache first,
  /// then accesses it directly in case of cache miss.
  Page* getPage(int address);

  /// @brief Maps content into memory.
  /// @param data Data to be mapped into pages in memory.
  /// @param size Size of data in bytes.
  /// @param pages Allocated pages block.
  /// @return Pointer to a page mapped data starts from.
  /// @note Pages block should be previously allocated before
  /// this call. If size in bytes of data is larger than size of
  /// allocated block, an error will occur.
  Page* mapToMemory(char* data, int size, PageBlock* pages);

  void defragmentation();  //!< Performs memory defragmentation.

private:
  constexpr static int npos = -1;

  Page m_pages[NUM_PAGES];
  Cache m_cache;

  /// @brief Find continuous block of pages large enough to
  /// contain {@link number_pages} pages.
  /// @param number_pages Number of pages to find a block for.
  /// @return Index of page the block starts from or ::npos if no
  /// such block found.
  int findFreeBlock(int number_pages);

  void longOperation();  //!< Imitates long memory access operation.

  Page* getPageDirectly(int address);  //!< Directly get page from memory.
};

MemoryManager::MemoryManager()
  : m_cache() {
  for (int i = 0; i < NUM_PAGES; ++i) {
    m_pages[i].is_empty = true;
    m_pages[i].start_address = i * PAGE_SIZE;
  }
}

Page* MemoryManager::getPage(int address) {
  if (address < 0 || address >= PAGE_SIZE * NUM_PAGES) {
    ERR("Access violation at address %i: Page fault", address);
    return nullptr;
  }

  Page* page = m_cache.getPage(address);
  if (page == nullptr) {  // cache miss
    page = getPageDirectly(address);
    m_cache.pushPage(page);  // cache new page
  }
  return page;
}

Page* MemoryManager::mapToMemory(char* data, int size, PageBlock* pages) {
  if (pages == nullptr || data == nullptr || size < 0 || size > pages->size * PAGE_SIZE) {
    ERR("Unable to map data into memory");
    return nullptr;
  }

  int number_pages = size / PAGE_SIZE;
  int tail = size % PAGE_SIZE;
  number_pages += tail > 0 ? 1 : 0;

  for (int i = 0; i + 1 < number_pages; ++i) {
    memmove(pages->pages[i]->data, &data[i * PAGE_SIZE], PAGE_SIZE);
  }
  if (tail > 0) {
    memmove(pages->pages[number_pages - 1]->data, &data[PAGE_SIZE * (number_pages - 1)], tail);
  }
  return pages->pages[0];
}

void MemoryManager::defragmentation() {
  ERR("Operation not supported!");
}

void MemoryManager::longOperation() {
  WRN("Accessing memory directly...");
  std::this_thread::sleep_for(std::chrono::seconds(LONG_OPERATION_SECONDS));
  WRN("Accessing memory directly... finished");
}

Page* MemoryManager::getPageDirectly(int address) {
  longOperation();  // long accessing memory...
  int page_index = address / PAGE_SIZE;
  return &m_pages[page_index];
}

int MemoryManager::findFreeBlock(int number_pages) {
  DBG("Requested a free block for %i pages", number_pages);
  for (int i = 0; i < NUM_PAGES; ++i) {
    Page& page = m_pages[i];
    int shift = 0;
    while (page.is_empty && shift < number_pages) {
      ++shift;
      page = m_pages[i + shift];
    }
    if (shift + 1 >= number_pages) {  // there is free block large enough
      return i;
    }
    i += shift;
  }
  return npos;  // no free block for 'number_pages' pages
}

// ----------------------------------------------
/// @class MemoryAllocator
/// @brief Allocates memory in pages of size required.
class MemoryAllocator {
public:
  /// @brief Constructor - initializes memory allocator.
  /// @param manager Reference to a memory manager.
  MemoryAllocator(MemoryManager& manager);

  /// @brief Allocates memory in pages which is enough to contain
  /// specified amount of bytes.
  /// @param size Size in bytes to allocate.
  /// @return Pointer to pages the allocated block covers.
  /// @note Returs nullptr in case of not enough memory left.
  PageBlock* allocate(int size);

  void free(PageBlock* pages);  //!< Free previously allocated memory.

  MemoryManager& getManager();  //!< Get reference to manager.

private:
  MemoryManager& m_manager;
};

MemoryAllocator::MemoryAllocator(MemoryManager& manager)
  : m_manager(manager) {
}

PageBlock* MemoryAllocator::allocate(int size) {
  DBG("Allocating %i bytes...", size);
  if (size <= 0 || size >= PAGE_SIZE * NUM_PAGES) {
    ERR("Unable to allocate %i bytes", size);
    return nullptr;
  }
  int number_pages = size / PAGE_SIZE;
  number_pages += size % PAGE_SIZE > 0 ? 1 : 0;

  int shift = m_manager.findFreeBlock(number_pages);
  if (shift == MemoryManager::npos) {
    ERR("Out of memory error");
    return nullptr;
  }

  PageBlock* pages = new PageBlock();
  pages->size = number_pages;
  pages->pages = new Page*[number_pages];

  for (int i = 0; i < number_pages; ++i) {
    Page& page = m_manager.m_pages[shift + i];
    page.is_empty = false;
    pages->pages[i] = &page;
  }
  DBG("Allocated %i pages total for %i bytes", number_pages, size);
  return pages;
}

void MemoryAllocator::free(PageBlock* pages) {
  if (pages == nullptr) {
    DBG("Nothing to free");
    return;
  }

  int size = pages->size;
  for (int i = 0; i < size; ++i) {
    pages->pages[i]->is_empty = true;
  }

  delete [] pages->pages;  pages->pages = nullptr;
  delete pages;  pages = nullptr;
  DBG("Total pages released: %i", size);
}

MemoryManager& MemoryAllocator::getManager() {
  return m_manager;
}

/* Utility */
// ----------------------------------------------------------------------------
void printPage(Page* page) {
  if (page == nullptr) {
    WRN("Page is null");
    return;
  }

  char head[HEAD_SIZE];
  memmove(head, page->data, HEAD_SIZE);
  printf("Page[%i]: %s\n", page->start_address, head);
}

std::chrono::steady_clock::time_point timer;

void startTimer() {
  timer = std::chrono::steady_clock::now();
}

void time() {
  std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();
  std::chrono::duration<double> span = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed - timer);
  DBG("Timer: %lf", span.count());
  startTimer();
}

/* Custom object */
// ---------------------------------------------------------------------------
struct Object {
  char data[OBJECT_SIZE];

  Object();
};

Object::Object() {
  char size[6];
  sprintf(size, "%i", OBJECT_SIZE);
  for (int i = 0; i < 6; ++i) {
    size[i] = size[i] == 0 ? ' ' : size[i];
  }

  data[0] = 'O';  data[1] = 'b';  data[2] = 'j';  data[3] = 'e';  data[4] = 'c';  data[5] = 't';
  data[6] = ' ';  data[7] = ' ';  data[8] = 's';  data[9] = 'i';  data[10] = 'z';  data[11] = 'e';
  data[12] = ' ';  data[13] = '=';  data[14] = ' ';  data[15] = size[0];  data[16] = size[1];
  data[17] = size[2];  data[18] = size[3];  data[19] = size[4];  data[20] = size[5];  data[21] = ' ';

  for (int i = 22; i < OBJECT_SIZE; ++i) {
    data[i] = static_cast<char>(rand() % 26 + 'a');
  }
}

Object* allocateObject(MemoryAllocator& allocator) {
  Object object;
  PageBlock* pages = allocator.allocate(OBJECT_SIZE);
  MemoryManager& manager = allocator.getManager();
  manager.mapToMemory(object.data, OBJECT_SIZE, pages);
  return reinterpret_cast<Object*>(pages);
}

void freeObject(MemoryAllocator& allocator, Object* object) {
  PageBlock* pages = reinterpret_cast<PageBlock*>(object);
  allocator.free(pages);
  object = nullptr;
}

void printObject(Object* object) {
  if (object == nullptr) {
    return;
  }
  PageBlock* pages = reinterpret_cast<PageBlock*>(object);
  for (int i = 0; i < pages->size; ++i) {
    printPage(pages->pages[i]);
  }
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 1]: Arrays : Cache 1");

  MemoryManager manager;
  MemoryAllocator allocator(manager);

  startTimer();
  Page* page_1 = manager.getPage(8096);    time();
  Page* page_11 = manager.getPage(10144);  time();
  Page* page_2 = manager.getPage(14160);   time();
  Page* page_21 = manager.getPage(16144);  time();
  Page* page_3 = manager.getPage(25785);   time();
  Page* page_22 = manager.getPage(17100);  time();
  Page* page_23 = manager.getPage(12388);  time();
  Page* page_31 = manager.getPage(24676);  time();

  //PageBlock* pages_64 = allocator.allocate(65536);  // 64 kB
  //PgeBlock* pages_32 = allocator.allocate(32768);  // 32 kB
  //PageBlock* pages_16 = allocator.allocate(16384);  // 16 kB

  Object* object_1 = allocateObject(allocator);
  printObject(object_1);
  freeObject(allocator, object_1);

  //allocator.free(pages_64);
  //allocator.free(pages_32);
  //allocator.free(pages_16);

  DBG("[Lesson 1]: Arrays : Cache 1 [END]");
  return 0;
}

