#include "common.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <set>
#include <sys/time.h>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::set;
void FastIntersect(vector<int>& v1, vector<int>& v2,
                   vector<int>& result, double factor = 1)
{
  result.reserve(static_cast<int>(v1.size()));
  if ((v1.size() << 2) < v2.size())
  {
    BinaryIntersect(v1, v2, result);
  } else
  {
    NormalIntersect(v1, v2, result);
  }
}

void Merge2(vector<int>& v1, vector<int>& v2, vector<int>& r)
{
  vector<int>::iterator it1 = v1.begin(), it2 = v2.begin();
  while(it1 != v1.end() && it2 != v2.end())
  {
    if(*it1 > *it2)
    {
      r.push_back(*it2);
      ++it2;
    } else if (*it1 < *it2)
    {
      r.push_back(*it1);
      ++it1;
    } else
    {
      r.push_back(*it1);
      ++it1;
      ++it2;
    }
  }

  if(it1 != v1.end())
  {
    r.insert(r.end(), it1, v1.end());
  }
  if(it2 != v2.end())
  {
    r.insert(r.end(), it2, v2.end());
  }
}

void SimpleUnionIntersection(vector<vector<int> >& Bs, vector<int>& A1, vector<int>& result)
{
  vector<int> temp1, temp2;
  for(vector<vector<int> >::iterator it = Bs.begin(); it != Bs.end(); ++it)
  {
    Merge2(*it, temp1, temp2);
    temp1.swap(temp2);
    temp2.clear();
  }
  FastIntersect(A1, temp1, result);
}

void SmartUnionIntersection(vector<vector<int> >& Bs, vector<int>& A1, vector<int>& result)
{
  vector<vector<int> > rs(Bs.size(), vector<int>() );
  for(vector<vector<int> >::size_type i = 0; i != Bs.size(); ++i)
  {
    if (A1.size() > Bs[i].size())
    {
      FastIntersect(A1, Bs[i], rs[i]);
    } else
    {
      FastIntersect(Bs[i], A1, rs[i]);
    }
  }

  vector<int> temp1, temp2;
  for(vector<vector<int> >::iterator it = rs.begin(); it != rs.end(); ++it)
  {
    Merge2(*it, temp1, temp2);
    temp1.swap(temp2);
    temp2.clear();
  }
  result.swap(temp1);
}


void GenerateRandom(vector<int>& vi, set<int>::size_type size, int maxV)
{
  set<int> s;
  while(s.size() != size)
  {
    s.insert(rand() % maxV);
  }
  vector<int> temp(s.begin(), s.end());
  vi.swap(temp);
}

int CombinationSwap(vector<vector<int> >& v1, vector<vector<int> > &v2, int num)
{
  int i = 0;
  while(num != 0)
  {
    if (num&1)
    {
      v1[i].swap(v2[i]);
    }
    i++;
    num /= 2;
  }
}

void PrintVec(vector<int>& vi)
{
  for(vector<int>::iterator it = vi.begin(); it != vi.end(); ++it)
  {
    cout << *it << "\t";
  }
  cout << std::endl;
}



int main(int argc, char *argv[])
{
  int base_size, maxV, vec_count = 20;
  int base_vector_size = 10;
  double incr_fact;
  double  us1 = 0, us2 = 0;
  vector<vector<int> > vvi1(vec_count, vector<int>()), vvi2(vvi1);
  vector<int> A1;
  cout << "please input base_size(int), maxV(int), incr_fact(double)";
  cin >> base_size >> maxV >> incr_fact;
  int num_of_count = base_size;
  int64_t beg = CurrentUSeconds();
  GenerateRandom(A1, base_vector_size, maxV);
  for(int i = 0; i != vec_count; i++)
  {
    num_of_count = static_cast<int>(base_size + 10 * i * incr_fact);
    GenerateRandom(vvi1[i], num_of_count, maxV);
    GenerateRandom(vvi2[i], num_of_count, maxV);
  }

  double end = CurrentUSeconds();
  cout << "generate cost time" << end - beg << std::endl;

  vector<int> result;
  volatile vector<int>::size_type size = 0;
  for(int k = 0; k != 2; k++)
  {
    int max_swap = pow(2, vec_count);
    max_swap /= 1000;
    {
      size = 0;
      cout << "----------------------------------------" << std::endl
           << std::endl;
      int64_t beg = CurrentUSeconds();
      for(int i = 0; i != max_swap; i++)
      {
        CombinationSwap(vvi1, vvi2, i);
        SimpleUnionIntersection(vvi1, A1, result);
        size += result.size();
        CombinationSwap(vvi1, vvi2, i);
        result.clear();
      }
      us1 =  CurrentUSeconds() - beg;
      
      cout << "SimpleUnionIntersection size: " << size << std::endl;
      cout << "SimpleUnionIntersection cost time" << us1 << "us" << std::endl;
      cout << "----------------------------------------" << std::endl;
      cout << std::endl;
    }

    {
      size = 0;
      cout << "----------------------------------------" << std::endl << std::endl;
      beg = CurrentUSeconds();
      for(int i = 0; i != max_swap ; i++)
      {
        CombinationSwap(vvi1, vvi2, i);
        SmartUnionIntersection(vvi1, A1, result);
        size += result.size();
        CombinationSwap(vvi1, vvi2, i);
        result.clear();
      }

      us2  = CurrentUSeconds() - beg;
      cout << "SmartUnionIntersection size: " << size << std::endl;
      cout << "SmartUnionIntersection cost time" << us2 << "us" << std::endl;
      cout << "----------------------------------------" << std::endl;
    }
    cout << "ratios is " << (us1 / us2) << std::endl;
  }
  return 0;
}
