irt#include "game.h"
#include "obstacles.h"
#include <stdio.h>

// Prototipo della nuova funzione di collisione
void controllaCollisioni(Giocatore *giocatore);

// Funzione per inizializzare il gioco e il giocatore
void inizializza_gioco(Giocatore *giocatore) {
    srand(time(NULL));
    inizializza_giocatore(giocatore);
    inizializza_ostacoli(); // Inizializziamo anche gli ostacoli
}

// Gestisce l'aggiornamento della logica di gioco
void aggiorna_logica(StatoGioco *statoCorrente, Giocatore *giocatore) {
    if (giocatore->vivo) {
        gameLoop(giocatore);
    } else {
        *statoCorrente = GAMEOVER;
    }
}

// Gestisce il disegno di tutti gli elementi a schermo
void disegna_schermo(StatoGioco statoCorrente, const Giocatore *giocatore) {
    // Pulisce lo schermo
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    switch (statoCorrente) {
        case MENU:
            break; // Il menu viene stampato altrove
        case GIOCO:
            disegna_ostacoli();
            disegna_giocatore(giocatore); // Disegniamo il giocatore dopo gli ostacoli
            break;
        case GAMEOVER:
            printf("\n\n          GAME OVER          \n\n");
            printf("Punteggio finale: %d\n", giocatore->punteggio);
            printf("Km percorsi: %ld\n", giocatore->km);
            // Qui si potrebbe attendere un input per tornare al menu
            break;
        default:
            break;
    }
}

// Menu principale
void menuPrincipale(StatoGioco *statoCorrente) {
    printf("========== GIOCO DI CORSA ==========\n");
    printf("1. Inizia Partita\n2. Record\n3. Esci\n");
    printf("Scelta: ");

    int scelta;
    if (scanf("%d", &scelta) == 1) {
        switch (scelta) {
            case 1:
                *statoCorrente = GIOCO;
                inizializza_gioco(NULL); // Resetta lo stato per una nuova partita
                break;
            case 2: *statoCorrente = RECORD; break;
            case 3: exit(0); break;
        }
    }
}

// Loop di gioco principale
void gameLoop(Giocatore *giocatore) {
    // 1. Aggiorna la posizione degli ostacoli
    aggiorna_ostacoli();

    // 2. Controlla le collisioni
    controllaCollisioni(giocatore);

    // 3. (Futuro) Leggi input del giocatore

    // 4. (Futuro) Aggiorna punteggio e km
    if (giocatore->vivo) {
        giocatore->km++;
        giocatore->punteggio += 10; // Esempio
    }
}

// Controlla se il giocatore ha colpito un ostacolo.
void controllaCollisioni(Giocatore *giocatore) {
    const Ostacolo* ostacoli = get_ostacoli(); // Ottieni l'array di ostacoli

    for (int i = 0; i < MAX_OSTACOLI; ++i) {
        // Verifica solo gli ostacoli attivi
        if (ostacoli[i].riga == RIGA_GIOCATORE) { // L'ostacolo è alla stessa 'altezza' del giocatore
            if (ostacoli[i].corsia == giocatore->corsia) { // L'ostacolo è nella stessa corsia del giocatore
                giocatore->vivo = 0; // Collisione! Il giocatore non è più vivo.
                // (Opzionale) Aggiungi un suono o un effetto visivo qui
                break; // Inutile controllare altri ostacoli
            }
        }
    }
}
