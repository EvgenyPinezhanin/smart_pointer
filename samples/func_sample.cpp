#include <iostream>
#include <memory>

#include <smart_ptr.h>

void foo(smart_ptr<int> ptr) {
    // something...
    std::cout << "counter = " << ptr.use_count() << "\n";
}

int main() {
    smart_ptr<int> ptr(new int[10], default_deleter<int[]>());
    std::cout << "counter = " << ptr.use_count() << "\n";

    foo(ptr);
    std::cout << "counter = " << ptr.use_count() << "\n";

    return 0;
}
