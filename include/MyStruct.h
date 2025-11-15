#pragma once
#include <string>

struct MyStruct {
    int x;
    std::string name;
    double value;
    MyStruct(int x_, std::string name_,double value_)
        : x(x_),name(std::move(name_)), value(value_) {}
};