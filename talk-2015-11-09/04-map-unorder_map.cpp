#include "common.h"
#include <iostream>
#include <unordered_map>
#include <set>
#include <map>
#include <string>
using std::string;
using std::map;
using std::unordered_map;
using std::vector;
using std::cout;
using std::set;

string GenRanStr(int len)
{
  std::string charCand = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
  std::string cur;
  for(int j = 0; j < len; j++)
  {
    cur.push_back(charCand[rand()%charCand.size()]);
  }
  return cur;
}
void GenerateMapRandom(unordered_map<string, int>& m, size_t size)
{
  while(m.size() != size)
  {
    m[GenRanStr(10)] = rand();
  }
}

void GenerateRandom(unordered_map<string, int>& vi, int size, vector<string>& result)
{
  for (unordered_map<string, int>::iterator it = vi.begin(); it != vi.end(); ++it)
  {
    if (rand() % 100 < 50)
    {
      result.push_back(it->first);
    }
  }
  for (size_t i = result.size(); i < size; i++)
  {
    result.push_back(GenRanStr(10));
  }
}

using std::cin;
int main(int argc, char *argv[])
{
  int map_size = 100000;
  int query_count = 1000000;
  unordered_map<string, int> unmap;
  vector<string> query;
  cout << "input map size:" << endl;
  cin >> map_size;
  GenerateMapRandom(unmap, map_size);
  map<string, int> non_unmap(unmap.begin(), unmap.end());
  GenerateRandom(unmap, query_count, query);
  int count = 0;
  int64_t beg = 0;

  cout << "unordered map size:" << unmap.size() << std::endl;
  cout << "map size:" << non_unmap.size() << std::endl;
  beg = CurrentUSeconds();
  for (vector<string>::iterator it = query.begin(); it != query.end(); ++it)
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
  for (vector<string>::iterator it = query.begin(); it != query.end(); ++it)
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
