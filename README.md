# Parallel-Computing_Lab2
## Les Threads:

Les threads, qu’on appelle aussi processus légers, sont des unités d’exécution qui opèrent dans le 
contexte d’un processus. Un processus peut contenir plusieurs threads qui exécutent tous le même 
programme et partagent la même mémoire. Plus précisément, les segments de code (le programme), 
de données (les variables globales) et le tas (les allocations dynamiques) sont partagés entre les 
différents threads d’un même processus. Chaque thread dispose de sa propre pile, ce qui leur permet 
de poursuivre les chemins d’exécution différents.
La mémoire partagée permet à des threads d’un processus d’échanger des données sans recourir à 
des outils de communication entre processus tels que tubes.

### Exercice 1 : Parallélisation de la multiplication matrice × vecteur. 
L’opération de multiplication d’une matrice par un vecteur est l’une des plus utiles en informatique 
(calcul scientifique, infographie, etc.). Il est très intéressant de la paralléliser pour en améliorer la 
performance. Elle est réalisée simplement par les deux boucles montrées en Figure 1 où on voit 
comment le vecteur résultat y est calculé à partir de la matrice A et du vecteur x. Plus précisément, on 
voit que le i-ième élément du vecteur y est calculé à partir seulement de la i-ième ligne de la matrice A 
et de tout le vecteur x. Puisque A et x restent constants, on peut calculer chaque élément du vecteur y 
indépendamment les uns des autres.
for (i = 0; i < NB_LIGNES; i++) 
for (j = 0; j < NB_COLONNES; j++) 
y[i] += A[i][j] * x[j];

on propose un programme en utilisant les threads pour le calcul du vecteur y tel que chaque élément de ce 
vecteur soit calculé en parallèle par rapport aux autres .


Le programme utilise la bibliothèque pthread pour créer plusieurs threads qui vont calculer indépendamment les éléments du vecteur y. Chaque thread utilise une portion différente de la matrice A et du vecteur x pour calculer les éléments correspondants de y. La variable mutex est utilisée pour éviter les conflits d'accès lors de la mise à jour des éléments de y.

La variable NB_THREADS peut être ajustée pour optimiser les performances en fonction des caractéristiques du système.
