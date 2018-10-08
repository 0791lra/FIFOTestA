#ifndef FIFO_H
#define FIFO_H
#include <queue>
#include <mutex>
#include <thread>
#include <utility>

template<class T> class Fifo
{
public:
	Fifo(unsigned int capacity)
		: qCapacity(capacity)
	{
	};

	bool push(const T& i)
	{
		std::lock_guard<std::mutex> pushLock(queueMutex);
		if(fifoQ.size() >= qCapacity) {
			return false;
		}
		fifoQ.push(i);
		return true;
	};

	T pop()
	{
		std::unique_lock<std::mutex> lock(queueMutex, std::try_to_lock);
		while(!lock.owns_lock()){
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			lock.try_lock();
		}
		T retVal = fifoQ.front();
		fifoQ.pop();
		return retVal;
	};

	std::pair<bool, T> pop_try()
	{
		std::pair<bool, T> retVal;
		std::unique_lock<std::mutex> lock(queueMutex, std::try_to_lock);
		if(!lock.owns_lock()){
			retVal.first = false;
			return retVal;
		}
		retVal.first = true;
		retVal.second = fifoQ.front();
		fifoQ.pop();
		return retVal;
	};

private:
	std::queue<T> fifoQ;
	unsigned int qCapacity;

	// Mutex to protect the queue
	std::mutex queueMutex;
};

#endif
