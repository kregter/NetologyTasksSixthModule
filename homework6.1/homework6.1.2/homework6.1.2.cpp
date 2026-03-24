#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void sum(std::vector<int>& vec1, std::vector<int>& vec2, std::vector<int>& result, int from, int to)
{
    for (int i = from; i < to; i++)
    {
        result[i] = vec1[i] + vec2[i];
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl;

    std::cout << "\t\t1000" << " \t\t" << "10000" << " \t\t" << "100000" << " \t\t" << "1000000" << std::endl;

    int vector_length = 1000;
    int threads_count = 1;

    for (threads_count = 1; threads_count <= 16; threads_count *= 2)
    {
        std::cout << threads_count << " Поток  \t";
        for (vector_length = 1000; vector_length <= 1000000; vector_length *= 10)
        {
            std::vector<int> a(vector_length);
            std::vector<int> b(vector_length);
            std::vector<int> result(vector_length);

            std::vector<std::thread> threads;

            auto start = std::chrono::steady_clock::now();

            int delta = vector_length / threads_count;
            for (int i = 0; i < threads_count; ++i) {
                int start = i * delta;
                int end = (i + 1 == threads_count) ? vector_length : start + delta;
                threads.emplace_back(sum, std::ref(a), std::ref(b), std::ref(result), start, end);
            }

            for (auto& th : threads)
            {
                th.join();
            }

            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;

            std::cout << duration.count() << " ms\t";
        }
        std::cout << std::endl;
    }
    return 0;
}