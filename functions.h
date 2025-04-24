//
// Created by michele on 24/04/25.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "numerics.h"

void divideByDeltaAndOrient3D(const bigrational &delta,
                         bigrational &x,
                         bigrational &y,
                         bigrational &z);

bigrational orient_3d_bigrational (const bigrational *pa ,
                                   const bigrational *pb ,
                                   const bigrational *pc ,
                                   const bigrational *pd);
#endif //FUNCTIONS_H
