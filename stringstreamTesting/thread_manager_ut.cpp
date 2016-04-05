#include "thread_manager.h"
#include "common.h"
#include <iostream>
#include <atomic>
#include <sstream>

using std::ostringstream;
using std::cout;
std::atomic<uint64_t> length(0);

void stringstreamF(int& i)
{
  ostringstream os;
  for (int k = 0; k < i; k++)
    os << k;
  length += os.str().size();
  //cout << os.str() << std::endl;
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
  //cout << result << std::endl;
  length += result.size();
}
const int32_t thread_num = 20;
int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  using namespace micro_ad::utils;
  using Task_t = Task<int>;
  ThreadManager<Task_t> tm(thread_num, "square calculate");
  for (int i = 0; i < 100000; i++)
  {
    std::shared_ptr<Task_t>  task = std::make_shared<Task_t>();
    task->data_ = i;
    task->task_routine_ = snprintfF;
    tm.AddTask(task);
  }
  uint64_t cur = CurrentUSeconds();
  tm.Start();
  while (tm.QueueSize() != -thread_num)
  {
    usleep(1000);
  }
  cout << "snprintf cost time: " << CurrentUSeconds() - cur << std::endl;
  cout << "the total length: "  << length << std::endl;

  ThreadManager<Task_t> tm2(thread_num, "square calculate");
  for (int i = 0; i < 100000; i++)
  {
    std::shared_ptr<Task_t>  task = std::make_shared<Task_t>();
    task->data_ = i;
    task->task_routine_ = stringstreamF;
    tm2.AddTask(task);
  }
  cur = CurrentUSeconds();
  tm2.Start();
  while (tm2.QueueSize() != -thread_num)
  {
    usleep(1000);
  }
  cout << "stringstream cost time: " << CurrentUSeconds() - cur << std::endl;
  cout << "the total length: "  << length << std::endl;

  return 0;
}
