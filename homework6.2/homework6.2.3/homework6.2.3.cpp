#include <iostream>
#include <mutex>

class Data
{

public:
    int value;
    std::mutex mtx;
};

void my_swap_1(Data& data_1, Data& data_2)
{
    std::lock(data_1.mtx, data_2.mtx);
    std::lock_guard<std::mutex> lock_1(data_1.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock_2(data_2.mtx, std::adopt_lock);

    int temp = data_1.value;
    data_1.value = data_2.value;
    data_2.value = temp;
}

void my_swap_2(Data& data_1, Data& data_2)
{
    std::scoped_lock(data_1.mtx, data_2.mtx);

    int temp = data_1.value;
    data_1.value = data_2.value;
    data_2.value = temp;
}

void my_swap_3(Data& data_1, Data& data_2)
{

    std::unique_lock<std::mutex> lock_1(data_1.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock_2(data_2.mtx, std::defer_lock);
    std::lock(lock_1, lock_2);

    int temp = data_1.value;
    data_1.value = data_2.value;
    data_2.value = temp;
}

int main()
{
    Data data_1;
    data_1.value = 10;
    Data data_2;
    data_2.value = 20;

    my_swap_1(data_1, data_2);
    std::cout << "data_1.value = " << data_1.value << ", data_2.value = " << data_2.value << std::endl;

    my_swap_2(data_1, data_2);
    std::cout << "data_1.value = " << data_1.value << ", data_2.value = " << data_2.value << std::endl;

    my_swap_3(data_1, data_2);
    std::cout << "data_1.value = " << data_1.value << ", data_2.value = " << data_2.value << std::endl;
}