#include <iostream>
#include "define.h"
#include <algorithm>
#include "define_constructHeuristic.h"

using namespace std;

int main() {
    FILE *ptr = fopen("../Instances/10_75.in", "r");
    int state = 0;
    int a = 0, b = 0, c = 0, n = 0, m = 0;
    state = fscanf(ptr, "%d %d", &n, &m); /// obtention du nombre de sommets et arêtes
    vertex adjacency_list[n + 1];
    /// on crée une liste égale à n+1 et non n car il n'existe pas de sommet 0 dans les graphes de Leandro,
    /// chaque index de ce tableau réfèrera à un sommet.
    while (69420) {
        state = fscanf(ptr, "%d %d %d", &a, &b, &c);
        if (state == EOF) {
            break;
        }
        /// mise à jour de la liste d'adjacence en fonction des données d'entrée
        adjacency_list[a].degree++;
        adjacency_list[a].neighbour[b] = c;
        adjacency_list[b].degree++;
        adjacency_list[b].neighbour[a] = c;
    }
    fclose(ptr);

    clock_t start, end;
    start = clock();
    ////////////////////////////////////////// DEBUT TIMER ///////////////////////////////////////////////////////////

    vector<int> tableau_result;
    vector<int> tableau_fired;
    int somme_poids = 0;
    constructHeuristicAlgorithm(adjacency_list,&tableau_result,n,&somme_poids);
    ////////////////////////////////////////// FIN TIMER /////////////////////////////////////////////////////////////

    end = clock();

    double result = (double) (end - start) / (double) CLOCKS_PER_SEC;
    printf("Time: %.6f", result);
    printf(" seconds \n");
    int* pos = tableau_result.data();
    cout << "Taille de la clique : " << tableau_result.size() << endl;
    cout << "Elements dans la clique : ";
    for(int i = 0; i < tableau_result.size(); i++){
        cout << *pos++ << " ";
    }
    cout << endl;
    cout << "Poids de la clique : " << somme_poids << endl;


    /// écriture dans le fichier de sortie
    FILE *ptr2 = fopen("10_75_constructive.out", "w");
    fprintf(ptr2, "%d %d\n", tableau_result.size(), somme_poids);
    int* pos2 = tableau_result.data();
    for(int i = 0; i < tableau_result.size(); i++)
    {
        fprintf(ptr2, "%d ", *pos2++);
    }

    return 0;
}
