/*
 * author: yuandx
 * create: 2015-06-18
 * email: yuandx@mvad.com
 */
#ifndef PUBLIC_COMMON_H_
#define PUBLIC_COMMON_H_
#include <pthread.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <stdint.h>

namespace micro_ad
{
namespace utils
{

class MutexGuard
{
public:
  explicit MutexGuard(pthread_mutex_t *mutex) : mu_(mutex)
  {
    pthread_mutex_lock(mu_);
  }
  ~MutexGuard()
  {
    pthread_mutex_unlock(mu_);
  }
private:
  // No copying allowed
  MutexGuard(const MutexGuard&);
  void operator=(const MutexGuard&);
  pthread_mutex_t *const mu_;
};

class ScopeSpinlock
{
public:
  ScopeSpinlock(pthread_spinlock_t * lock)
  {
    lock_ = lock;
    pthread_spin_lock(lock_);
  }

  ~ScopeSpinlock()
  {
    pthread_spin_unlock(lock_);
  }

private:
  pthread_spinlock_t * lock_;
};

class ScopeRwlock
{
public:
  ScopeRwlock(pthread_rwlock_t * lock, bool is_readlock)
  {
    lock_ = lock;
    if (is_readlock)
    {
      pthread_rwlock_rdlock(lock_);
    }
    else
    {
      pthread_rwlock_wrlock(lock_);
    }
  }

  ~ScopeRwlock()
  {
    pthread_rwlock_unlock(lock_);
  }

private:
  pthread_rwlock_t * lock_;
};


/*
 * string utils
 * to Lower/Upper, split/join by string,
 */


inline std::string ToLower(const std::string& str)
{
  std::string ret(str);
  std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
  return ret;
}

inline std::string ToUpper(const std::string& str)
{
  std::string ret(str);
  std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
  return ret;
}

inline std::string Join(const std::vector<std::string>& strs, const std::string& sep)
{
  std::string ret;
  if(strs.size() < 1)
  {
    return ret;
  }
  ret.append(strs[0]);
  for(std::size_t i = 1; i != strs.size(); i++)
  {
    ret.append(sep);
    ret.append(strs[i]);
  }
  return ret;
}

inline std::vector<std::string> Split(const std::string& s, const std::string& delim)
{
  std::vector<std::string> ret;
  std::size_t start = 0, next = 0;
  do
  {
    next = s.find_first_of(delim, start);
    ret.push_back(s.substr(start, next - start));
    start = next + 1;
  } while (next != std::string::npos);
  return ret;
}

inline bool StartWith(const std::string& l, const std::string& r)
{
  return l.compare(0, r.size(), r) == 0;
}

class Random
{
public:
  Random();
  Random(unsigned int seed);
  int Next();

private:
  unsigned int seed_;
};

inline Random::Random():
  seed_(0)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  seed_ = static_cast<unsigned int>(tv.tv_sec ^ tv.tv_usec);
}
inline Random::Random(unsigned int seed):
  seed_(seed)
{
}
inline int Random::Next()
{
  return rand_r(&seed_);
}

inline int64_t CurrentUSeconds()
{
  struct timeval cur;
  gettimeofday(&cur, NULL);
  return cur.tv_sec *1000000 + cur.tv_usec;
}

template <typename Iterator>
void LockFreeShuffle(Iterator begin, Iterator end)
{
  Random rand_;
  for (std::ptrdiff_t size = end - begin; size != 0; size--)
  {
    std::swap(*(begin + size - 1), *(begin + rand_.Next() % size));
  }
}

void ReplaceAll(std::string& str, const std::string& from, const std::string& to)
{
  if (from.empty())
  {
    return ;
  }
  size_t pos = 0;
  for (pos = str.find(from, pos); pos != std::string::npos; pos = str.find(from, pos))
  {
    str.replace(pos, from.size(), to);
    pos += to.size();
  }
}

template <typename int_type>
void SortUniqVector(std::vector<int_type>& vec)
{
  if (vec.size() == 0u)
  {
    return ;
  }
  sort(vec.begin(), vec.end());
  int insert_pos = 1;
  for (size_t i = 1; i < vec.size(); i++)
  {
    if ( vec[i-1] != vec[i] )
    {
      vec[insert_pos++] = vec[i];
    }
  }
  vec.resize(insert_pos);
}

template<typename T, typename Iter>
static void SplitBySign(Iter beg , Iter end, std::vector<T>& positive, std::vector<T>& negative)
{
  for (; beg != end; ++beg)
  {
    T val = *beg;
    std::vector<T>& dest = val > static_cast<T>(0) ? positive : negative;
    dest.push_back(*beg);
  }
}

template <typename T>
inline static std::string Number2Bit(T data)
{
  std::string result;
  int bit_num = sizeof(T) * 8;
  do
  {
    result.push_back( (data & 1 ? '1' : '0') );
    data >>= 1;
    --bit_num;
  } while (bit_num > 0 && data != 0);
  std::reverse(result.begin(), result.end());
  return result;
}

class Singleton
{
  static Singleton* Instance()
  {
    if (NULL == instance)
    {
      MutexGuard mg(&lock);
      if (NULL == instance)
      {
        instance = new Singleton();
      }
    }
    return instance;
  }
private:
  Singleton()
  {}
  ~Singleton()
  {}
  Singleton(const Singleton&)
  {}
  Singleton(Singleton&&)
  {}
  static Singleton* instance;
  static pthread_mutex_t lock;
};
Singleton* Singleton::instance = NULL;
pthread_mutex_t Singleton::lock = PTHREAD_MUTEX_INITIALIZER;
}
}
#endif // PUBLIC_COMMON_H_
