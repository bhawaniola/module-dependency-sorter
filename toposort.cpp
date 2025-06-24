#include "toposort.h"
#include <queue>
#include <stdexcept>

TopoSort::TopoSort(const std::vector<std::string>& modules, const std::vector<std::pair<std::string, std::string>>& dependencies)
    : modules(modules) {

    for (const auto& module : modules)
        inDegree[module] = 0;

    for (const auto& dep : dependencies) {
        graph[dep.first].push_back(dep.second);
        inDegree[dep.second]++;
    }
}

std::vector<std::string> TopoSort::sort() {
    std::queue<std::string> q;
    for (const auto& mod : modules)
        if (inDegree[mod] == 0)
            q.push(mod);

    std::vector<std::string> result;

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        result.push_back(current);

        for (const std::string& neighbor : graph[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    if (result.size() != modules.size()) {
        throw std::runtime_error("Cycle detected in dependency graph. Topological sort not possible.");
    }

    return result;
}
