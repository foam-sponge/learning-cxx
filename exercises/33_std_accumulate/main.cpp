#include "../exercise.h"
#include <numeric>
// 需包含 <functional> 以使用 std::multiplies（C++17 前部分编译器需显式包含）
#include <functional>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    // 1. 计算张量总元素数：用 std::accumulate 计算 shape 所有维度的乘积
    // - 输入范围：shape 数组的起始（std::begin(shape)）到结束（std::end(shape)）
    // - 初始值：1（乘法的单位元，若初始为 0 会导致乘积始终为 0）
    // - 二元操作：std::multiplies<int>()（计算两个 int 的乘积）
    int total_elements = std::accumulate(
        std::begin(shape),        // 输入范围起始迭代器（shape[0]）
        std::end(shape),          // 输入范围结束迭代器（shape[4]，数组末尾后一位）
        1,                        // 初始值（乘法起始值）
        std::multiplies<int>()    // 二元操作：累积值 × 当前维度值
    );

    // 2. 计算总字节数：总元素数 × 单个 float 字节数（sizeof(DataType) 动态获取）
    int size = total_elements * sizeof(DataType);

    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}