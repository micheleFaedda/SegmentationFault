#include <implicit_point.h>
#include <functions.h>

int main()
{
    const genericPoint * P = new explicitPoint3D(-3187387764.50317621, 1126377053.35020828, 188836791.971181154);
    const genericPoint * Q = new explicitPoint3D(-3149376875.99077082, 1267182566.25400305, 66971483.9567909241);
    const genericPoint * R = new explicitPoint3D(-3076994817.51175404, 1138988462.58166265, 171892881.34736976);
    const genericPoint * S = new explicitPoint3D(-3234895480.78921461, 1320481356.62345767, 195023508.552951127);
    const genericPoint * T = new explicitPoint3D(-3270817787.86637497, 1300215181.04815841, 1.39057735376339457e-06);

    implicitPoint3D_LPI * LPI = new implicitPoint3D_LPI(P->toExplicit3D(),
                                                 Q->toExplicit3D(),
                                                 R->toExplicit3D(),
                                                 S->toExplicit3D(),
                                                 T->toExplicit3D());

    bigrational x, y, z;
    bigrational delta = bigrational(-23121312331.5435345345);
    LPI->getExactXYZCoordinates(x,y,z); /**Exact crash point**/

    for (int i = 0; i < 100; ++i)
    {
        x = x / delta;
        y = y / delta;
        z = z / delta;

        divideByDelta(delta, x, y, z);

    }


    return 0;
}
