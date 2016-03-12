#include <algorithm>
#include <fstream>
#include <iostream>
#include <functional>  // plus
#include <mutex>
#include <numeric>  // accumulate
#include <iterator>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <cstdio>
#include "logger.h"

#define NUM_THREADS 2

/* Storage */
// ----------------------------------------------------------------------------
class Storage {
public:
  Storage();
  static std::string emptyString;

  size_t size() const;
  bool empty() const;
  const std::string top();  // Quiz: why don't we return by reference ?
  void enqueue(const std::string& word);
  void dequeue();

  bool isUnderflow() const;
  void underflow();

private:
  bool is_underflow;
  std::queue<std::string> words;

public:
  std::mutex mutex;
};

std::string Storage::emptyString = "";

Storage::Storage()
  : is_underflow(false) {
}

size_t Storage::size() const {
  return words.size();
}

bool Storage::empty() const {
  return words.empty();
}

const std::string Storage::top() {
  if (empty()) {
    return emptyString;
  }
  return words.front();
}

void Storage::enqueue(const std::string& word) {
  words.push(word);
}

void Storage::dequeue() {
  if (empty()) {
    return;
  }
  words.pop();
}

bool Storage::isUnderflow() const {
  return is_underflow;
}

void Storage::underflow() {
  is_underflow = true;
}

/* Hash */
// ----------------------------------------------------------------------------
int64_t hash(const std::string& str) {
  // Java String hash code: s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
  int prime = 7;
  int64_t hash = 0;
  int power = str.length() - 1;

  for (auto it = str.begin(); it != str.end(); ++it, --power) {
    hash += static_cast<int64_t>(*it) * std::pow(prime, power);
  }
  return hash;
}

/* Worker thread */
// ----------------------------------------------------------------------------
void process(Storage& storage, int id, int64_t* sum, int* count) {
  while (!storage.isUnderflow() || !storage.empty()) {
    while (storage.empty()) {
      // active waiting
      std::this_thread::yield();
    }
    {
      std::lock_guard<std::mutex> lock(storage.mutex);
      const std::string word = storage.top();
      if (!word.empty()) {
        int64_t value = hash(word);
        *sum += value;
        *count += 1;
        printf("Thread [%i] is working... Word = %s, hash = %li, sum = %li, processed = %i\n", id, word.c_str(), value, *sum, *count);
        storage.dequeue();
        std::this_thread::yield();
      }
    }
  }
  INF("Thread [%i] exits", id);
}

/* Main */
/**
 * Concurrent reading words from file. Storage collection is not thread-safe.
 *
 * Also, to learn why std::ref(), see the following link:
 * http://stackoverflow.com/questions/28950835/c-error-no-type-named-type-in-class-stdresult-ofvoid-stdunordered
 */
// ----------------------------------------------------------------------------
int main(int args, char** argv) {
  DBG("[Lesson 12]: Mutex 2.2");

  // make storage
  Storage storage;
  int64_t values[NUM_THREADS];
  int words_count[NUM_THREADS];
  int64_t checksum = 0;

  // run threads
  std::vector<std::thread> threads;
  threads.reserve(NUM_THREADS);
  for (int i = 0; i < NUM_THREADS; ++i) {
    values[i] = 0;
    words_count[i] = 0;
    threads.emplace_back(process, std::ref(storage), i, &values[i], &words_count[i]);
  }

  // open and read file
  std::fstream fin;
  fin.open("../threads/lorem.txt", std::fstream::in);

  int counter = 0;
  std::string word;
  while (fin >> word) {
    storage.enqueue(word);
    ++counter;
  }
  DBG("Total words: %i", counter);

  // close file
  fin.close();

  // send stop signals
  storage.underflow();

  // wait for threads
  for (int i = 0; i < NUM_THREADS; ++i) {
    threads[i].join();
  }

  // summary
  for (int i = 0; i < NUM_THREADS; ++i) {
    DBG("Thread [%i]: sum = %li, processed = %i", i, values[i], words_count[i]);
  }

  // accumulate result
  checksum = std::accumulate(values,  values + NUM_THREADS, checksum, std::plus<int64_t>());
  WRN("Checksum: %li", checksum);

  DBG("[Lesson 12]: Mutex 2.2 END");
  return 0;
}

