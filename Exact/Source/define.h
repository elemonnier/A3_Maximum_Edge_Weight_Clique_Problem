#ifndef EXACT_ALGORITHM_BACKTRACKING_DEFINE_H
#define EXACT_ALGORITHM_BACKTRACKING_DEFINE_H

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct vertex {
    /// degré du vertex (nombre de voisins directs)
    int degree = 0;
    /// cette map représente les sommets voisins de vertex (premier int), et leur distance à vertex (second int)
    map<int, int> neighbour;
} vertex;

typedef struct setToReturn { /// structure permettant d'écrire dans le fichier de sortie
    int taille;
    int clique;
    vector<int> tab;
} setToReturn;

void exactAlgorithm(int n, vertex* list, setToReturn* maxClique);

void exactRecursive(int n, vertex *list, setToReturn *maxClique, vector<int>* actualClique, int actualCliqueWeight, vector<int>* verticesToTest);

#endif