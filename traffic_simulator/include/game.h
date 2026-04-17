#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enum per rappresentare i diversi stati del gioco
typedef enum { MENU, GIOCO, PAUSA, GAMEOVER, RECORD } StatoGioco;

// Struttura per rappresentare il giocatore.
// Viene modificata in 'aggiorna_logica' per gestire il movimento (cambio corsia)
// e per aggiornare i km percorsi e il punteggio.
// Il valore 'vivo' diventa 0 in caso di collisione.
typedef struct {
    int corsia;      // 0, 1, 2 (3 corsie)
    long km;
    int punteggio;
    int vivo;
    int velocita;
} Giocatore;

// Struttura per rappresentare un ostacolo
typedef struct {
    int corsia;
    int riga;        // posizione verticale
    char simbolo;    // 'X', '#', '@', etc.
} Ostacolo;

// Struttura per rappresentare un record
typedef struct {
    int km;
    char nome[20];
    int tempo;
} Record;

// Prototipi delle funzioni di gestione del gioco
void inizializza_gioco();
void aggiorna_logica(StatoGioco *statoCorrente, Giocatore *giocatore);
void disegna_schermo(StatoGioco statoCorrente, const Giocatore *giocatore);

// Funzioni per la gestione dei singoli stati
void menuPrincipale(StatoGioco *statoCorrente);
void gameLoop(Giocatore *giocatore);

// Prototipi delle funzioni dei moduli
void inizializza_giocatore(Giocatore *giocatore);
void disegna_giocatore(const Giocatore *giocatore);
void aggiorna_ostacoli();
void disegna_ostacoli();

#endif // GAME_H
