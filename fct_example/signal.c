#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Fonction de gestion du signal
void handle_sigint(int sig) {
    printf("Signal %d reçu. Interruption ignorée.\n", sig);
}

int main() {
    // Associe SIGINT au gestionnaire handle_sigint
    signal(SIGINT, handle_sigint);

    // Boucle infinie
    while (1) {
        printf("En cours d'exécution...\n");
        sleep(1); // Délai pour observer les effets
    }

    return 0;
}