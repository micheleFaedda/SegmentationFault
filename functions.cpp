//
// Created by michele on 24/04/25.
//

#include "functions.h"
void divideByDelta(const bigrational &delta,
                         bigrational &x,
                         bigrational &y,
                         bigrational &z) {
    x = x / delta;
    y = y / delta;
    z = z / delta;
}
