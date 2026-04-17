#include "player.h"
#include "utils.h"

void inizializza_giocatore(Giocatore *giocatore) {
    giocatore->corsia = 1;       // Inizia nella corsia centrale
    giocatore->km = 0;
    giocatore->punteggio = 0;
    giocatore->vivo = 1;
    giocatore->velocita = 10;    // Velocità iniziale
}

void aggiorna_giocatore(Giocatore *giocatore) {
    // Aggiorna la posizione e la velocità del giocatore
    // Esempio: gestisci input per cambiare corsia
}

void disegna_giocatore(const Giocatore *giocatore) {
    // Disegna il giocatore nella sua posizione corrente
    // Esempio: printf("      [O]      ");
}
