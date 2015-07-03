//
// Copyright (c) 2015 DudeTeam. All rights reserved.
//

#include <iostream>
#include "PropertyPointer.h"
#include "CounterProperty.h"

int main() {
    auto counter = make_property<CounterProperty>(5);
    std::cout << counter.value<CounterProperty>() << std::endl;
    std::cout << counter.value<CounterProperty>() << std::endl;
    std::cout << counter.value<CounterProperty>() << std::endl;
    std::cout << counter.value<CounterProperty>() << std::endl;
    std::cout << counter.value<CounterProperty>() << std::endl;
    return 0;
}