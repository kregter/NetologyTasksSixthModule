#include <iostream>
#include <future>
#include <list>
#include <thread>

void find_min(std::promise<std::list<int>::iterator>&& prom,
    std::list<int>::iterator start,
    std::list<int>::iterator end)
{
    auto min_it = start;
    for (auto it = start; it != end; ++it)
    {
        if (*it < *min_it)
        {
            min_it = it;
        }
    }
    prom.set_value(min_it);
}

void my_sort(std::list<int>& lst)
{
    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        std::promise<std::list<int>::iterator> prom;
        std::future<std::list<int>::iterator> fut = prom.get_future();

        std::thread t(find_min,
            std::move(prom),
            it,
            lst.end());

        auto min_it = fut.get();
        if (min_it != it)
        {
            std::swap(*it, *min_it);
        }

        t.join();
    }
}

int main()
{
    std::list<int> lst = { 5, 3, 8, 1, 4 };

    std::cout << "Initial list: ";
    for (const auto& val : lst)
    {
        std::cout << val << " ";
    }
    std::cout << '\n';

    my_sort(lst);

    std::cout << "Sorted list: ";
    for (const auto& val : lst)
    {
        std::cout << val << " ";
    }
    std::cout << '\n';
}