#pragma once
#include <iostream>
#include "LinkedList.h"

class selector {
    String selector_name;
public:
    selector() = default;

    explicit selector(const char* str) : selector_name(str) {};

    String getSelector_name() const {
        return selector_name;
    };

    void setName(const char* str) {
        this->selector_name = str;
    };

    friend ostream& operator << (ostream& os, const selector& sel) {
        os << sel.selector_name.getStr();
        return os;
    };
};