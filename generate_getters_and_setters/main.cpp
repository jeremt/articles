//
// Copyright (c) 2015 DudeTeam. All rights reserved.
//

#include <string>
#include <iostream>
#include "field.h"

class Player {
public:
    Player(std::string const &name) :
            _name(name) {

    }
public:
    FIELD(std::string, name, true, true);
    FIELD(int, age, true, _set_age);

private:
    void _set_age(int age) {
        if (age > 10) {
            _age = age;
        }
    }
};

int main(int, char **) {
    Player p("toto");

    std::cout << p.name() << std::endl;
    return 0;
}