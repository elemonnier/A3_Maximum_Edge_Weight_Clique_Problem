//
// Created by Sébastien on 23/04/2021.
//

#include "define_constructHeuristic.h"
#include <iostream>
void constructHeuristicAlgorithm(vertex* list, vector<int>* tableau_result, int index, int* somme_poids) {
    bool actualisation = false;
    int max = 0;
    int index_max = 0;
    int index_actual = 1;
    int start = 0;
    int compteur = 0;
    int compteur_vertex = 0;
    int *pos;
    int weight_max = 0;
    vertex save_weight[index + 1];
    vector<int> tableau_result_final;
    vector<int> list_vertex;
    vector<int> tableau_used;
    std::vector<int>::iterator it_vector_result;
    std::vector<int>::iterator it_vector_used;
    for (int j = 1; j <= index; j++) { //Boucle pour voir tous les sommets et on prend celui avec le plus de voisin
        if (list[j].degree > start) {
            start = list[j].degree;
        }
    }

    for (int j = 1; j <= index; j++) {
        if (list[j].degree == start) {
            list_vertex.insert(list_vertex.end(), j);
        }
    }
    map<int, int>::iterator j;
    while (compteur_vertex != list_vertex.size()) {
        index_actual = list_vertex[compteur_vertex];
        while (true) {
            ///Mise à jour de notre résultat///
            it_vector_result = find(tableau_result->begin(), tableau_result->end(), index_actual);
            if (it_vector_result != tableau_result->end()) { //On ajoute dans le résultat le sommet de notre clique
                break;
            } else {
                tableau_result->insert(tableau_result->begin(), index_actual);
            }

            ///Selection du prochain sommet///
            for (j = list[index_actual].neighbour.begin(); j != list[index_actual].neighbour.end(); j++) { //Boucle pour voir tous les voisins et récupérer celui avec le poids le plus important
                if (j->second > max) {
                    index_max = j->first;
                    max = j->second;
                }
            }

            for (j = list[index_max].neighbour.begin(); j != list[index_max].neighbour.end(); j++) {
                it_vector_result = find(tableau_result->begin(), tableau_result->end(),j->first);// Je check si le voisin se trouve dans le vector
                if (it_vector_result != tableau_result->end()) {
                    compteur++;
                }
            }

            if (compteur == tableau_result->size()) {
                actualisation = true;
            }
            if (actualisation) {
                ///On retire l'accès au sommet actuel pour le prochain sommet pour éviter des boucles///
                for (j = list[index_max].neighbour.begin(); j != list[index_max].neighbour.end(); j++) { //On supprime le lien entre le sommet actuel et le nouveau sommet pour éviter une boucle infinie
                    if (j->first == index_actual) {
                        save_weight[index_max].degree++;
                        save_weight[index_max].neighbour[j->first] = j->second;
                        j->second = 0;
                    }
                }
                index_actual = index_max;
                actualisation = false;
            } else {
                for (j = list[index_actual].neighbour.begin(); j != list[index_actual].neighbour.end(); j++) { //Boucle pour voir tous les voisins et récupérer celui avec le poids le plus important
                    if (index_max == j->first) {
                        save_weight[index_max].degree++;
                        save_weight[index_max].neighbour[j->first] = j->second;
                        j->second = 0;
                    }
                }
            }
            max = 0;
            index_max = 0;
            compteur = 0;
        }
        ///Calcul du poids de la clique///
        pos = tableau_result->data();
        for (int i = 0; i < tableau_result->size(); i++) {
            for (j = list[*pos].neighbour.begin(); j != list[*pos].neighbour.end(); j++) {
                it_vector_used = find(tableau_used.begin(), tableau_used.end(), j->first);
                if (it_vector_used != tableau_used.end()) {
                    it_vector_result = find(tableau_result->begin(), tableau_result->end(), j->first);
                    if (it_vector_result != tableau_result->end()) {
                        *somme_poids += j->second;
                    }
                }
            }
            tableau_used.insert(tableau_used.begin(), *pos);
            pos++;
        }
        ///On sauvegarde la meilleure clique///
        if(*somme_poids > weight_max){
            weight_max = *somme_poids;
            tableau_result_final = *tableau_result;
        }
        ///On réinitialise la liste pour pouvoir recommencer (on remet les poids différents de 0)///
        for(int i = 1; i < index;i++){
            for(j = list[i].neighbour.begin(); j != list[i].neighbour.end(); j++){
                if(j->second == 0){
                    j->second = save_weight[i].neighbour[j->first];
                }
            }
        }
        *somme_poids = 0;
        tableau_result->clear();
        tableau_used.clear();
        compteur_vertex++;
    }
    ///On donne la meilleure clique et son poids à la fin///
    *somme_poids = weight_max;
    *tableau_result = tableau_result_final;
}
