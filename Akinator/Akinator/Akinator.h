#pragma once

#include "../Node/Node.h"

#define SKIP_SPASES while(*cur == ' ' || *cur == '\n' || *cur == '\t' || *cur == '\r')\
                        cur++;

#define BUFF_SIZE 32




char* CreateBuffer();
char* AddAkinatorTree(Node* node, char* cur);
Node* CreateAkinatorTree();
void WriteAkinatorTree(Node* tree);
void AskQuestion(Node* node);
void Akinator(Node* tree);
void GetAnswer(char* answ_buf);
void ClearBuffer(char* buf);
