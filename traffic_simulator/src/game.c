#include "game.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
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
int _getch() {
    return getchar();
}
#endif

// Funzione per la schermata di Game Over
void mostraGameOver(StatoGioco *statoCorrente, const Giocatore *giocatore) {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");
    #endif

    printf("\n\n");
    printf("  GGGGGGGGGGGGG                  AAA              MMMMMMMM               MMMMMMMM EEEEEEEEEEEEEEEEEEEEEE     OOOOOOOOO     VVVVVVVV           VVVVVVVV EEEEEEEEEEEEEEEEEEEEEE RRRRRRRRRRRRRRRRR   \n");
    printf(" GGG::::::::::::G               AAAAA             M:::::::M             M:::::::M E::::::::::::::::::::E   OO:::::::::OO   V::::::V           V::::::V E::::::::::::::::::::E R::::::::::::::::R  \n");
    printf("G:::::GGGGGGGG::::G            A:::::A            M::::::::M           M::::::::M E::::::::::::::::::::E OO:::::::::::::OO V::::::V           V::::::V E::::::::::::::::::::E R::::::RRRRRR:::::R \n");
    printf("G:::::G     GGGGGG           A:::::::A           M:::::::::M         M:::::::::M EE::::::EEEEEEEEE     O:::::OOO:::::O      V::::::V         V::::::V  EE::::::EEEEEEEEE    RR:::::R     R:::::R\n");
    printf("G:::::G                      A:::::::::A          M::::::::::M       M::::::::::M   E:::::E               O::::O   O::::O   V:::::V       V:::::V      E:::::E              R:::::R     R:::::R\n");
    printf("G:::::G    GGGGGGGGGG       A:::::A:::::A         M:::::::::::M     M:::::::::::M   E:::::E               O::::O   O::::O    V:::::V     V:::::V       E:::::E              R:::::R     R:::::R\n");
    printf("G:::::G    G::::::::G      A:::::A A:::::A        M:::::::M::::M   M::::M:::::::M   E::::::EEEEEEEEEE     O::::O   O::::O     V:::::V   V:::::V        E::::::EEEEEEEEEE    R:::::RRRRRR:::::R \n");
    printf("G:::::G    GGGGG::::G     A:::::A   A:::::A       M::::::M M::::M M::::M M::::::M   E:::::::::::::::E     O::::O   O::::O      V:::::V V:::::V         E:::::::::::::::E    R:::::::::::::RR  \n");
    printf("G:::::G        G::::G    A:::::A     A:::::A      M::::::M  M::::M::::M  M::::::M   E:::::::::::::::E     O::::O   O::::O       V:::::V:::::V          E:::::::::::::::E    R:::::RRRRRR:::::R \n");
    printf("G:::::G    G GGG::::G   A:::::AAAAAAAAA:::::A     M::::::M   M:::::::M   M::::::M   E::::::EEEEEEEEEE     O::::O   O::::O        V:::::::::V           E::::::EEEEEEEEEE    R:::::R     R:::::R\n");
    printf("G:::::G    G:::::G    A:::::::::::::::::::::A    M::::::M    M:::::M    M::::::M   E:::::E               O::::O   O::::O         V:::::::V             E:::::E              R:::::R     R:::::R\n");
    printf("G:::::G     GGGGGG   A:::::A         A:::::A   M::::::M     MMMMM     M::::::M EE::::::EEEEEEEEEEE     O:::::OOO:::::O          V:::::V                EE::::::EEEEEEEEEEE   RR:::::R     R:::::R\n");
    printf("G:::::GGGGGGGG::::G  A:::::A           A:::::A  M::::::M               M::::::M E::::::::::::::::::::E OO:::::::::::::OO           V:::V              E::::::::::::::::::::E R::::::R     R:::::R\n");
    printf(" GGG::::::::::::G A:::::A             A:::::A M::::::M               M::::::M E::::::::::::::::::::E   OO:::::::::OO              V:V                 E::::::::::::::::::::E R::::::R     R:::::R\n");
    printf("  GGGGGGGGGGGG    AAAAAAA               AAAAAAAMMMMMMMM               MMMMMMMM EEEEEEEEEEEEEEEEEEEEEE     OOOOOOOOO                 V                 EEEEEEEEEEEEEEEEEEEEEE RRRRRRRR     RRRRRRR\n");
    printf("\n\n");

    printf("\tRecord di Chilometri: %ld\n\n", giocatore->km);
    printf("\tPremi 'R' per rigiocare o 'M' per tornare al menu principale.\n");

    char scelta = ' ';
    while (scelta != 'r' && scelta != 'R' && scelta != 'm' && scelta != 'M') {
        if (_kbhit()) {
            scelta = _getch();
        }
    }

    if (scelta == 'r' || scelta == 'R') {
        *statoCorrente = GIOCO;
    } else {
        *statoCorrente = MENU;
    }
}

void gameLoop(StatoGioco *statoCorrente, Giocatore *giocatore) {
    inizializza_giocatore(giocatore);
    inizializza_ostacoli();

    while (*statoCorrente == GIOCO) {
        if (giocatore->vivo) {
            gestisciInput(giocatore);
            aggiorna_ostacoli();

            // Controllo collisioni
            const Ostacolo *ostacoli = get_ostacoli();
            for (int i = 0; i < MAX_OSTACOLI; i++) {
                if (ostacoli[i].riga == RIGA_GIOCATORE && ostacoli[i].corsia == giocatore->corsia) {
                    giocatore->vivo = 0; // Il giocatore è morto!
                    break;
                }
            }

            if (giocatore->vivo) {
                 giocatore->km++; // Incrementa i km
            }
            
            disegnaSchermo(giocatore, get_ostacoli());

            // Rallenta il gioco per renderlo giocabile
            #ifdef _WIN32
                Sleep(100 - giocatore->velocita > 0 ? 100 - giocatore->velocita : 10);
            #else
                usleep((100 - giocatore->velocita > 0 ? 100 - giocatore->velocita : 10) * 1000);
            #endif

        } else {
            *statoCorrente = GAMEOVER;
        }
    }
}
