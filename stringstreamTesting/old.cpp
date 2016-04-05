#include <stdio.h>
#include "thread_manager_old.h"
#include <iostream>
#include <sstream>

using std::ostringstream;
using std::cout;
int64_t length = 0;
void stringstreamF(int& i)
{
  std::stringstream os;
  for (int k = 0; k < i; k++)
    os << k;
  length += os.str().size();
}
void stringStreamWapper(void *arg)
{
  int* p = (int*)arg;
  stringstreamF(*p);
  delete p;
}
const int buff_size = 4096*10;
void snprintfF(int& i )
{
  char tmp[buff_size] = {0};
  int pos = 0;
  std::string result;
  for (int k = 0; k < i; k++)
  {
    pos += snprintf(tmp + pos, buff_size - pos, "%d", k);
    if (buff_size - pos < 20)
    {
      result.append(tmp, pos);
      pos = 0;
    }
  }
  result.append(tmp, pos);
  length += result.size();
}

void printfWrapper(void *arg)
{
  int *p = (int *)arg;
  snprintfF(*p);
  delete p;
}
inline int64_t CurrentUSeconds()
{
  struct timeval cur;
  gettimeofday(&cur, NULL);
  return cur.tv_sec *1000000 + cur.tv_usec;
}

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  using namespace micro_ad::utils;
  ThreadManager tm(20, "square calculate");
  for (int i = 0; i < 100000; i++)
  {
    int* p = new int(i);
    tm.AddTask(printfWrapper, p);
  }
  uint64_t cur = CurrentUSeconds();
  tm.Start();
  while (tm.QueueSize() != -20)
  {
    //cout << "sleep 1000..." << std::endl;
    usleep(1000);
  }
  cout << "printf cost time: " << CurrentUSeconds() - cur << std::endl;
  cout << "the total length: "  << length << std::endl;

  ThreadManager tm2(20, "square calculate");
  for (int i = 0; i < 100000; i++)
  {
    int* p = new int(i);
    tm2.AddTask(stringStreamWapper, p);
  }
  cur = CurrentUSeconds();
  tm2.Start();
  while (tm2.QueueSize() != -20)
  {
    usleep(1000);
  }
  cout << "stringstream cost time: " << CurrentUSeconds() - cur << std::endl;
  cout << "the total length: "  << length << std::endl;

  //tm.Stop();
  return 0;
}
