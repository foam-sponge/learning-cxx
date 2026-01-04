#include "../exercise.h"
// 核心头文件：std::string 必需
#include <string>
// std::is_same_v 必需
#include <type_traits>
// std::string_literals (s后缀) 必需
#include <string_view>

int main(int argc, char **argv) {
    // 启用std::string的字面量后缀s（C++14+）
    using namespace std::string_literals;
    auto hello = "Hello"s;  // 推导为std::string
    auto world = "world";   // 推导为const char*

    // 编译期验证类型推导正确性
    static_assert(std::is_same_v<decltype(hello), std::string>, 
                  "hello 必须推导为 std::string 类型");
    static_assert(std::is_same_v<decltype(world), const char*>, 
                  "world 必须推导为 const char* 类型");

    // 字符串拼接：std::string + const char* + const char* + char → std::string
    std::string result = hello + ", " + world + '!';
    
    // 运行时验证（替代编译期断言，因为result是运行时变量）
    if (result != "Hello, world!") {
        // 可根据exercise.h的封装调整错误处理逻辑
        return 1;
    }

    return 0;
}