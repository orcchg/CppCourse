#include <algorithm>
#include <ctime>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

std::default_random_engine generator;

template <typename T, size_t N = SIZE>
class Matrix;

/* Multiplication strategy */
// ----------------------------------------------------------------------------
template <typename T, size_t N>
class Strategy {
public:
  Strategy();
  virtual ~Strategy();

  virtual Matrix<T, N> multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) = 0;
};

template <typename T, size_t N>
Strategy<T, N>::Strategy() {
}

template <typename T, size_t N>
Strategy<T, N>::~Strategy() {
}

// ----------------------------------------------
template <typename T, size_t N>
class BruteForceStrategy : public Strategy<T, N> {
public:
  Matrix<T, N> multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) override final;
};

template <typename T, size_t N>
Matrix<T, N> BruteForceStrategy<T, N>::multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) {
  Matrix<T, N> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      result[i][j] = T();  // default value (zero for scalar type T)
      for (size_t k = 0; k < N; ++k) {
        result[i][j] += lhs[i][k] * rhs[k][j];
      }
    }
  }
  return result;
}

// ----------------------------------------------
template <typename T, size_t N>
class RecursiveStrategy : public Strategy<T, N> {
public:
  Matrix<T, N> multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) override final;

private:
  template <size_t K>
  Matrix<T, K> mul(const Matrix<T, K>& lhs, const Matrix<T, K>& rhs);
};

template <typename T, size_t N, size_t K>
struct MultiplyHelper;

template <typename T, size_t N>
struct MultiplyHelper<T, N, 1> {
  static Matrix<T, 1> mul(const Matrix<T, 1>& lhs, const Matrix<T, 1>& rhs);
};

template <typename T, size_t N>
Matrix<T, 1> MultiplyHelper<T, N, 1>::mul(const Matrix<T, 1>& lhs, const Matrix<T, 1>& rhs) {
  Matrix<T, 1> scalar;
  scalar[0][0] = lhs[0][0] * rhs[0][0];
  return scalar;
}

template <typename T, size_t N, size_t K>
struct MultiplyHelper {
  static Matrix<T, K> mul(const Matrix<T, K>& lhs, const Matrix<T, K>& rhs);
};

template <typename T, size_t N, size_t K>
Matrix<T, K> MultiplyHelper<T, N, K>::mul(const Matrix<T, K>& lhs, const Matrix<T, K>& rhs) {
  auto lhs_11 = lhs.template submatrix<K/2>(0, 0);
  auto lhs_12 = lhs.template submatrix<K/2>(0, K/2);
  auto lhs_21 = lhs.template submatrix<K/2>(K/2, 0);
  auto lhs_22 = lhs.template submatrix<K/2>(K/2, K/2);

  auto rhs_11 = rhs.template submatrix<K/2>(0, 0);
  auto rhs_12 = rhs.template submatrix<K/2>(0, K/2);
  auto rhs_21 = rhs.template submatrix<K/2>(K/2, 0);
  auto rhs_22 = rhs.template submatrix<K/2>(K/2, K/2);

  Matrix<T, K/2> block_ul = MultiplyHelper<T, N, K/2>::mul(lhs_11, rhs_11) + MultiplyHelper<T, N, K/2>::mul(lhs_12, rhs_21);
  Matrix<T, K/2> block_ur = MultiplyHelper<T, N, K/2>::mul(lhs_11, rhs_12) + MultiplyHelper<T, N, K/2>::mul(lhs_12, rhs_22);
  Matrix<T, K/2> block_ll = MultiplyHelper<T, N, K/2>::mul(lhs_21, rhs_11) + MultiplyHelper<T, N, K/2>::mul(lhs_22, rhs_21);
  Matrix<T, K/2> block_lr = MultiplyHelper<T, N, K/2>::mul(lhs_21, rhs_12) + MultiplyHelper<T, N, K/2>::mul(lhs_22, rhs_22);
  auto result = compound(block_ul, block_ur, block_ll, block_lr);
  return result;
}

template <typename T, size_t N>
Matrix<T, N> RecursiveStrategy<T, N>::multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) {
  return MultiplyHelper<T, N, N>::mul(lhs, rhs);
}

// ----------------------------------------------
template <typename T, size_t N>
class MultiThreadStrategy : public Strategy<T, N> {
public:
  MultiThreadStrategy();
  virtual ~MultiThreadStrategy();

  Matrix<T, N> multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) override final;

private:
  const Matrix<T, N>* m_lhs;
  const Matrix<T, N>* m_rhs;
  Matrix<T, N> m_output;

  void mul(size_t slice);
};

template <typename T, size_t N>
MultiThreadStrategy<T, N>::MultiThreadStrategy()
  : Strategy<T, N>()
  , m_lhs(nullptr)
  , m_rhs(nullptr)
  , m_output() {
}

template <typename T, size_t N>
MultiThreadStrategy<T, N>::~MultiThreadStrategy() {
  m_lhs = nullptr;
  m_rhs = nullptr;
}

template <typename T, size_t N>
Matrix<T, N> MultiThreadStrategy<T, N>::multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) {
  m_lhs = &lhs;
  m_rhs = &rhs;

  std::vector<std::thread> threads;
  for (size_t slice = 0; slice < THREADS; ++slice) {
    threads.push_back(std::thread([this, slice](){this->mul(slice);}));
  }
  for (auto& worker_thread : threads) {
    worker_thread.join();
  }
  return m_output;
}

template <typename T, size_t N>
void MultiThreadStrategy<T, N>::mul(size_t slice) {
  size_t from = slice * N / THREADS;
  size_t to = (slice + 1) * N / THREADS;
  size_t i, j, k;

  for (i = from; i < to; ++i) {
    for (j = 0; j < N; ++j) {
      m_output[i][j] = T();
      for (k = 0; k < N; ++k) {
        m_output[i][j] += (*m_lhs)[i][k] * (*m_rhs)[k][j];
      }
    }
  }
}

// ----------------------------------------------
// @see also: http://stackoverflow.com/questions/22634121/openmp-c-matrix-multiplication-run-slower-in-parallel

#ifdef _OPENMP
template <typename T, size_t N>
class OpenMPStrategy : public Strategy<T, N> {
public:
  Matrix<T, N> multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) override final;
};

template <typename T, size_t N>
Matrix<T, N> OpenMPStrategy<T, N>::multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) {
  Matrix<T, N> result;
  size_t i, j, k;
#pragma omp parallel for private (i, j, k) num_threads(THREADS)
  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      T sum = T();
      for (k = 0; k < N; ++k) {
        sum += lhs[i][k] * rhs[k][j];
      }
      result[i][j] = sum;
    }
  }
  return result;
}
#endif

// ----------------------------------------------
template <typename T, size_t N>
class TBBStrategy : public Strategy<T, N> {
public:
  Matrix<T, N> multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) override final;
};

template <typename T, size_t N>
Matrix<T, N> TBBStrategy<T, N>::multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs) {
  // TODO: implement matrix multiplication with strategy
  return Matrix<T, N>();
}

// ----------------------------------------------------------------------------
template <typename T, size_t N>
class StrategyFactory {
public:
  StrategyFactory();
  virtual ~StrategyFactory();
  Strategy<T, N>* create(const std::string& name);
  void release(Strategy<T, N>* const strategy);

private:
 std::unordered_map<std::string, Strategy<T, N>*> m_map;
};

template <typename T, size_t N>
StrategyFactory<T, N>::StrategyFactory() {
  m_map["brute-force"] = new BruteForceStrategy<T, N>();
  m_map["recursive"] = new RecursiveStrategy<T, N>();
  m_map["multi-thread"] = new MultiThreadStrategy<T, N>();
#ifdef _OPENMP
  m_map["openmp"] = new OpenMPStrategy<T, N>();
#endif
  m_map["tbb"] = new TBBStrategy<T, N>();
}

template <typename T, size_t N>
StrategyFactory<T, N>::~StrategyFactory() {
  m_map.clear();
}

template <typename T, size_t N>
Strategy<T, N>* StrategyFactory<T, N>::create(const std::string& name) {
  return m_map.at(name);  // throws std::out_of_range exception is case of missing 'name'
}

template <typename T, size_t N>
void StrategyFactory<T, N>::release(Strategy<T, N>* strategy) {
  if (strategy != nullptr) {
    delete strategy;
  }
  strategy = nullptr;
}

/* Matrix definition */
// ----------------------------------------------------------------------------
template <typename T, size_t N>
class Matrix {
public:
  static const size_t Size = N;
  
  static Matrix<T, N> identity(const T& value);  //!< Creates identity matrix
  static Matrix<T, N> createRandom(T low, T high);

  Matrix(const T& scalar = T());
  Matrix(const Matrix& obj);  // deep copy constructor
  Matrix& operator = (Matrix rhs);
  virtual ~Matrix();

  T* const operator[] (size_t row);
  const T* const operator[] (size_t row) const;
  bool operator == (const Matrix& rhs) const;
  bool operator != (const Matrix& rhs) const;
  Matrix operator + (const Matrix& rhs) const;
  Matrix operator * (const Matrix& rhs) const;

  void print(size_t size = 4) const;

  template <size_t K>
  Matrix<T, K> submatrix(size_t i, size_t j) const;

private:
  T** m_data;

  static Matrix multiply(const Matrix& lhs, const Matrix& rhs, Strategy<T, N>* const strategy);
  void swap(Matrix& lhs, Matrix& rhs);
};

template <typename T, size_t N>
Matrix<T, N>::Matrix(const T& scalar)
  : m_data(new T*[N]) {
  for (size_t i = 0; i < N; ++i) {
    m_data[i] = new T[N];
    for (size_t j = 0; j < N; ++j) {
      m_data[i][j] = scalar;
    }
  }
}

template <typename T, size_t N>
Matrix<T, N>::Matrix(const Matrix& obj)
  : m_data(new T*[N]) {
  for (size_t i = 0; i < N; ++i) {
    m_data[i] = new T[N];
    for (size_t j = 0; j < N; ++j) {
      m_data[i][j] = obj[i][j];
    }
  }
}

template <typename T, size_t N>
Matrix<T, N>& Matrix<T, N>::operator = (Matrix rhs) {
  swap(*this, rhs);
  return *this;
}

template <typename T, size_t N>
void Matrix<T, N>::swap(Matrix& lhs, Matrix& rhs) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      std::swap(lhs[i][j], rhs[i][j]);
    }
  }
}

template <typename T, size_t N>
Matrix<T, N>::~Matrix() {
  for (size_t i = 0; i < N; ++i) {
    delete [] m_data[i];
    m_data[i] = nullptr;
  }
  delete [] m_data;
  m_data = nullptr;
}

template <typename T, size_t N>
T* const Matrix<T, N>::operator[] (size_t row) {
  return m_data[row];
}

template <typename T, size_t N>
const T* const Matrix<T, N>::operator[] (size_t row) const {
  return m_data[row];
}

template <typename T, size_t N>
Matrix<T, N> Matrix<T, N>::identity(const T& value) {
  Matrix<T, N> matrix;
  for (size_t i = 0; i < N; ++i) {
    matrix[i][i] = static_cast<T>(value);
  }
  return matrix;
}

template <typename T, size_t N>
Matrix<T, N> Matrix<T, N>::createRandom(T low, T high) {
  std::uniform_real_distribution<T> distribution(low, high);
  
  Matrix<T, N> matrix;
  for (size_t row = 0; row < N; ++row) {
    for (size_t col = 0; col < N; ++col) {
      matrix[row][col] = distribution(generator);
    }
  }
  return matrix;
}

template <typename T>
bool equal(const T& lhs, const T& rhs) {
  std::equal_to<T> e;
  return e(lhs, rhs);
}

template <>
bool equal<double>(const double& lhs, const double& rhs) {
  return std::fabs(lhs - rhs) < 0.000001;
}

template <>
bool equal<float>(const float& lhs, const float& rhs) {
  return std::fabs(lhs - rhs) < 0.0001f;
}

template <typename T, size_t N>
bool Matrix<T, N>::operator == (const Matrix& rhs) const {
  for (size_t row = 0; row < N; ++row) {
    for (size_t col = 0; col < N; ++col) {
      if (!equal((*this)[row][col], rhs[row][col])) {
        return false;
      }
    }
  }
  return true;
}

template <typename T, size_t N>
bool Matrix<T, N>::operator != (const Matrix& rhs) const {
  return !(*this == rhs);
}

template <typename T, size_t N>
Matrix<T, N> Matrix<T, N>::operator + (const Matrix<T, N>& rhs) const {
  Matrix<T, N> result;
  for (size_t row = 0; row < N; ++row) {
    for (size_t col = 0; col < N; ++col) {
      result[row][col] = (*this)[row][col] + rhs[row][col];
    }
  }
  return result;
}

// ----------------------------------------------
template <typename T, size_t N>
void Matrix<T, N>::print(size_t size) const {
  size = size > N ? N : size;
  for (size_t row = 0; row < size; ++row) {
    for (size_t col = 0; col < size; ++col) {
      printf("%.4lf ", static_cast<double>(m_data[row][col]));
    }
    printf("\n");
  }
  printf("\n");
}

// ----------------------------------------------
template <typename T, size_t N>
template <size_t K>
Matrix<T, K> Matrix<T, N>::submatrix(size_t i, size_t j) const {
  if (i < 0 || j < 0 || i > N || j > N || i + K > N || j + K > N) {
    printf("Cannot create submatrix of size %lu. Indices %lu %lu out of bounds.", K, i, j);
    throw;
  }
  // TODO: avoid copy
  Matrix<T, K> matrix;
  for (size_t row = 0; row < K; ++row) {
    for (size_t col = 0; col < K; ++col) {
      matrix[row][col] = (*this)[row + i][col + j];
    }
  }
  return matrix;
}

template <typename T, size_t K>
Matrix<T, 2 * K> compound(const Matrix<T, K>& ul, const Matrix<T, K>& ur, const Matrix<T, K>& ll, const Matrix<T, K>&lr) {
  Matrix<T, 2 * K> result;
  for (size_t i = 0; i < K; ++i) {
    for (size_t j = 0; j < K; ++j) {
      result[i][j] = ul[i][j];
    }
  }
  for (size_t i = 0; i < K; ++i) {
    for (size_t j = 0; j < K; ++j) {
      result[i][j + K] = ur[i][j];
    }
  }
  for (size_t i = 0; i < K; ++i) {
    for (size_t j = 0; j < K; ++j) {
      result[i + K][j] = ll[i][j];
    }
  }
  for (size_t i = 0; i < K; ++i) {
    for (size_t j = 0; j < K; ++j) {
      result[i + K][j + K] = lr[i][j];
    }
  }
  return result;
}

/* Multiplication */
// ----------------------------------------------------------------------------
Strategy<double, SIZE>* g_Strategy = nullptr;  // global variable

template <typename T, size_t N>
Matrix<T, N> Matrix<T, N>::operator * (const Matrix<T, N>& rhs) const {
  return multiply(*this, rhs, g_Strategy);
}

template <typename T, size_t N>
Matrix<T, N> Matrix<T, N>::multiply(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs, Strategy<T, N>* const strategy) {
  if (strategy == nullptr) {
    printf("Error: strategy not specified!");
    throw;
  }
  return strategy->multiply(lhs, rhs);
}

/* Main */
// ---------------------------------------
// Compile: g++ -std=c++11 -fopenmp -DSIZE=128 -DTHREADS=2 -DRECURSIVE=true -DTBB=true matmul.cpp -o matmul
// Run: ./matmul

int main(int argc, char** argv) {
  clock_t start = clock();
  clock_t elapsed = start;

  auto A = Matrix<double>::createRandom(0.0, 1.0);
  auto B = Matrix<double>::createRandom(0.0, 1.0);
  A.print();  printf("\n");
  B.print();  printf("\n");

  // setting multiplication Strategy
  StrategyFactory<double, Matrix<double>::Size> factory;

  //---------------------------------------------
  g_Strategy = factory.create("brute-force");
  start = clock();
  auto C = A * B;
  elapsed = clock() - start;
  printf("Brute-Force strategy, time elapsed: %lf\n", static_cast<double>(elapsed) / CLOCKS_PER_SEC);
  C.print();  printf("\n");
  factory.release(g_Strategy);

  //---------------------------------------------
#if RECURSIVE
  g_Strategy = factory.create("recursive");
  start = clock();
  auto D = A * B;
  elapsed = clock() - start;
  printf("Recursive strategy, time elapsed: %lf\n", static_cast<double>(elapsed) / CLOCKS_PER_SEC);
  D.print();
  if (C != D) {
    printf("ERROR!!! Recursive\n");
  }
  printf("\n");
  factory.release(g_Strategy);
#endif

  //---------------------------------------------
  g_Strategy = factory.create("multi-thread");
  start = clock();
  auto F = A * B;
  elapsed = clock() - start;
  printf("Multithread strategy [%i threads], time elapsed: %lf\n", THREADS, static_cast<double>(elapsed) / CLOCKS_PER_SEC);
  F.print();
  if (C != F) {
    printf("ERROR!!! Multithread\n");
  }
  printf("\n");
  factory.release(g_Strategy);

  //---------------------------------------------
#ifdef _OPENMP
  g_Strategy = factory.create("openmp");
  start = clock();
  auto G = A * B;
  elapsed = clock() - start;
  printf("OpenMP strategy [%i threads], time elapsed: %lf\n", THREADS, static_cast<double>(elapsed) / CLOCKS_PER_SEC);
  G.print();
  if (C != G) {
    printf("ERROR!!! OpenMP\n");
  }
  printf("\n");
  factory.release(g_Strategy);
#endif

  //---------------------------------------------
#if TBB
  g_Strategy = factory.create("tbb");
  start = clock();
  auto H = A * B;
  elapsed = clock() - start;
  printf("Intel TBB strategy [%i threads], time elapsed: %lf\n", THREADS, static_cast<double>(elapsed) / CLOCKS_PER_SEC);
  H.print();
  if (C != H) {
    printf("ERROR!!! TBB\n");
  }
  printf("\n");
  factory.release(g_Strategy);
#endif

  return 0;
}

