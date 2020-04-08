#ifndef PARSEELGRAPH_H
#define PARSEELGRAPH_H

#include "Using.h"
#include <memory>

std::unique_ptr<Graph> parseELGraph(const char* filepath);

#endif //PARSEELGRAPH_H
