#include "ThreadPool.h"
//
// Created by Romain on 06/02/2024.
//

ThreadPool::ThreadPool(uint32_t numThreads) : m_Stop(false) {
    for (uint32_t i = 0; i < numThreads; i++) {
        // Each thread executes the workerThread() method
        m_Workers.emplace_back([this] { this->WorkerThread(); });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);  // We lock access to the task queue
        m_Stop = true;                                    // Threads are told to stop
    }
    m_Condition.notify_all();  // Wake up all threads so they can finish

    // Wait for each thread to finish
    for (std::thread &worker : m_Workers) {
        worker.join();
    }
}

void ThreadPool::Enqueue(Task task) {
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);  // We lock access to the task queue
        m_Tasks.push(task);                               // Add the task to the queue
    }
    m_Condition.notify_one();  // Wakes up a waiting thread to execute the task
}

std::shared_ptr<ThreadPool> ThreadPool::Create(uint32_t numThreads) { return std::make_shared<ThreadPool>(numThreads); }

void ThreadPool::WorkerThread() {
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(m_QueueMutex);  // We lock access to the task queue

            // Wait for a task to become available or for a stop request to be made
            m_Condition.wait(lock, [this] { return m_Stop || !m_Tasks.empty(); });

            // If we have to stop and there are no more tasks, we exit the loop
            if (m_Stop && m_Tasks.empty()) return;

            // Retrieve the task to execute
            task = std::move(m_Tasks.front());
            m_Tasks.pop();
        }

        // Execute the task outside the lock to avoid blocking other threads
        task();  // Run the task
    }
}
