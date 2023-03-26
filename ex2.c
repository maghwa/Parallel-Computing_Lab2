#include <stdio.h>
#include <pthread.h>

#define NUM_PLACES 100
int places[NUM_PLACES];
int nextClientID = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* client_handler(void* arg) {
    int clientID = *(int*)arg;
    int numPlaces = places[clientID - 1];

    pthread_mutex_lock(&mutex);
    while (numPlaces > 0) {
        int i;
        for (i = 0; i < NUM_PLACES; i++) {
            if (places[i] == 0) {
                places[i] = clientID;
                printf("Client %d a réservé la place %d\n", clientID, i + 1);
                numPlaces--;
                if (numPlaces == 0) {
                    pthread_cond_signal(&cond);
                    break;
                }
            }
        }
        if (i == NUM_PLACES) {
            pthread_cond_wait(&cond, &mutex);
        }
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t client_threads[NUM_PLACES];
    int numClients = 0;

    while (1) {
        int numPlaces;
        printf("Entrez le nombre de places que vous voulez réserver (ou un nombre négatif pour quitter) : ");
        scanf("%d", &numPlaces);

        if (numPlaces < 0) {
            break;
        }

        if (numClients == NUM_PLACES) {
            printf("Impossible de traiter la demande : toutes les places sont déjà réservées.\n");
            continue;
        }

        places[nextClientID - 1] = numPlaces;

        int rc = pthread_create(&client_threads[numClients], NULL, client_handler, &nextClientID);
        if (rc) {
            printf("Erreur lors de la création du thread pour le client %d\n", nextClientID);
            break;
        }

        printf("Client %d a demandé la réservation de %d places.\n", nextClientID, numPlaces);

        nextClientID++;
        numClients++;
    }

    int i;
    for (i = 0; i < numClients; i++) {
        pthread_join(client_threads[i], NULL);
    }

    printf("Voici la liste des places :\n");
    for (i = 0; i < NUM_PLACES; i++) {
        if (places[i] == 0) {
            printf("Place %d : libre\n", i + 1);
        } else {
            printf("Place %d : réservée par le client %d\n", i + 1, places[i]);
        }
    }

    return 0;
}
