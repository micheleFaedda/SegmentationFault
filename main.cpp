/*****************************************************************************************
 *              MIT License                                                              *
 *                                                                                       *
 * Copyright (c) 2022 G. Cherchi, F. Pellacini, M. Attene and M. Livesu                  *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION     *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                *
 *                                                                                       *
 * Authors:                                                                              *
 *      Gianmarco Cherchi (g.cherchi@unica.it)                                           *
 *      https://www.gianmarcocherchi.com                                                 *
 *                                                                                       *
 *      Fabio Pellacini (fabio.pellacini@uniroma1.it)                                    *
 *      https://pellacini.di.uniroma1.it                                                 *
 *                                                                                       *
 *      Marco Attene (marco.attene@ge.imati.cnr.it)                                      *
 *      https://www.cnr.it/en/people/marco.attene/                                       *
 *                                                                                       *
 *      Marco Livesu (marco.livesu@ge.imati.cnr.it)                                      *
 *      http://pers.ge.imati.cnr.it/livesu/                                              *
 *                                                                                       *
 * ***************************************************************************************/

#ifdef _MSC_VER // Workaround for known bugs and issues on MSVC
#define _HAS_STD_BYTE 0  // https://developercommunity.visualstudio.com/t/error-c2872-byte-ambiguous-symbol/93889
#define NOMINMAX // https://stackoverflow.com/questions/1825904/error-c2589-on-stdnumeric-limitsdoublemin
#endif

#include "booleans.h"
#include "filesystem"
#include "cinolib/meshes/trimesh.h"
#include "code/triangles_intersections/orientTemplated.h"

std::vector<std::string> files;
bool test = false;
namespace fs = std::filesystem;
bool debug = true;

int main(int argc, char **argv)
{
    std::cout << "Trying the conversion" << std::endl;
    const genericPoint * P_tmp = new explicitPoint3D(-3187387764.50317621, 1126377053.35020828, 188836791.971181154);
    const genericPoint * Q_tmp = new explicitPoint3D(-3149376875.99077082, 1267182566.25400305, 66971483.9567909241);
    const genericPoint * R_tmp = new explicitPoint3D(-3076994817.51175404, 1138988462.58166265, 171892881.34736976);
    const genericPoint * S_tmp = new explicitPoint3D(-3234895480.78921461, 1320481356.62345767, 195023508.552951127);
    const genericPoint * T_tmp = new explicitPoint3D(-3270817787.86637497, 1300215181.04815841, 1.39057735376339457e-06);

    genericPoint * new_LPI2 = new implicitPoint3D_LPI(P_tmp->toExplicit3D(), Q_tmp->toExplicit3D(), R_tmp->toExplicit3D(), S_tmp->toExplicit3D(), T_tmp->toExplicit3D());

    bigrational x_tmp, y_tmp, z_tmp;
    new_LPI2->getExactXYZCoordinates(x_tmp,y_tmp,z_tmp);
    std::cout << x_tmp << std::endl;
    std::cout << y_tmp << std::endl;
    std::cout << z_tmp << std::endl;


    BoolOp op;
    std::string file_out;

    if(debug) {
        std::cout << "Debug mode enabled" << std::endl;
        op = UNION;
        files.emplace_back("../32770_sf_a.obj");
        files.emplace_back("../32770_sf_a_rotated.obj");
        file_out = "output.obj";
    }
    if(!debug){
        if(argc < 5)
        {
            std::cout << "syntax error!" << std::endl;
            std::cout << "./exact_boolean BOOL_OPERATION (intersection OR union OR subtraction) input1.obj input2.obj output.obj" << std::endl;
            return -1;
        }
        else
        {
            if (strcmp(argv[1], "intersection") == 0)       op = INTERSECTION;
            else if (strcmp(argv[1], "union") == 0)         op = UNION;
            else if (strcmp(argv[1], "subtraction") == 0)   op = SUBTRACTION;
            else if (strcmp(argv[1], "xor") == 0)           op = XOR;
        }
        for(int i = 2; i < (argc -1); i++)
            files.emplace_back(argv[i]);

        file_out = argv[argc-1];
    }


    std::vector<double> in_coords, bool_coords;
    std::vector<uint> in_tris, bool_tris;
    std::vector<uint> in_labels;
    std::vector<std::bitset<NBIT>> bool_labels;

    loadMultipleFiles(files, in_coords, in_tris, in_labels);

    //new_P->getExactXYZCoordinates(x_tmp,y_tmp,z_tmp);

    booleanPipeline(in_coords, in_tris, in_labels, op, bool_coords, bool_tris, bool_labels);

    cinolib::write_OBJ(file_out.c_str(), bool_coords, bool_tris, {});

    if(test) {
        fs::path script_dir = fs::absolute(fs::path(argv[0])).parent_path();
        fs::path exePath = fs::absolute(script_dir / "mesh_booleans_inputcheck");
        const std::string exe = exePath.string();

        // Costruzione del comando da eseguire
        std::string command = std::string(exe) + " " + file_out.c_str();
        // Esecuzione del comando
        int result = system(command.c_str());
        if (result != 0) {
            std::cerr << "Error in the execution of the command" << std::endl;
        }
    }
    return 0;
}