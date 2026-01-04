#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 实现无参构造器，初始化前两个基值并设置已缓存的索引
    Fibonacci() {
        cache[0] = 0;
        cache[1] = 1;
        cached = 1; // 表示已计算到索引 1
        for (size_t k = 2; k < 16; ++k) cache[k] = 0;
    }

    // 按需计算并缓存斐波那契值
    size_t get(int i) {
        if (i < 0) return 0;
        if ((size_t)i <= (size_t)cached) return cache[i];
        for (int idx = cached + 1; idx <= i; ++idx) {
            cache[idx] = cache[idx - 1] + cache[idx - 2];
        }
        cached = i;
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
