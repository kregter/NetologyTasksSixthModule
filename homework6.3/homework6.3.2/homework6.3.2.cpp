#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <future>

template<typename Iterator, typename Function>
void parallel_for_each(Iterator first, Iterator end, Function func)
{
    size_t size = std::distance(first, end);
    if (size < 2)
    {
        std::for_each(first, end, func);
        return;
    }
    else
    {
        Iterator mid = first;
        std::advance(mid, size / 2);

        std::async(parallel_for_each<Iterator, Function>, first, mid, func);
        parallel_for_each(mid, end, func);
    }
}


int main()
{
    std::list<int> lst = { 5, 3, 8, 1, 4 };

    std::cout << std::accumulate(lst.begin(), lst.end(), 0) << std::endl;

    for (const auto& val : lst)
    {
        std::cout << val << " ";
    }
    std::cout << '\n';

    parallel_for_each(lst.begin(), lst.end(), [](int& n) { n *= 2; });

    for (const auto& val : lst)
    {
        std::cout << val << " ";
    }
    std::cout << '\n';
}