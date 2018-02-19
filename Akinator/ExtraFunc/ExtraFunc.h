#pragma once

#include "../Node/Node.h"
#include "../Stack/Stack.h"

void makeDetermination(Node* tree);
void makeCompasition(const Node* tree);
Stack* makeStack(const Node* node);