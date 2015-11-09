#include "common.h"
int main(int argc, char *argv[])
{
  int max_int = 100000, iterate_times = 100;

  vector<int> search_vector, sample;
  set<int> temp;
  GenSet(temp, 1000, max_int);
  search_vector.insert(search_vector.end(), temp.begin(), temp.end());
  GenVector(sample, 1000000, max_int);

  int find_times = 0, lower_bound = 0;

  int64_t beg = CurrentUSeconds();
  for (int i = 0; i != iterate_times; i++)
  {
    for (vector<int>::iterator it = sample.begin(); it != sample.end(); ++it)
    {
      find_times += BinarySearch(search_vector, *it, -1, lower_bound) ? 1 : 0;
    }
  }
  int64_t end = CurrentUSeconds();
  cout << "find_times : " << find_times << std::endl;
  cout << "cost time:" << end - beg << std::endl;

  find_times = 0;
  beg = CurrentUSeconds();
  for (int i = 0; i != iterate_times; i++)
  {
    for (vector<int>::iterator it = sample.begin(); it != sample.end(); ++it)
    {
      find_times += std::binary_search(search_vector.begin(), search_vector.end(), *it) ? 1 : 0;
    }
  }
  end = CurrentUSeconds();
  cout << "find_times : " << find_times << std::endl;
  cout << "cost time:" << end - beg << std::endl;
  return 0;
}
