#ifndef TOPOSORT_H
#define TOPOSORT_H

#include <vector>
#include <string>
#include <unordered_map>

class TopoSort {
public:
    TopoSort(const std::vector<std::string>& modules, const std::vector<std::pair<std::string, std::string>>& dependencies);
    std::vector<std::string> sort(); // Throws exception if cycle detected

private:
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, int> inDegree;
    std::vector<std::string> modules;
};

#endif
