/*
 * author: yuandx
 * create: 2015-06-18
 * email: yuandx@mvad.com
 */

#ifndef PUBLIC_THREAD_MANAGER_H_
#define PUBLIC_THREAD_MANAGER_H_
#include <pthread.h>
#include <sys/time.h>
#include <algorithm>
#include <tbb/concurrent_queue.h>
#include <string>
#include <vector>
#include <memory>
namespace micro_ad
{
namespace utils
{

using tbb::concurrent_bounded_queue;
using std::string;
using std::vector;

template <typename T>
struct Task
{
  T data_;
  using TASKRUTINE = void (*)(T& );
  TASKRUTINE task_routine_;
};

template <typename TASK>
class ThreadManager
{
public:
  ThreadManager(int thread_num, const string& manager_name,
                int task_capacity = 100000);
  void Start();
  void Stop();
  void AddTask(const std::shared_ptr<TASK>& );
  std::ptrdiff_t QueueSize()
  {
    return tasks_.size();
  }
private:
  void Worker();
  static void* WorkerWrapper(void*);

private:
  //no copy
  ThreadManager(const ThreadManager&);
  void operator=(const ThreadManager&);

private:
  bool running_;
  const int thread_num_;
  concurrent_bounded_queue<std::shared_ptr<TASK>> tasks_;
  vector<pthread_t> thread_ids_;
  string name_;
};

template <typename TASK>
ThreadManager<TASK>::ThreadManager(int thread_num, const string& manager_name, int task_capacity) :
  running_(false), thread_num_(thread_num)
{
  name_ = manager_name;
  tasks_.set_capacity(task_capacity);
}

template <typename TASK>
void ThreadManager<TASK>::Start()
{
  running_ = true;
  for (int i = 0; i != thread_num_; ++i)
  {
    pthread_t id;
    pthread_create(&id, NULL, ThreadManager::WorkerWrapper, this);
    thread_ids_.push_back(id);
  }
}
template <typename TASK>
void ThreadManager<TASK>::Stop()
{
  running_ = false;
}
template <typename TASK>
void ThreadManager<TASK>::AddTask(const std::shared_ptr<TASK>& task)
{
  tasks_.push(task);
}

template <typename TASK>
void ThreadManager<TASK>::Worker()
{
  while (running_)
  {
    std::shared_ptr<TASK> t;
    tasks_.pop(t);
    t->task_routine_(t->data_);
  }
}
template <typename TASK>
void* ThreadManager<TASK>::WorkerWrapper(void* arg)
{
  ThreadManager* tm = static_cast<ThreadManager*>(arg);
  tm->Worker();
  return NULL;
}

}
}
#endif // PUBLIC_THREAD_MANAGER_H_
