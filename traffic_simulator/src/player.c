#include "player.h"
#include <stdio.h>

// Su Windows, usa conio.h per l'input non bloccante
#ifdef _WIN32
#include <conio.h>
#else
// Su sistemi non-Windows (Linux, macOS), usa una combinazione di
// termios.h e fcntl.h per ottenere un comportamento simile
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// Funzione per l'input non bloccante su sistemi non-Windows
int _kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Funzione per leggere un carattere senza aspettare Invio
int _getch() {
    return getchar();
}

#endif

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
