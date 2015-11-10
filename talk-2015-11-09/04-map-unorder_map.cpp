#include "common.h"
#include <iostream>
#include <unordered_map>
#include <set>
#include <map>
using std::map;
using std::unordered_map;
using std::vector;
using std::cout;
using std::set;

void GenerateMapRandom(unordered_map<int, int>& m, unordered_map<int, int>::size_type size,
                       int maxV)
{
  while(m.size() != size)
  {
    m[rand() % maxV] = rand();
  }
}

void GenerateRandom(vector<int>& vi,int size, int maxV)
{
  set<int> s;
  while(s.size() != size)
  {
    s.insert(rand() % maxV);
  }
  vector<int> temp(s.begin(), s.end());
  vi.swap(temp);
}

using std::cin;
int main(int argc, char *argv[])
{
  int map_size = 1000000;
  int query_count = 1000000;
  unordered_map<int, int> unmap;
  vector<int> query;
  cout << "input map size:" << endl;
  cin >> map_size;
  GenerateMapRandom(unmap, map_size, map_size*1000);
  map<int, int> non_unmap(unmap.begin(), unmap.end());
  GenerateRandom(query, query_count, query_count*1000);
  int count = 0;
  int64_t beg = 0;

  beg = CurrentUSeconds();
  for (vector<int>::iterator it = query.begin(); it != query.end(); ++it)
  {
    if (unmap.find(*it) != unmap.end())
    {
      count++;
    }
  }
  int64_t c1 = CurrentUSeconds() - beg;
  cout << "query unorder map match: " << count << std::endl;
  cout << "cost time:" << c1 << std::endl;

  count = 0;
  beg = CurrentUSeconds();
  for (vector<int>::iterator it = query.begin(); it != query.end(); ++it)
  {
    if (non_unmap.find(*it) != non_unmap.end())
    {
      count++;
    }
  }
  int64_t c2 = CurrentUSeconds() - beg;
  cout << "query map match: " << count << std::endl;
  cout << "cost time: " << c2 << std::endl;
  return 0;
}
