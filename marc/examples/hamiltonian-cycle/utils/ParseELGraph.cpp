#include <map>
#include <vector>
#include <fstream>
#include <memory>
#include "ParseELGraph.h"

std::unique_ptr<Graph> parseELGraph(const char* filepath) {
    auto g = std::make_unique<Graph>();
    std::ifstream infile(filepath);
    int from = 0, to = 0, last = 0;
    auto current = std::make_shared<std::vector<unsigned int>>();
    while(infile >> from >> to) {
        if (from != last){
            if (last != 0){
                g->insert(std::pair<unsigned int, std::vector<unsigned int>>(last, *current));
                current->clear();
            }
            last = from;
        }
        current->push_back(to);
    }
    g->insert(std::pair<unsigned int, std::vector<unsigned int>>(last, *current));
    return std::move(g);
}
