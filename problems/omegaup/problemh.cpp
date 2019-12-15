#include <iostream>

int main() {
    short n, min, max, count = 0;
    std::cin >> n;
    short* N = new short[n];
    for (int i = 0; i < n; ++i)
        std::cin >> N[i];
    std::cin >> min >> max;
    for (int i = 0; i < n; ++i) 
        if (N[i] >= min && N[i] <= max)
            ++count;
    std::cout << count << std::endl;
    return 0;
}