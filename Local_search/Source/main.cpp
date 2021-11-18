#include "define.h"

int main() {
    FILE *ptr = fopen("../Instances/10_75.in", "r");
    int state = 0;
    int a = 0, b = 0, c = 0, n = 0, m = 0;
    fscanf(ptr, "%d %d", &n, &m); /// obtention du nombre de sommets et arêtes
    vertex adjacency_list[n + 1];
    /// on crée une liste égale à n+1 et non n car il n'existe pas de sommet 0 dans les graphes,
    /// chaque index de ce tableau réfèrera à un sommet.

    setToReturn maxClique;
    int sumMaxDegree = 0; /// on choisit l'arête qui a le plus d'arêtes voisines pour maximiser les chances
    /// d'avoir une clique max
    vector<int> maxEdgeDegree;

    while (true) {
        state = fscanf(ptr, "%d %d %d", &a, &b, &c);
        if (state == EOF) {
            break;
        }
        /// mise à jour de la liste d'adjacence en fonction des données d'entrée
        adjacency_list[a].degree++;
        adjacency_list[a].neighbour[b] = c;
        adjacency_list[b].degree++;
        adjacency_list[b].neighbour[a] = c;
        if ((adjacency_list[a].degree + adjacency_list[b].degree) > sumMaxDegree){
            sumMaxDegree = (adjacency_list[a].degree + adjacency_list[b].degree);
            maxEdgeDegree.clear();
            maxEdgeDegree.push_back(a);
            maxEdgeDegree.push_back(b);
        }
    }


    maxClique.taille = 2;
    maxClique.clique = adjacency_list[maxEdgeDegree[0]].neighbour[maxEdgeDegree[1]];
    maxClique.tab = maxEdgeDegree; /// on assigne la dernière valeur de fscanf (arbitraire)
    /// pour le 10_75, mettre en entrée la derniere arete du fichier ne donne pas le max clique exact,
    /// mais 4 234 {1,3,5,7} oui
    fclose(ptr);

    bool hasIncreased = true;

    clock_t start, end;
    start = clock();

    ////////////////////////////////////////// START TIMER ///////////////////////////////////////////////////////////


    localSearch(n, adjacency_list, &maxClique, &hasIncreased);


    ////////////////////////////////////////// END TIMER /////////////////////////////////////////////////////////////

    end = clock();

    double result = (double) (end - start) / (double) CLOCKS_PER_SEC;

    cout << "\nResults:\n" << maxClique.taille << " " << maxClique.clique << endl;
    for (int v : maxClique.tab){
        cout << v << " ";
    }

    printf("\n\nTime: %.6f seconds\n", result);

    /// écriture dans le fichier de sortie
    FILE *ptr2 = fopen("10_75_local_search.out", "w");
    fprintf(ptr2, "%d %d\n", maxClique.taille, maxClique.clique);
    for(int i = 0; i < maxClique.taille; i++)
    {
        fprintf(ptr2, "%d ", maxClique.tab[i]);
    }

    return 0;
}
