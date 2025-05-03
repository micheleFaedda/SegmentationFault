#include <implicit_point.h>

int main()
{
    const bigrational s0[] = {bigrational(bignatural(static_cast<uint32_t >(28954682368)), bignatural(static_cast<uint32_t> (3)), 1),
                        bigrational(bignatural(static_cast<uint32_t>(18845212751614903)), bignatural(static_cast<uint32_t> (36291456)), -1),
                        bigrational(bignatural(static_cast<uint32_t>(1242883924321459)), bignatural(static_cast<uint32_t> (2097152)), -1)
    };

    const bigrational s1[] = {bigrational(bignatural(static_cast<uint32_t>(28954718211)), bignatural(static_cast<uint32_t> (2)), 1),
                        bigrational(bignatural(static_cast<uint32_t>(18845212751614903)), bignatural(static_cast<uint32_t> (36291456)), -1),
                        bigrational(bignatural(static_cast<uint32_t>(1242883924321459)), bignatural(static_cast<uint32_t> (2097152)), -1)
    };


    std::cout << "Values" << std::endl;
    std::cout << "s0 x y z coords: " << s0[0] << " " << s0[1] << " " << s0[2] << std::endl;
    std::cout << "s1 x y z coords: " << s1[0] << " " << s1[1] << " " << s1[2] << std::endl;
    std::cout << std::endl;

    /*** Comparing with == operator ***/
    std::cout << "Are equals? " << std::endl;
    const char *x_equals = s0[0] == s1[0] ? "yes" : "no";
    std::cout << "s0_x == s1_x: " << x_equals<< std::endl;

    const char *y_equals = s0[1] == s1[1] ? "yes" : "no";
    std::cout << "s0_y == s1_y: " << y_equals<< std::endl;

    const char *z_equals = s0[2] == s1[2] ? "yes" : "no";
    std::cout << "s0_z == s1_z: " << z_equals<< std::endl;


    /*** Comparing with > or < operators ***/
    std::cout << std::endl;
    std::cout << "Other comparisons :" << std::endl;

    const char *less_greather_x = s0[0] < s1[0] ? "yes" : "no";
    std::cout << "s0_x < s1_x: " <<  less_greather_x << std::endl;

    less_greather_x = s0[0] > s1[0] ? "yes" : "no";
    std::cout << "s0_x > s1_x: " <<  less_greather_x << std::endl;

    std::cout << std::endl;

    const char *less_greather_y = s0[1] < s1[1] ? "yes" : "no";
    std::cout << "s0_y < s1_y: " <<  less_greather_y << std::endl;

    less_greather_y = s0[1] > s1[1] ? "yes" : "no";
    std::cout << "s0_y > s1_y: " <<  less_greather_y << std::endl;

    std::cout << std::endl;

    const char *less_greather_z = s0[2] < s1[2] ? "yes" : "no";
    std::cout << "s0_z < s1_z: " <<  less_greather_z << std::endl;

    less_greather_z = s0[2] > s1[2] ? "yes" : "no";
    std::cout << "s0_z > s1_z: " <<  less_greather_z << std::endl;

    std::cout << std::endl;


    /** Calulating distance to be sure that are different **/
    const bigrational distance = (s1[0] - s0[0]) * (s1[0] - s0[0]) +
                              (s1[1] - s0[1]) * (s1[1] - s0[1]) +
                              (s1[2] - s0[2]) * (s1[2] - s0[2]);
    std::cout << "Distance: " << distance << std::endl;


    return 0;
}
