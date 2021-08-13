#ifndef ATORIO_JSON
#define ATORIO_JSON

#include <nlohmann/json.hpp>

using JSON = nlohmann::json;

class JSON_IO {
public:
    static JSON load(std::string fname);
    static void save(std::string fname, JSON j);
};

#endif