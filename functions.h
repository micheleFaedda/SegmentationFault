//
// Created by michele on 24/04/25.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "numerics.h"

void divideByDelta(const bigrational &delta,
                         bigrational &x,
                         bigrational &y,
                         bigrational &z);

bigrational orient3D(const bigrational *p0, const bigrational *p1, const bigrational *p2, const bigrational *p3);
#endif //FUNCTIONS_H
