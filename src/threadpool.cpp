#include "threadpool.h"
#include <QDebug>
#include <QThread>

ThreadPool::ThreadPool(int number_of_threads = 0)
{
    if(number_of_threads <= 0)
    {
        number_of_threads = std::thread::hardware_concurrency();
    }
    numberOfThreads = number_of_threads;
    for(int i = 0; i < number_of_threads; i++)
    {
        std::thread t = std::thread(&ThreadPool::waitOrWork,this,i);
        threadWorkers.push_back(std::move(t));
        threadStatus.push_back(true);
        threadWorkers[i].detach();
    }
    isWaiting = false;
    stopNow = false;
}

void ThreadPool::addThread()
{
    numberOfThreads++;
    std::thread t = std::thread(&ThreadPool::waitOrWork,this,numberOfThreads-1);
    threadWorkers.push_back(std::move(t));
    threadStatus.push_back(true);
    threadWorkers[numberOfThreads-1].detach();
}

void ThreadPool::assignToThread(std::function<void()> function_with_work)
{
    if(isWaiting)
    {
        std::unique_lock<std::mutex> queueEmptyLock(queueEmptyMutex);
        isWaitingForQueue.wait(queueEmptyLock,[&](){ return !isWaiting; });
    }
    std::unique_lock<std::mutex> lock(mutexForQueue);
    functionsWaitingToBeExecuted.push(function_with_work);
    isWorkAvailable.notify_one();
}

void ThreadPool::waitOrWork(int i)
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(mutexForQueue);
        isWorkAvailable.wait(lock, [&](){ return !functionsWaitingToBeExecuted.empty(); });
        std::function<void()> work_to_do = functionsWaitingToBeExecuted.front();
        functionsWaitingToBeExecuted.pop();
        work_to_do();
        if(stopNow)
        {
            break;
        }
        if(isWaiting && functionsWaitingToBeExecuted.empty())
        {
            std::unique_lock<std::mutex> waiterLock(waiterMutex);
            isWaiting = false;
            waiter.notify_one();
        }
    }
    threadStatus[i] = false;
}

void ThreadPool::waitTillAllComplete()
{
    queueEmptyMutex.lock();
    isWaiting = true;
    queueEmptyMutex.unlock();
    std::unique_lock<std::mutex> waiterLock(waiterMutex);
    waiter.wait(waiterLock, [&]() { return (!isWaiting || functionsWaitingToBeExecuted.empty()); });
    isWaiting = false;
    isWaitingForQueue.notify_all();
    //waiter waits till it is woken up when queue is empty
    //notifies assigntothreads to continue
}

ThreadPool::~ThreadPool()
{
   stopNow = true;
   while(threadStatus.size())
   {
       for(int i = 0; i < threadStatus.size(); i++)
       {
           if(threadStatus[i] == false)
           {
               threadStatus.erase(threadStatus.begin() + i);
               i = -1;
           }
       }
   }
}
