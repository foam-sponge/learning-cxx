#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // 1. 初始化 ans，提前分配与 val 相同的大小（避免写入时越界）
    std::vector<std::string> ans(val.size());
    
    // 2. 调用 std::transform：一元操作版本
    // 输入范围：val.begin() ~ val.end()（所有int元素）
    // 输出范围：ans.begin()（起始位置，需提前分配空间）
    // 一元函数：lambda表达式（捕获无，接收int，返回string，实现“乘2+转字符串”）
    std::transform(
        val.begin(),          // 输入范围起始迭代器
        val.end(),            // 输入范围结束迭代器
        ans.begin(),          // 输出范围起始迭代器
        [](int num) -> std::string {  // 自定义一元操作
            return std::to_string(num * 2);  // 先乘2，再转字符串
        }
    );

    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}