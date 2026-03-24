#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstdint>

#include <mutex>
#include <atomic>

#define NUNBER_POSSITION 1
#define ID_POSSITION 10
#define PROGRESS_BAR_POSSITION 30
#define TOTAL_TIME_POSSITION 58

void setCursorPosition(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

std::mutex mtx;
// std::atomic<uint32_t> count_of_ended_threads = 0;

struct thread_info
{
    uint32_t thread_number;
    std::atomic<std::thread::id> thread_id;
    std::atomic<uint32_t> progress{ 0 };
    std::atomic<long long> duration_ms{ 0 };
};

struct Node
{
    thread_info m_info;
    void foo();
};

void Node::foo()
{
    m_info.thread_id.store(std::this_thread::get_id());

    {
        std::lock_guard<std::mutex> lock(mtx);
        setCursorPosition(NUNBER_POSSITION, m_info.thread_number + 2);
        std::cout << m_info.thread_number << std::flush;
        setCursorPosition(ID_POSSITION, m_info.thread_number + 2);
        std::cout << m_info.thread_id.load() << std::flush;
    }

    auto t0 = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        uint32_t sleep_time = static_cast<uint32_t>(std::rand() % 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        m_info.progress = (i + 1) / 100.0 * 20;
        {
            std::lock_guard<std::mutex> lock(mtx);
            setCursorPosition(PROGRESS_BAR_POSSITION + m_info.progress, m_info.thread_number + 2);
            std::cout << 'X' << std::flush;
        }
    }

    auto t1 = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
    m_info.duration_ms.store(duration.count());

    {
        std::lock_guard<std::mutex> lock(mtx);
        setCursorPosition(TOTAL_TIME_POSSITION, m_info.thread_number + 2);
        std::cout << m_info.duration_ms.load() << " ms" << std::flush;
    }
}

int main()
{
    std::system("clear");
    std::cout << "# \t id \t\t\t  Progress Bar \t\t Time \n\n\n\n";

    const uint32_t thread_count = 4;

    std::vector<std::thread> threads;
    std::vector<Node> nodes(thread_count);

    for (uint32_t i = 0; i < thread_count; ++i)
    {
        nodes[i].m_info.thread_number = i;
        threads.emplace_back(&Node::foo, &nodes[i]);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    setCursorPosition(0, thread_count + 2);

    return 0;
}