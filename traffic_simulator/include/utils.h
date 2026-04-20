#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "player.h"
#include "obstacles.h"

// Funzioni di utilità generiche
int random_int(int min, int max);
void disegnaSchermo(Giocatore *g, Ostacolo ostacoli[]);

#endif // UTILS_H
