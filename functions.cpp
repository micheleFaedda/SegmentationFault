//
// Created by michele on 24/04/25.
//

#include "functions.h"
void divideByDeltaAndOrient3D(const bigrational &delta,
                         bigrational &x,
                         bigrational &y,
                         bigrational &z) {
    x = x / delta;
    y = y / delta;
    z = z / delta;

    std::cout << x << " " << y << " " << z << std::endl;

    //Simply creating 4 points and calling orient_3d_bigrational
    const bigrational p0[3] = {x, y, z};
    const bigrational p1[3] = {x + bigrational(1.0), y + bigrational(1.0), z + bigrational(1.0)};
    const bigrational p2[3] = {x - bigrational(1.0), y - bigrational(1.0), z - bigrational(1.0)};
    const bigrational p3[3] = {x , y, z + bigrational(2.0)};


    bigrational res =  orient_3d_bigrational(p0, p1, p2, p3);

    std::cout << res << std::endl;
}

bigrational orient_3d_bigrational (const bigrational *pa ,
                                   const bigrational *pb ,
                                   const bigrational *pc ,
                                   const bigrational *pd) {
    bigrational adx = pa[0] - pd[0];
    bigrational bdx = pb[0] - pd[0];
    bigrational cdx = pc[0] - pd[0];
    bigrational ady = pa[1] - pd[1];
    bigrational bdy = pb[1] - pd[1];
    bigrational cdy = pc[1] - pd[1];
    bigrational adz = pa[2] - pd[2];
    bigrational bdz = pb[2] - pd[2];
    bigrational cdz = pc[2] - pd[2];

    bigrational res =  adx * (bdy * cdz - bdz * cdy)
                       + bdx * (cdy * adz - cdz * ady)
                       + cdx * (ady * bdz - adz * bdy);
    return res;
}
