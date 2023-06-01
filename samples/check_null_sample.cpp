#include <iostream>

#include <smart_ptr.h>

int main() {
    smart_ptr<int> data(new int[5]{ 0, 1, 2, 3, 4 });

    std::cout << "Without checking on null" << "\n";
    std::cout << data[0] << "\n";

    std::cout << "With checking on null" << "\n";
    if (data)
        std::cout << data[0] << "\n";

    return 0;
}
