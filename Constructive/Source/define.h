#ifndef LOCAL_SEARCH_DEFINE_H
#define LOCAL_SEARCH_DEFINE_H

#include <map>
#include <vector>
#include <algorithm>
#include <system_error>

using namespace std;

typedef struct vertex : public error_code {
//    int index;
    /// degré du vertex (nombre de voisins directs)
    int degree = 0;
    /// cette map représente les sommets voisins de vertex (premier int), et leur distance à vertex (second int)
    std::map<int, int> neighbour;
} vertex;

typedef struct setToReturn { /// structure utile pour écrire dans le fichier de sortie
    int taille;
    int clique;
    std::vector<int> tab;
}setToReturn;


#endif