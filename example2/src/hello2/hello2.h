#pragma once

#include <iostream>
#include <utility>

class Hello2 {
public:
    Hello2():
            Hello2(std::string("default")) {};
    explicit Hello2(std::string name):
            name(std::move(name)) {};
    void Print() const;

private:
    std::string name;
};