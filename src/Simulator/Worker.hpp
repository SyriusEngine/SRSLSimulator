#pragma once

#include <functional>
#include <condition_variable>
#include <list>
#include <thread>

class Worker{
public:
    Worker();

    ~Worker();

    void stop();

    template<typename... Args>
    void addTask(Args&&... args){
        {
            std::lock_guard<std::mutex> lk(m_Mutex);
            m_Queue.push_back(std::bind(std::forward<Args>(args)...));
        }

        m_Condition.notify_all();
    }

    template<typename... Args>
    void addTaskSync(Args&&... args){
        bool finished = false;

        {
            std::lock_guard<std::mutex> lk(m_Mutex);
            m_Queue.push_back([func = std::bind(std::forward<Args>(args)...), &finished](){
                func();
                finished = true;
            });
        }

        m_Condition.notify_all();

        while (!finished){
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

private:

    void threadFunc();

private:
    std::thread m_Thread;
    std::list<std::function<void()>> m_Queue;
    std::mutex m_Mutex;
    std::condition_variable m_Condition;

    bool m_IsRunning;
};