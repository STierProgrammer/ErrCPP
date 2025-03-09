#include <iostream>
#include <string>
#include "include/err/result.hpp"

Result<int, std::string> divide(int a, int b) {
    if (b == 0) {
        return Result<int, std::string>::Err("Division by zero");
    }

    return Result<int, std::string>::Ok(a / b);
}

int main() {
    auto result = divide(1, 0);

    std::cout << "Result 1: " << result.unwrap() << std::endl;

    return 0;
}
