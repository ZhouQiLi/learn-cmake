//
// Created by 35374 on 2022/7/28.
//

#include "hello1.h"
#include "hello2/hello2.h"

int main() {
    Hello1 h1("foo");
    h1.Print();

    Hello2 h2("bar");
    h2.Print();
}