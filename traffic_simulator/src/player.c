#include "player.h"
#include "obstacles.h"
#include <stdio.h>

void inizializza_giocatore(Giocatore *g) {
    g->corsia = 1;      // Inizia nella corsia centrale
    g->km = 0;
    g->punteggio = 0;
    g->vivo = 1;
    g->velocita = 60; // Velocità iniziale
}

void gestisciInput(Giocatore *g) {
    if (_kbhit()) { // Controlla se è stato premuto un tasto
        char tasto = _getch(); // Legge il tasto premuto

        switch (tasto) {
            case 'a':
            case 'A':
                if (g->corsia > 0) { // Controlla che non sia nella corsia più a sinistra
                    g->corsia--;
                }
                break;
            case 'd':
            case 'D':
                if (g->corsia < NUM_CORSIE - 1) { // Controlla che non sia nella corsia più a destra
                    g->corsia++;
                }
                break;
            case 'p':
            case 'P':
                printf("PAUSA. Premi un tasto per riprendere...");
                while (!_kbhit()) { // Rimane in pausa finché non viene premuto un tasto
                    // Aspetta
                }
                _getch(); // Consuma il tasto premuto per riprendere
                break;
        }
    }
}
