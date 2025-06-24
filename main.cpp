#include "toposort.h"
#include <iostream>
#include <fstream>

void readInput(const std::string& filename, std::vector<std::string>& modules, std::vector<std::pair<std::string, std::string>>& dependencies) {
    std::ifstream file(filename);
    int n, d;
    file >> n;
    modules.resize(n);
    for (int i = 0; i < n; ++i) {
        file >> modules[i];
    }

    file >> d;
    for (int i = 0; i < d; ++i) {
        std::string from, to;
        file >> from >> to;
        dependencies.emplace_back(from, to);
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> modules;
    std::vector<std::pair<std::string, std::string>> dependencies;

    if (argc > 1) {
        readInput(argv[1], modules, dependencies);
    } else {
        // Fallback: Hardcoded example
        modules = {"A", "B", "C", "D", "E", "F"};
        dependencies = {{"A", "D"}, {"F", "B"}, {"B", "D"}, {"F", "A"}, {"D", "C"}};
    }

    try {
        TopoSort sorter(modules, dependencies);
        std::vector<std::string> order = sorter.sort();

        std::cout << "Build Order:\n";
        for (const auto& mod : order) {
            std::cout << mod << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
