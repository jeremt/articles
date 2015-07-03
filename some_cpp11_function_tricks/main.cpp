#include <iostream>
#include "Callable.h"
#include "Function.h"

auto callable_basic() -> void {
    auto my_number = 3;
    auto add_and_half = make_callable([] (int &result, int n) {
        result = (result + n) / 2;
    }, my_number, 7);
    add_and_half();
    std::cout << my_number << std::endl;
}

auto function_basic() -> void {
    auto my_number = 3;
    auto add_and_half = Function([] (int &result, int n) {
        result = (result + n) / 2;
    });
    add_and_half(my_number, 7);
    std::cout << my_number << std::endl;

    auto add = Function([] (int a, int b) {
        return a + b;
    });

    std::cout << add.call<int>(1, 2) << std::endl;

    auto add_copy = add;
    std::cout << add_copy.call<int>(3, 4) << std::endl;

    auto no_op = Function();

    auto add_assign = Function();
    add_assign = add;

    std::cout << add_assign.call<int>(2, 3) << std::endl;

    auto add_move = std::move(add);
    std::cout << add_move.call<int>(10, 10) << std::endl;

}

int main() {
    callable_basic();
    function_basic();
    return 0;
}