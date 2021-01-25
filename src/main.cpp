// Kosek, Kowalski, Convex_Hull

#include<iostream>
#include<vector>
#include<unordered_set>

#include "Point.hpp"
#include "Triangle.hpp"
#include "preprocessing.hpp"
#include "naive_solver.hpp"
#include "quickhull_solver.hpp"
#include "incremental_solver.hpp"
#include "data_converter.hpp"
#include "data_generator.hpp"
#include "gift_wrapping.hpp"
#include "Edge.hpp"
#include "timer.hpp"

int main(int argc, char *argv[]) {
    
    std::string input_file;
    data_converter c;
    data_generator g;
    timer t;
    std::vector<Point> points;
    std::vector<Triangle> convex_hull;
    std::string cmd = "python3 ./src/visualize.py";
    std::string cmd2 = "python3 ./src/time.py";
    
    if(argc != 5 && argc != 6 && argc != 9) {
		std::cout << "niepoprawna liczba parametrów programu" << std::endl;
		return 1;
	}

    if(*argv[1] != '1' && *argv[1] != '2' && *argv[1] != '3') {
		std::cout << "niepoprawne polecenie" << std::endl;
		return 1;
	}

    if(*argv[2] != 'n' && *argv[2] != 'i' && *argv[2] != 'g' && *argv[2] != 'q') {
		std::cout << "niepoprawny algorytm" << std::endl;
		return 1;
	}

    switch(*argv[1]) {

        case '1':

            points = c.load(argv[3]);
            Preprocessing::voxelize(points, std::stoi(argv[4]));
            
            switch(*argv[2]) {

            case 'n':

                Naive_solver solver;
                convex_hull = solver.solve(points);
                break;
            case 'i':

                Incremental_solver solver1;
                convex_hull = solver1.solve(points);
                break;
            case 'g':

                gift_wrapping solver2;
                convex_hull = solver2.solve(points);
                break;

            case 'q':

                Quickhull_solver solver3;
                convex_hull = solver3.solve(points);
                break;
            default:

                Quickhull_solver solver4;
                convex_hull = solver4.solve(points);
            }

            c.save(points, convex_hull);
            ::popen(cmd.c_str(), "r");
            break;
        case '2':

            switch(*argv[3]) {

            case 'n':

                g.generate_normal_distribution(std::stoi(argv[4]), std::stoi(argv[5]));
                break;
            case 'c':

                g.generate_cube_data(std::stoi(argv[4]), std::stoi(argv[5]));
                break;
            case 's':

                g.generate_sphere_data(std::stoi(argv[4]), std::stoi(argv[5]));
                break;
            }
            
            points = c.load();
            Preprocessing::voxelize(points, std::stoi(argv[6]));

            switch(*argv[2]) {

            case 'n':

                Naive_solver solver;
                convex_hull = solver.solve(points);
                break;
            case 'i':

                Incremental_solver solver1;
                convex_hull = solver1.solve(points);
                break;
            case 'g':

                gift_wrapping solver2;
                convex_hull = solver2.solve(points);
                break;

            case 'q':

                Quickhull_solver solver3;
                convex_hull = solver3.solve(points);
                break;
            default:

                Quickhull_solver solver4;
                convex_hull = solver4.solve(points);
            }

            c.save(points, convex_hull);
            ::popen(cmd.c_str(), "r");
            break;
        case '3':

            t.measure_time(std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]), std::stoi(argv[7]), *argv[2], *argv[3], std::stoi(argv[8]));
            ::popen(cmd2.c_str(), "r");
            break;
    }


    //data_generator g;

    //int d = 1;
    //std::string cmd = "python3 ./src/visualize.py";

    //g.generate_sphere_data(10000, 10000);
    //std::vector<Point> points = c.load();
    //Preprocessing::voxelize(points, d);
    //Incremental_solver solver2;
    //Naive_solver solver1;
    //gift_wrapping solver;
    //Quickhull_solver solver3;
    //std::vector<Triangle> convex_hull = solver.solve(points);
    //c.save(points, convex_hull);
    //::popen(cmd.c_str(), "r");

    // timer t;
    // std::string cmd = "python3 ./src/time.py";

    // t.measure_time(100, 30, 1000, 10000);
    // ::popen(cmd.c_str(), "r");
}
