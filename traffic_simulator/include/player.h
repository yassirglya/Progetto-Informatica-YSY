#ifndef PLAYER_H
#define PLAYER_H

// Struttura per rappresentare il giocatore
typedef struct {
    int corsia;      // 0,1,2 (3 corsie)
    int km;
    int punteggio;
    int vivo;
    int velocita;
} Giocatore;

// Funzioni per la gestione del giocatore
void inizializza_giocatore(Giocatore *giocatore);
void aggiorna_giocatore(Giocatore *giocatore);
void disegna_giocatore(const Giocatore *giocatore);

#endif // PLAYER_H
