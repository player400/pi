//
// Created by player402 on 30.03.25.
//

#include "Pattern.h"

bool Pattern::isToken() {
    return false;
}

const Pattern &Pattern::operator[](unsigned int position) {
    return *(patterns[position]);
}

unsigned int Pattern::size() {
    return patterns.size();
}
