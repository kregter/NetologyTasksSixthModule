#include <iostream>
#include <thread>
#include <functional>

void incr_queue(int& queue_count, int max_queue) {
	while (queue_count < max_queue) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		(queue_count)++;
		std::cout << "Текущая очередь ++ = " << queue_count << std::endl;
	}
}

void decr_queue(int& queue_count) {
	while (queue_count > 0) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		(queue_count)--;
		std::cout << "Текущая очередь -- = " << queue_count << std::endl;
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	
	int max_queue = 6;
	int queue_count = 1;
	
	std::thread t1(incr_queue, std::ref(queue_count), max_queue);
	std::thread t2(decr_queue, std::ref(queue_count));
	t1.join();
	t2.join();
	
	return 0;
}