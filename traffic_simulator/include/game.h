#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enum per rappresentare i diversi stati del gioco
typedef enum { MENU, GIOCO, PAUSA, GAMEOVER, RECORD, ESCI } StatoGioco;

typedef struct {
    int corsia;
    long km;
    int punteggio;
    int vivo;
    int velocita;
} Giocatore;

typedef struct {
    int corsia;
    int riga;
    char simbolo;
} Ostacolo;

typedef struct {
    int km;
    char nome[20];
    int tempo;
} Record;

// Funzioni di gestione del gioco
void aggiorna_logica(StatoGioco *statoCorrente, Giocatore *giocatore);
void menuPrincipale(StatoGioco *statoCorrente);
void mostraGameOver(StatoGioco *statoCorrente, const Giocatore *giocatore);
void gameLoop(StatoGioco *statoCorrente, Giocatore *giocatore);

// Funzioni dei moduli
void inizializza_giocatore(Giocatore *giocatore);
void gestisciInput(Giocatore *giocatore);
void inizializza_ostacoli();
void aggiorna_ostacoli();
const Ostacolo* get_ostacoli();
void disegnaSchermo(Giocatore *g, Ostacolo ostacoli[]);

#endif // GAME_H
