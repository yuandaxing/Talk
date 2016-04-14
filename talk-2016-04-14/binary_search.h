/*
 * author: yuandx
 * create: 2016-04-04
 * email: yuandx@mvad.com
 */

#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_
#include <vector>
using std::vector;
/*
  result is the index of  lower bound (-8, v]
 */
/*
 * (left, right), left == right - 1
 * left == right - 2, true
 * left = right - 3, 2, 1
 *
 */
template <typename value_type >
bool LowerBound1(const vector<value_type>& lists, const value_type& v, int i, int& result)
{
  int left = i, right = static_cast<int>(lists.size()); //[left, right), lower bound algorithm
  while (left < right - 1)
  {
    int mid = (right + left) >> 1;
    if (lists[mid] < v)
    {
      left = mid;
    }
    else
    {
      right = mid;
    }
  }
  result = right;
  return static_cast<std::size_t>(right) <
    lists.size() && lists[right] == v;
}

template <typename value_type >
void UpperBound1(const vector<value_type>& lists,
            const value_type& v, int i, int& result)
{
  int left = i, right = static_cast<int>(lists.size()); //[left, right), lower bound algorithm
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
  result = right;
}


/*
 * if  v in lists
 * before the left <= right v must be in [left, right]
 * v must be return from lists[mid]
 *
 * update left < right, left = mid cause loop forever
 *
 *
 */

template <typename value_type >
bool BadBS(const vector<value_type>& lists, const value_type& v, int i, int& result)
{
  int left = i, right = static_cast<int>(lists.size() - 1); //[left, right), lower bound algorithm
  while (left <= right)
  {
    int mid = (right + left) >> 1;
    if (lists[mid] == v)
    {
      result = mid;
      return true;
    }
    else if (lists[mid] < v)
    {
      left = mid + 1; //left = mid
    }
    else
    {
      right = mid - 1; // right = mid
    }
  }
  return false;
}

/*
 *
 * loop invariant:
 * 1. [-1, left-1] < v [right+1, size] >= v
 * assert while exit:
 *  left=right+1
 * size = 0, true, left == right+1
 * size = 1, true, left == right, size = 0
 * size = 2, left == right - 1, size = 0, size = 1
 * size = 3, left == right - 2, size = 1
 *
 * left [0, size], right [-1, size-1]
 */
/*
 * if left < right, error for size = 1
 * if lists[mid] == v, two compare, low effeciency
 *
 */

template <typename value_type >
bool LowerBound(const vector<value_type>& lists, const value_type& v, int i, int& result)
{
  int left = i, right = static_cast<int>(lists.size() - 1); //[left, right), lower bound algorithm
  while (left <= right)
  {
    int mid = (right + left) >> 1;
    if (lists[mid] < v)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }
  result = left;
  return static_cast<std::size_t>(left) < lists.size() && lists[left] == v;
}

/*
 * loop invariant:
 * [0, left-1] <= v, [right+1, size] > v
 * assert: left = right+1
 *
 */

template <typename value_type >
void UpperBound(const vector<value_type>& lists, const value_type& v, int i, int& result)
{
  int left = i, right = static_cast<int>(lists.size() - 1); //[left, right), lower bound algorithm
  while (left <= right)
  {
    int mid = (right + left) >> 1;
    if (lists[mid] <= v)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }
  result = left;
}

template <typename value_type >
void BinaryIntersect(const vector<value_type>& list1, const vector<value_type>& list2, vector<value_type>& result)
{
  int pos1 = 0, pos2 = 0;
  int size1 = static_cast<int>(list1.size()), size2 = static_cast<int>(list2.size());
  result.reserve(size1);
  while (pos1 < size1 && pos2 < size2)
  {
    if (LowerBound(list2, list1[pos1], pos2, pos2))
    {
      result.push_back(list1[pos1]);
      ++pos2;
    }
    ++pos1;
    if (pos2 < size2 && LowerBound(list1, list2[pos2], pos1, pos1))
    {
      result.push_back(list2[pos2]);
      ++pos1;
    }
    ++pos2;
  }
}


#endif // BINARY_SEARCH_H_
