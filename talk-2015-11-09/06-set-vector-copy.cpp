#include "common.h"
#include <list>
using std::list;

int main()
{
  size_t size = 100000;
  size_t count = 100, total = 0;
  Random rand;
  vector<int> temp;
  while (temp.size() < size)
  {
    temp.push_back(rand.Next());
  }

  int64_t beg = CurrentUSeconds();
  for (size_t i = 0; i != count; i++)
  {
    vector<int> a;
    a.insert(a.end(), temp.begin(), temp.end());
    total += a.size();
  }
  int64_t end = CurrentUSeconds();
  cout << "vec cost: " << end - beg << endl;
  cout << total << endl;

  total = 0;
  beg = CurrentUSeconds();
  for (size_t i = 0; i != count; i++)
  {
    list<int> a(temp.begin(), temp.end());
    total += a.size();
  }
  end = CurrentUSeconds();
  cout << "list cost: " << end - beg << endl;
  cout << total << endl;

  total = 0;
  beg = CurrentUSeconds();
  for (size_t i = 0; i != count; i++)
  {
    set<int> a(temp.begin(), temp.end());
    total += a.size();
  }
  end = CurrentUSeconds();
  cout << "set cost: " << end - beg << endl;
  cout << total << endl;
}
