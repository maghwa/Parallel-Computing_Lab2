#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_LIGNES 1000
#define NB_COLONNES 1000
#define NB_THREADS 4

int A[NB_LIGNES][NB_COLONNES];
int x[NB_COLONNES];
int y[NB_LIGNES];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *multiply(void *arg) {
    int id = *(int*) arg;
    int i, j, start, end;
    start = id * NB_LIGNES / NB_THREADS;
    end = (id+1) * NB_LIGNES / NB_THREADS;

    for (i = start; i < end; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            pthread_mutex_lock(&mutex);
            y[i] += A[i][j] * x[j];
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

int main() {
    int i, j;
    pthread_t threads[NB_THREADS];
    int ids[NB_THREADS];

    // Initialisation des matrices et vecteurs
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            A[i][j] = i + j; // Exemple de matrice
        }
        y[i] = 0;
    }
    for (j = 0; j < NB_COLONNES; j++) {
        x[j] = j; // Exemple de vecteur
    }

    // Création des threads
    for (i = 0; i < NB_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, &ids[i]);
    }

    // Attente de la fin des threads
    for (i = 0; i < NB_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Affichage du résultat
    for (i = 0; i < NB_LIGNES; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");

    return 0;
}
