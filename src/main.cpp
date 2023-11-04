#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 3, 4, 6 };

    for (const int& i : v)
    {
        std::cout << i << std::endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
