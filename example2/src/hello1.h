#pragma once

#include <iostream>
#include <utility>

class Hello1 {
public:
    Hello1():
        Hello1(std::string("default")) {};
    explicit Hello1(std::string name):
        name(std::move(name)) {};
    void Print() const;

private:
    std::string name;
};