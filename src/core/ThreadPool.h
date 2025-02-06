//
// Created by Romain on 06/02/2024.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "pch.h"

class ThreadPool {
   public:
    ThreadPool(uint32_t numThreads);
    ~ThreadPool();

    using Task = std::function<void()>;

    void Enqueue(Task task);  // Add a task to the queue

    static std::shared_ptr<ThreadPool> Create(uint32_t numThreads);

   private:
    std::vector<std::thread> m_Workers;  // Contain active threads
    std::queue<Task> m_Tasks;            // Store queued tasks

    // Synchronisation
    std::mutex m_QueueMutex;              // Protect task queue access
    std::condition_variable m_Condition;  // Allows threads to wait for a task to become available
    bool m_Stop;                          // Indicates whether the thread pool should stop

    void WorkerThread();  // Loop the threads:
                          // 1. Wait for a task
                          // 2. Run the task
                          // 3. Wait for the next one
};

#define BIND_THREADED_FN(fn) \
    [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif  // THREADPOOL_H