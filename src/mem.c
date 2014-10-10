/*****************************************************
 * Copyright Grégory Mounié 2008-2013                *
 * This code is distributed under the GLPv3 licence. *
 * Ce code est distribué sous la licence GPLv3+.     *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "mem.h"

// Une zone mémoire (voir explications plus bas)
// La taille minimale alouable est celle d'un pointeur sur un autre bloc.
union bloc {
    union bloc *next_record; // Chaine de zone mémoire disponible lorsque la
                             // zone est non allouée
    void       *data;        // Les données lorsque la zone est allouée
};
#define MIN_SIZE_ALLOC sizeof(union bloc)

struct allocated_space {
    uint8_t    memory_pool[ALLOC_MEM_SIZE*MIN_SIZE_ALLOC];    // zone mémoire
                                // disponible pour l'utilisateur
    union bloc free_space[BUDDY_MAX_INDEX]; /*LA TAILLE NE DOIT-ELLE PAS ETRE DE BUDDYMAX_INDEX + 1 ???*/              // zone mémoire
                                // contenant les données utilisées par
                                // l'algorithme d'alocation
};

// allocated_space est le pool de mémoire contenant toutes les données que l'on
// va allouer
//
// Le tableau allocated_space->memory_pool de BUDDY_MAX_INDEX elements pointe
// sur les zones mémoire libres de taille MIN_SIZE_ALLOC * (2 puissance n)
// (avec n <= BUDDY_MAX_INDEX).
//
// Les blocs allouables ont une taille T(n) = MIN_SIZE_ALLOC * (2 puissance n).
//
// Les blocs allouables de taille T(n) sont regroupés dans une liste dont le
// premier élément est allocated_space->free_space[n].
//
// Si free_space[n] = 0, alors il n'y a pas de blocs de taille T(n) disponible.
// Si free_space[n] = A (avec A une adresse différente de 0), alors le bloc
// situé à l'adresse A est un bloc prêt à être alloué. De même, si le champ
// next_record du bloc situé à l'adresse A pointe vers B (avec B != 0), alors le bloc
// situé à l'adresse B est disponible, et ainsi de suite jusqu'au dernier
// élément de la chaine (dont le champ next_record == 0).

// Si un bloc est alloué, alors il ne sera plus présent ni dans le tableau
// memory_space->free_space, ni dans aucune des sous-chaines. Dans ce cas, seul
// le champ data du bloc devient utile.
static struct allocated_space *memory_space = 0;

int mem_init()
{
    if (!memory_space) {
        memory_space = (void *) malloc( sizeof(struct allocated_space) );
    }
    if (memory_space == 0) {
        perror("mem_init:");
        return -1;
    }

    // À l'initialisation, seul un bloc de de taille maximal (faisant
    // MIN_SIZE_ALLOC*(2 puissance BUDDY_MAX_INDEX) octets) est disponible.
    for(int i = 0; i < BUDDY_MAX_INDEX - 2; i++) {
        memory_space->free_space[i].next_record = 0;
    }
    memory_space->free_space[BUDDY_MAX_INDEX] = *((union bloc *) &(memory_space->memory_pool));
    return 0;//l'index ici ne doit it pas être BUDDY_MAX_INDEX - 1 ??? (dans le cas ou la taille de Free_space est de BUDDY_MAX_INDEX et non de BUDDY_MAX_INDEX+1)
}

void *mem_alloc(unsigned long size)
{
    /*  ecrire votre code ici */
    return 0;
}

int mem_free(void *ptr, unsigned long size)
{
    /* ecrire votre code ici */
    return 0;
}


int mem_destroy()
{
    /* ecrire votre code ici */

    free(memory_space);
    memory_space = 0;
    return 0;
}
