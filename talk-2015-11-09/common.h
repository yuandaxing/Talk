/*
 * author: yuandx
 * create: 2015-11-09
 * email: yuandx@mvad.com
 */

#ifndef DEMO_COMMON_H_
#define DEMO_COMMON_H_

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <set>
#include <iostream>
#include <sys/time.h>

using std::binary_search;
using std::vector;
using std::set;
using std::endl;
using std::cout;

inline bool BinarySearch(const vector<int>& lists, const int v, int start, int& lower_bound)
{
  int left = start, right = static_cast<int>(lists.size()); //[left, right), lower bound algorithm
  while (left < right - 1)
  {
    int mid = (right + left) >> 1;
    if (lists[mid] <= v)
    {
      left = mid;
    }
    else
    {
      right = mid;
    }
  }
  lower_bound = left;
  return left >= 0 && lists[left] == v;
}

class Random
{
public:
  Random(): seed_(0)
  {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    seed_ = static_cast<unsigned int>(tv.tv_sec ^ tv.tv_usec);
  }
  Random(unsigned int seed):  seed_(seed)
  {
  }
  int Next()
  {
    return rand_r(&seed_);
  }
private:
  unsigned int seed_;
};

inline void GenVector(vector<int>& result, int size, int max)
{
  Random rand;
  for(int i = 0; i < size; i++)
  {
    result.push_back(rand.Next() % max);
  }
}
inline void GenSet(set<int>& result, int size, int max)
{
  Random rand;
  size_t expect = static_cast<size_t>(size);
  while (result.size() < expect)
  {
    result.insert(rand.Next() % max);
  }
}

inline int64_t CurrentUSeconds()
{
  struct timeval cur;
  gettimeofday(&cur, NULL);
  return cur.tv_sec *1000000 + cur.tv_usec;
}

inline void BinaryIntersect(const vector<int>& small, const vector<int>& large, vector<int>& result)
{
  int occur = 0;
  int i = 0, j = -1;
  int size1 = static_cast<int>(small.size()), size2 = static_cast<int>(large.size());
  result.reserve(small.size());

  while (i < size1 && j < size2)
  {
    if (BinarySearch(large, small[i], j, occur))
    {
      result.push_back(small[i]);
    }
    j = occur + 1;

    if (j < size2 && BinarySearch(small, large[j], i, occur))
    {
      result.push_back(large[j]);
    }
    i = occur + 1;
  }
}
void NormalIntersect(vector<int>& vec1, vector<int>& vec2, vector<int>& result)
{
  for (vector<int>::iterator it1 = vec1.begin(), it2 = vec2.begin();
       it1 != vec1.end() && it2 != vec2.end();)
  {
    if (*it1 < *it2)
    {
      ++it1;
    } else if (*it1 > *it2)
    {
      ++it2;
    } else
    {
      result.push_back(*it1);
      ++it1;
      ++it2;
    }
  }
}

#endif // DEMO_COMMON_H_
