/*
 * author: yuandx
 * create: 2016-04-09
 * email: yuandx@mvad.com
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <string>
#include <utility>
#include <functional>
#include <algorithm>
#include <stdio.h>
#include <sstream>
#include <atomic>
#include <future>
#include <thread>
#include <mutex>
#include <chrono>
using std::ostringstream;
using std::istringstream;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::sort;
using std::string;
using std::for_each;
using std::atomic;
using std::thread;
using std::future;
using std::promise;

struct Pair
{
  int key_, val_;
  Pair(int k, int v): key_(k), val_(v)
  {}
};

int main()
{
  Pair p(9, 2);
  vector<Pair> vec = {Pair(1, 0), Pair(2, 0), Pair(3, 0), Pair(6, 0), Pair(6, 0), Pair(6, 0), Pair(7, 0), Pair(9, 0), Pair(10, 0)};
  bool found = binary_search(vec.begin(), vec.end(), p,
                             [](const Pair& p0, const Pair& p1)
                             {
                               return p0.key_ < p1.key_;
                             });
  cout << found << endl;
  auto it = lower_bound(vec.begin(), vec.end(), 6, [](const Pair& p, int v)
                        { return p.key_ < v; });
  if (it != vec.end())
  {
    cout << it->key_ << endl;
  }

  auto it1 = upper_bound(vec.begin(), vec.end(), 6, [](int v, const Pair& p)
                        { return v < p.key_; });
  if (it1 != vec.end())
  {
    cout << it1->key_ << endl;
  }

  return 0;
}
