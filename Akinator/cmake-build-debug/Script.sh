#!/bin/bash 
./Akinator
dot Node.dot -Tjpg -O
gwenview Node.dot.jpg
