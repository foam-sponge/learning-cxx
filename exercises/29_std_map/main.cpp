#include "../exercise.h"
#include <map>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>

template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // 方案1：使用 find() 接口（推荐，明确表达“查找”语义）
    // find() 返回指向键的迭代器，若不存在则返回 map.end()
    return map.find(key) != map.end();

    // 方案2：使用 count() 接口（适用于键唯一的容器，如 map）
    // count() 返回键的出现次数（map 中键唯一，故返回 0 或 1）
    // return map.count(key) > 0;
}

template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // 利用 std::map::operator[] 特性：
    // 1. 若 key 存在：返回对应 value 的引用，直接赋值更新
    // 2. 若 key 不存在：自动插入 (key, 默认构造的 value)，再返回引用赋值
    map[key] = value;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    set(secrets, "hello"s, "world"s);
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" shoud be in `secrets`");
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" shoud not be in `secrets`");

    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    set(secrets, "hello"s, "developer"s);
    ASSERT(secrets["hello"] == "developer", "hello -> developer");

    return 0;
}