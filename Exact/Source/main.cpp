#include "define.h"

int main() {
    FILE *ptr = fopen("../Instances/10_75.in", "r");
    int state = 0;
    int a = 0, b = 0, c = 0, n = 0, m = 0;
    fscanf(ptr, "%d %d", &n, &m); /// obtention du nombre de sommets et arêtes
    vertex adjacency_list[n + 1];
    /// on crée une liste égale à n+1 et non n car il n'existe pas de sommet 0 dans les graphes,
    /// chaque index de ce tableau réfèrera à un sommet.
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
    }
    fclose(ptr);

    setToReturn maxClique;
    maxClique.taille = 0;
    maxClique.clique = 0;

    clock_t start, end;
    start = clock();

    ////////////////////////////////////////// START TIMER ///////////////////////////////////////////////////////////

    exactAlgorithm(n, adjacency_list, &maxClique);

    ////////////////////////////////////////// END TIMER /////////////////////////////////////////////////////////////

    end = clock();

    double result = (double) (end - start) / (double) CLOCKS_PER_SEC;

    cout << "\nResults:\n" << maxClique.taille << " " << maxClique.clique << endl;
    for (int v : maxClique.tab){
        cout << v << " ";
    }

    printf("\n\nTime: %.6f seconds\n", result);

    /// écriture dans le fichier de sortie
    FILE *ptr2 = fopen("10_75_exact.out", "w");
    fprintf(ptr2, "%d %d\n", maxClique.taille, maxClique.clique);
    for(int i = 0; i < maxClique.taille; i++)
    {
        fprintf(ptr2, "%d ", maxClique.tab[i]);
    }

    return 0;
}
