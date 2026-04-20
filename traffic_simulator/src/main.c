#include "game.h"
#include "player.h"

int main() {
    srand(time(NULL)); // Inizializza il generatore di numeri casuali

    StatoGioco statoCorrente = MENU;
    Giocatore giocatore;

    while (statoCorrente != ESCI) {
        switch (statoCorrente) {
            case MENU:
                // menuPrincipale(&statoCorrente);
                // Per ora, andiamo direttamente al gioco
                statoCorrente = GIOCO;
                break;
            case GIOCO:
                gameLoop(&statoCorrente, &giocatore);
                break;
            case GAMEOVER:
                mostraGameOver(&statoCorrente, &giocatore);
                break;
            case RECORD:
                // Da implementare
                statoCorrente = MENU;
                break;
            case PAUSA:
                // Gestito all'interno di gestisciInput
                break;
            case ESCI:
                // Il loop terminerà
                break;
        }
    }

    printf("Grazie per aver giocato!\n");

    return 0;
}
