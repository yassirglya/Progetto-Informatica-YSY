#include "game.h"

// Funzione per una semplice pausa (cross-platform)
void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

int main() {
    const int FPS = 30;
    const int frameDelay = 1000 / FPS;

    StatoGioco statoCorrente = MENU;
    Giocatore giocatore;

    // Inizializza il gioco
    inizializza_gioco(&giocatore);

    // Loop principale del gioco
    while (1) {
        // Gestione degli stati del gioco
        switch (statoCorrente) {
            case MENU:
                menuPrincipale(&statoCorrente);
                break;
            case GIOCO:
                // Logica del gioco
                aggiorna_logica(&statoCorrente, &giocatore);
                break;
            case PAUSA:
                // Metti in pausa il gioco
                break;
            case GAMEOVER:
                // Fine del gioco
                break;
            case RECORD:
                // Visualizza i record
                break;
        }

        // Disegna la schermata
        disegna_schermo(statoCorrente, &giocatore);

        // Controllo del frame rate
        sleep_ms(frameDelay);
    }

    return 0;
}
