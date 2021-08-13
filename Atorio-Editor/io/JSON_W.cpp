#include "JSON_W.hpp"
#include <fstream>
#include <iomanip>

JSON JSON_IO::load(std::string fname) {
    std::ifstream i(fname.c_str());
    JSON j;
    i >> j;
    return j;
}

void JSON_IO::save(std::string fname, JSON j) {
    std::ofstream o(fname.c_str());
    o << std::setw(4) << j << std::endl;
}