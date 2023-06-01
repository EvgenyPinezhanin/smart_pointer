#include <iostream>

#include <smart_ptr.h>

int main() {
    int* val = new int(100);

    smart_ptr<int> ptr(val);
    std::cout << "ptr counter = " << ptr.use_count() << "\n\n";

    smart_ptr<int> ptr1(ptr);
    std::cout << "ptr counter = " << ptr.use_count() << "\n";
    std::cout << "ptr1 counter = " << ptr1.use_count() << "\n\n";

    smart_ptr<int> ptr2(ptr1);
    std::cout << "ptr counter = " << ptr.use_count() << "\n";
    std::cout << "ptr1 counter = " << ptr1.use_count() << "\n";
    std::cout << "ptr2 counter = " << ptr2.use_count() << "\n\n";

    {
        smart_ptr<int> ptr3(ptr2);
        std::cout << "ptr counter = " << ptr.use_count() << "\n";
        std::cout << "ptr1 counter = " << ptr1.use_count() << "\n";
        std::cout << "ptr2 counter = " << ptr2.use_count() << "\n";
        std::cout << "ptr3 counter = " << ptr2.use_count() << "\n\n";
    }

    std::cout << "ptr counter = " << ptr.use_count() << "\n";
    std::cout << "ptr1 counter = " << ptr1.use_count() << "\n";
    std::cout << "ptr2 counter = " << ptr2.use_count() << "\n\n";

    int* val_new = new int(1000);

    ptr2.reset(val_new);
    std::cout << "ptr counter = " << ptr.use_count() << "\n";
    std::cout << "ptr1 counter = " << ptr1.use_count() << "\n";
    std::cout << "ptr2 counter = " << ptr2.use_count() << "\n\n";

    ptr1.reset(nullptr);
    std::cout << "ptr counter = " << ptr.use_count() << "\n";
    std::cout << "ptr1 counter = " << ptr1.use_count() << "\n";
    std::cout << "ptr2 counter = " << ptr2.use_count() << "\n\n";

    if (ptr) std::cout << "ptr = " << *ptr << "\n";
    if (ptr2) std::cout << "ptr2 = " << *ptr2 << "\n\n";

    ptr.swap(ptr2);

    if (ptr) std::cout << "ptr = " << *ptr << "\n";
    if (ptr2) std::cout << "ptr2 = " << *ptr2 << "\n\n";

    smart_ptr<int> ptr_null;
    std::cout << "ptr_null counter = " << ptr_null.use_count() << "\n\n";

    ptr_null = ptr;
    std::cout << "ptr counter = " << ptr.use_count() << "\n";
    std::cout << "ptr_null counter = " << ptr_null.use_count() << "\n";

    return 0;
}
