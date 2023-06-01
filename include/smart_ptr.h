#ifndef SMART_PTR_H_
#define SMART_PTR_H_

#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>

class Counter {
    int count;

public:
    Counter() : count(1) {};

    Counter& operator++() {
        count++;
        return *this;
    }

    Counter operator++(int) {
        Counter tmp = *this;
        count++;
        return tmp;
    }

    Counter& operator--() {
        count--;
        return *this;
    }

    Counter operator--(int) {
        Counter tmp = *this;
        count--;
        return tmp;
    }

    int get_count() const { return count; };
};

template <typename T>
struct default_deleter {
    void operator()(T* ptr) const {
        delete ptr;
    }
};

template <typename T>
struct default_deleter<T[]> {
    void operator()(T* ptr) const {
        delete [] ptr;
    }
};

template <typename T>
class smart_ptr {
    using Deleter = std::function<void(T*)>;

    T* obj;
    Counter* cntr;
    Deleter deleter;
    bool is_checked_null;

    void warning() const {
        if (!is_checked_null)
            std::cerr << "Warning: pointer is used without checking on null\n";
    }

    void clear() {
        if (cntr) {
            (*cntr)--;
            if (!cntr->get_count()) {
                delete cntr;
                deleter(obj);
            }
        }
    }

public:
    smart_ptr() : obj(nullptr), cntr(nullptr), deleter(nullptr), is_checked_null(false) {};
    smart_ptr(nullptr_t, const Deleter& _deleter = default_deleter<T>())
        : obj(nullptr), cntr(nullptr), deleter(_deleter), is_checked_null(false) {};
    smart_ptr(T* _obj, const Deleter& _deleter = default_deleter<T>())
        : obj(_obj), cntr(new Counter()), deleter(_deleter), is_checked_null(false) {};

    smart_ptr(const smart_ptr& _smart_ptr)
        : obj(_smart_ptr.obj), cntr(_smart_ptr.cntr), deleter(_smart_ptr.deleter), is_checked_null(false) {
        (*cntr)++;
    }
    smart_ptr(smart_ptr&& _smart_ptr)
        : obj(_smart_ptr.obj), cntr(_smart_ptr.cntr),
          deleter(std::move(_smart_ptr.deleter)), is_checked_null(false) {
        _smart_ptr.obj = _smart_ptr.cntr = _smart_ptr.deleter = nullptr;
    }

    ~smart_ptr() {
        clear();
    }

    smart_ptr& operator=(const smart_ptr& _smart_ptr) {
        is_checked_null = false;
        if (cntr != _smart_ptr.cntr) {
            clear();
            obj = _smart_ptr.obj;
            cntr = _smart_ptr.cntr;
            deleter = _smart_ptr.deleter;
            (*cntr)++;
        }
        return *this;
    }
    smart_ptr& operator=(smart_ptr&& _smart_ptr) {
        is_checked_null = false;
        clear();
        obj = _smart_ptr.obj;
        cntr = _smart_ptr.cntr;
        deleter = _smart_ptr.deleter;
        _smart_ptr.obj = _smart_ptr.cntr = _smart_ptr.deleter = nullptr;
    }

    void reset(T* _obj) {
        is_checked_null = false;
        clear();
        obj = _obj;
        if (obj) cntr = new Counter();
            else cntr = nullptr;
    }

    void swap(smart_ptr<T>& _smart_ptr) {
        is_checked_null = false;
        std::swap(obj, _smart_ptr.obj);
        std::swap(cntr, _smart_ptr.cntr);
        std::swap(deleter, _smart_ptr.deleter);
    }

    operator bool() {
        is_checked_null = true;
        return obj != nullptr;
    }

    T* get() const { return obj; };

    T& operator*() const {
        warning();
        return *obj;
    }

    T* operator->() const {
        warning();
        return obj;
    }

    T& operator[](size_t ind) const {
        warning();
        return *(obj + ind);
    }

    int use_count() { return (cntr) ? cntr->get_count() : 0; };
};

#endif // SMART_PTR_H_
