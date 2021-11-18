#include "define.h"

void exactAlgorithm(int n, vertex *list, setToReturn *maxClique) {
    for (int counter = 1; counter <= n; counter++) { /// parcours de tous les sommets
        for (map<int, int>::const_iterator it = list[counter].neighbour.begin(); it != list[counter].neighbour.end(); it++) { /// parcours de tous les voisins de chaque sommet
            if (it->first > counter) {
                if (maxClique->clique <
                    it->second) { /// update de la clique (au cas où il n'y a pas mieux que 2 sommets)
                    maxClique->clique = it->second;
                    maxClique->taille = 2;
                    maxClique->tab.clear();
                    maxClique->tab.push_back(counter);
                    maxClique->tab.push_back(it->first);
                }
                vector<int> actual; /// tableau actual : stocker les éléments de clique actuels
                actual.push_back(counter);
                actual.push_back(it->first);
                vector<int> test; /// tableau test : éléments voisins du sommet dans la liste d'adjacence, à tester pour éventuellement augmenter la clique
                for (map<int, int>::const_iterator it2 = list[counter].neighbour.begin();
                     it2 != list[counter].neighbour.end(); it2++) {
                    if (it2->first > it->first) {
                        test.push_back(it2->first);
                    }
                }
                cout << counter << " " << it->first << " -> " << it->second << endl;
                exactRecursive(n, list, maxClique, &actual, it->second, &test);
            }
        }
    }
    sort(maxClique->tab.begin(), maxClique->tab.end()); /// tri des valeurs du tableau de clique
}

void exactRecursive(int n, vertex *list, setToReturn *maxClique, vector<int>* actualClique, int actualCliqueWeight, vector<int>* verticesToTest) {
    if (verticesToTest->empty()){ /// si le tableau à tester est vide, on arrête la récursion
        return;
    }

    for (int it1 : *verticesToTest) { /// parcours du tableau de test
        bool isClique = true;
        int sum = actualCliqueWeight;
        for (int it2 : *actualClique) { /// test de clique
                if (list[it2].neighbour.count(it1) == 0) {
                    isClique = false;
                    break;
                }
                sum += list[it2].neighbour[it1];
            }

        if (isClique) { /// update de la clique, et ré-appel de la récursion afin de trouver une clique plus grande avec les sommets actuels
            actualClique->push_back(it1);
            for (int v : *actualClique) {
                cout << v << " ";
            }
            cout << "-> " << sum << endl;
            if (sum > maxClique->clique){
                maxClique->clique = sum;
                maxClique->taille = actualClique->size();
                maxClique->tab.clear();
                maxClique->tab.insert(maxClique->tab.end(), actualClique->begin(), actualClique->end());
            }
            vector<int> temp;
            for (int i : *verticesToTest){
                if (i > it1) {
                    temp.push_back(i);
                }
            }
            temp.erase(remove(temp.begin(), temp.end(), it1), temp.end());
            exactRecursive(n, list, maxClique, actualClique, sum, &temp);
            actualClique->erase(remove(actualClique->begin(), actualClique->end(), it1), actualClique->end());
        }
    } /// si ce n'est pas une clique, on abandonne la récursion
}