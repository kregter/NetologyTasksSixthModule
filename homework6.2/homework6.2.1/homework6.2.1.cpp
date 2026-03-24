#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>

std::mutex m;

void incr_queue(int& queue_count, int max_queue) {
	while (queue_count < max_queue) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::lock_guard<std::mutex> grd(m);
		(queue_count)++;
		std::cout << "Текущая очередь ++ = " << queue_count << std::endl;
	}
}

void decr_queue(int& queue_count) {
	while (queue_count > 0) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::lock_guard<std::mutex> grd(m);
		(queue_count)--;
		std::cout << "Текущая очередь -- = " << queue_count << std::endl;
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	
	int max_queue = 6;
	int queue_count = 1;
	// std::atomic<int> queue_count = 1; // 2 variants, mutex or atomic
	
	std::thread t1(incr_queue, std::ref(queue_count), max_queue);
	std::thread t2(decr_queue, std::ref(queue_count));
	t1.join();
	t2.join();
	
	return 0;
}