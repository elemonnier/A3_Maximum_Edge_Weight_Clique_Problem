#include "define.h"

void localSearch(int n, vertex* list, setToReturn *maxClique, bool* hasIncreased) {

    for (int counter = 0; counter < n - 2; counter++) {
        localSearchAlgorithm(n, list, maxClique, hasIncreased, maxClique->clique);
    }

    sort(maxClique->tab.begin(), maxClique->tab.end());
}

void localSearchAlgorithm(int n, vertex *list, setToReturn *maxClique, bool *hasIncreased, int actualCliqueWeight) {
    if (*hasIncreased) {
        vector<int> verticesToTest;

        for (int i = 1; i <= n; i++) { /// remplissage du tableau n-k
            if (count(maxClique->tab.begin(), maxClique->tab.end(), i) == 0) {
                verticesToTest.push_back(i);
            }
        }
        vector<int> tempMax = maxClique->tab;
        for (int it1 : tempMax) {
            /// complexité de k

            int tempWeight1 = actualCliqueWeight;
            vector<int> temp = tempMax;
            for (int i : temp) {
                tempWeight1 -= list[i].neighbour[it1];
            }
            temp.erase(remove(temp.begin(), temp.end(), it1), temp.end()); /// suppression d'un sommet


            for (vector<int>::const_iterator it2 = verticesToTest.begin(); it2 != verticesToTest.end(); it2++) {
                int tempWeight2 = tempWeight1;
                bool isClique;
                bool condition = false;
                bool needToBreak = false;
                while (!condition) {
                    isClique = true;
                    for (int i : temp) {
                        if (list[i].neighbour.count(*it2) == 0) {
                            isClique = false;
                            break;
                        }
                        tempWeight2 += list[i].neighbour[*it2];
                    }
                    if (isClique) {
                        temp.push_back(*it2);
                        condition = true;
                    } else if (it2 != verticesToTest.end() - 1) {
                        tempWeight2 = tempWeight1;
                        it2++;
                    } else {
                        needToBreak = true;
                        condition = true;
                    }
                }

                if (needToBreak) {
                    break;
                }

                for (auto it3 = it2 + 1; it3 != verticesToTest.end(); it3++) {
                    /// double for => test des 2 parmi n-k (complexité n^2)

                    int tempWeight3 = tempWeight2;
                    condition = false;
                    needToBreak = false;
                    while (!condition) {
                        isClique = true;
                        for (int i : temp) {
                            if (list[i].neighbour.count(*it3) == 0) {
                                isClique = false;
                                break;
                            }
                            tempWeight3 += list[i].neighbour[*it3];
                        }
                        if (isClique) {
                            temp.push_back(*it3);
                            condition = true;
                        } else if (it3 != verticesToTest.end() - 1) {
                            tempWeight3 = tempWeight2;
                            it3++;
                        } else {
                            needToBreak = true;
                            condition = true;
                        }
                    }

                    if (needToBreak) {
                        break;
                    }

                    if (tempWeight3 > maxClique->clique) { /// update de la clique
                        maxClique->clique = tempWeight3;
                        maxClique->taille = temp.size();
                        maxClique->tab.clear();
                        maxClique->tab.insert(maxClique->tab.end(), temp.begin(), temp.end());
                    }

                    temp.erase(remove(temp.begin(), temp.end(), *it3), temp.end());
                }
                temp.erase(remove(temp.begin(), temp.end(), *it2), temp.end());
            }
        }
        if (maxClique->taille == tempMax.size()) {
            *hasIncreased = false;
        }
    }
}