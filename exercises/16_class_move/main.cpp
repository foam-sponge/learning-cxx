#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 动态设置容量的构造器
    DynFibonacci(int cap) : cache(nullptr), cached(0), capacity(cap) {
        if (capacity <= 0) { cache = nullptr; cached = -1; capacity = 0; return; }
        cache = new size_t[capacity];
        cache[0] = 0;
        if (capacity > 1) {
            cache[1] = 1;
            cached = 1;
            for (int k = 2; k < capacity; ++k) cache[k] = 0;
        } else {
            cached = 0;
        }
    }

    // 移动构造器（夺取资源）
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr;
        other.cached = -1;
        other.capacity = 0;
    }

    // 移动赋值（处理自移动）
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) {
            delete[] cache;
            cache = other.cache;
            cached = other.cached;
            capacity = other.capacity;
            other.cache = nullptr;
            other.cached = -1;
            other.capacity = 0;
        }
        return *this;
    }

    // 析构器释放资源
    ~DynFibonacci() {
        delete[] cache;
    }

    // 按需计算并缓存斐波那契值
    size_t operator[](int i) {
        if (i < 0 || i >= capacity || capacity == 0) return 0;
        if (i <= cached) return cache[i];
        for (int idx = cached + 1; idx <= i; ++idx) {
            cache[idx] = cache[idx - 1] + cache[idx - 2];
        }
        cached = i;
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
