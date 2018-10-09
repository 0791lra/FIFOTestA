#ifndef FIFO_H
#define FIFO_H
#include <queue>
#include <mutex>
#include <thread>
#include <utility>

/** \class Fifo
 *  \brief Thread-safe FIFO queue
 *
 *  Wrapper for std::queue that provides thread-safety and limits the threads
 *  capacity.
 */
template<class T> class Fifo
{
public:
    /// Create a Fifo with specified capacity
    Fifo(unsigned int capacity)
        : qCapacity(capacity)
    {
    };

    /// Push an item onto the stack unless it is full.
    bool push(const T& i)
    {
        std::lock_guard<std::mutex> pushLock(queueMutex);
        if(fifoQ.size() >= qCapacity) {
            return false;
        }
        fifoQ.push(i);
        return true;
    };

    /// Pop an item off the stack, waiting for one to be available
    T pop()
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        while(fifoQ.size() == 0) {
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            lock.lock();
        }
        T retVal = fifoQ.front();
        fifoQ.pop();
        return retVal;
    };

    /// Pop an item off the stack, returning if none is available
    std::pair<bool, T> pop_try()
    {
        std::pair<bool, T> retVal;
        std::lock_guard<std::mutex> pushLock(queueMutex);
        if(fifoQ.size() > 0) {
            retVal.first = true;
            retVal.second = fifoQ.front();
            fifoQ.pop();
        }
        else {
            retVal.first = false;
        }
        return retVal;
    };

private:
    std::queue<T> fifoQ; /*<! encapsulated queue */
    unsigned int qCapacity; /*<! maximum number of items that can be queued */

    std::mutex queueMutex; /*<! Mutex to protect the queue */
};

#endif
