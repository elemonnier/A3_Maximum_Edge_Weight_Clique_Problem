#ifndef LOCAL_SEARCH_HEURISTIC_DEFINE_H
#define LOCAL_SEARCH_HEURISTIC_DEFINE_H

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

void localSearch(int n, vertex* list, setToReturn *maxClique, bool* hasIncreased);

void localSearchAlgorithm(int n, vertex* list, setToReturn *maxClique, bool* hasIncreased, int actualCliqueWeight);

#endif