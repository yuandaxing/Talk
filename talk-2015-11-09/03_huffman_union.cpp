#include "common.h"
#include <list>
void Union(vector<int>& v1, vector<int>& v2, vector<int>& r)
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

using std::list;
vector<int>* StoreTemp(vector<int>& p, list<vector<int> >& tmp)
{
  tmp.push_back(vector<int>());
  vector<int>& back = tmp.back();
  back.swap(p);
  return &back;
}

vector<int>* pop_front(list<vector<int>*>& list)
{
  vector<int>* p = list.front();
  list.pop_front();
  return p;
}

void Insert(vector<int>* pl, list<vector<int>*>& lists)
{
  list<vector<int>*>::iterator it = lists.begin();
  for (; it != lists.end() && (*it)->size() < pl->size(); ++it) ;
  lists.insert(it, pl);
}


void PrintList(vector<int>& v)
{
  for (int i: v)
  {
    cout << i << " ";
  }
  cout << endl;
}
bool compare(const vector<int>* v1, const vector<int> *v2)
{
  return v1->size() <= v2->size();
}
void HuffmanUnion(list<vector<int>* >& lists, vector<int>& result)
{
  list<vector<int> > tmp;
  //  lists.sort(compare);

  while (lists.size() > 2ul)
  {
    vector<int> cur;
    vector<int>* p1 = pop_front(lists), *p2 = pop_front(lists);
    Union(*p1, *p2, cur);
    Insert(StoreTemp(cur, tmp), lists);
  }

  if (lists.size() == 2ul)
  {
    vector<int>* p1 = pop_front(lists), *p2 = pop_front(lists);
    Union(*p1, *p2, result);
  }

  if (lists.size() == 1ul)
  {
    vector<int>* p1 = pop_front(lists);
    result.insert(result.end(), p1->begin(), p1->end());
  }
}

template <typename Iterator>
void Union(Iterator beg, Iterator end, size_t size, vector<int>& result)
{
  vector<int> cur, tmp;

  if (size >= 2ul)
  {
    vector<int>* p1 = *beg, *p2 = *(++beg);
    Union(*p1, *p2, cur);
    ++beg;
  }

  for (; beg != end; ++beg)
  {
    Union(cur, *(*beg), tmp);
    cur.swap(tmp);
    tmp.clear();
  }
  result.swap(cur);
}

void Union(list<vector<int>*>& lists, vector<int>& result)
{
  Union(lists.begin(), lists.end(), lists.size(), result);
}

int main(int argc, char *argv[])
{
  int num_vec = 10, num_element = 10000;
  list<vector<int> > list_vector;
  Random rand;
  for (int i = 0; i != num_vec; i++)
  {
    set<int> tmp;
    GenSet(tmp, num_element, 100000);
    vector<int> tmp1(tmp.begin(), tmp.end());
    list_vector.push_back(tmp1);
  }
  int try_times = 100, result_size = 0;
  int64_t beg = CurrentUSeconds();
  for (int i = 0; i != try_times; i++)
  {
    list<vector<int>*> lists;
    for (list<vector<int> >::iterator it = list_vector.begin(); it != list_vector.end(); ++it)
    {
      lists.push_back(&(*it));
    }
    vector<int> result;
    Union(lists, result);
    result_size += result.size();
  }
  int64_t c2 = CurrentUSeconds() - beg;
  cout << "result_size: " << result_size << std::endl;
  cout << "cost: " << c2 << std::endl;

  result_size = 0;
  beg = CurrentUSeconds();
  for (int i = 0; i != try_times; i++)
  {
    list<vector<int>*> lists;
    for (list<vector<int> >::iterator it = list_vector.begin(); it != list_vector.end(); ++it)
    {
      lists.push_back(&(*it));
    }
    vector<int> result;
    HuffmanUnion(lists, result);
    result_size += result.size();
  }
  int64_t c1 = CurrentUSeconds() - beg;
  cout << "result_size: " << result_size << std::endl;
  cout << "cost: " << c1 << std::endl;

  cout << "ratio : " << c1 * 1.0 / c2 << std::endl;

  return 0;
}
