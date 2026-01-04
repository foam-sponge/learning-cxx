#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 动态设置容量的构造器，初始化前两个基值并准备缓存
    DynFibonacci(int cap) : cache(new size_t[cap]), cached(0), capacity(cap) {
        if (capacity <= 0) return;
        cache[0] = 0;
        if (capacity > 1) {
            cache[1] = 1;
            cached = 1;
            for (int k = 2; k < capacity; ++k) cache[k] = 0;
        } else {
            cached = 0;
        }
    }

    // 析构器释放动态分配的缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 按需计算并缓存斐波那契值
    size_t get(int i) {
        if (i < 0 || i >= capacity) return 0;
        if (i <= cached) return cache[i];
        for (int idx = cached + 1; idx <= i; ++idx) {
            cache[idx] = cache[idx - 1] + cache[idx - 2];
        }
        cached = i;
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
