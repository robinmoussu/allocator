/*****************************************************
 * Copyright Grégory Mounié 2008-2013                *
 * This code is distributed under the GLPv3 licence. *
 * Ce code est distribué sous la licence GPLv3+.     *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mem.h"

// Le pool de mémoire contenant toutes les données que l'on va allouer
void *zone_memoire = 0;

// Une zone mémoire (voir explications plus bas)
// La taille minimale alouable est celle d'un pointeur.
union bloc {
    union record *next_record; // Chaine de zone mémoire disponible
    void         *data;        // Les données lorsque la zone est allouée
};

// Le tableau de BUDDY_MAX_INDEX elements pointant sur les zones mémoire libres
// de taille MIN_SIZE_ALLOC * (2 puissance n) (avec n <= BUDDY_MAX_INDEX).
//
// Les blocs allouables ont une taille T(n) = MIN_SIZE_ALLOC * (2 puissance n).
//
// Les blocs allouables de taille T(n) sont regroupés dans une liste dont le
// premier élément est free_space[n].
//
// Si free_space[n] = 0, alors il n'y a pas de blocs de taille T(n) disponible.
// Si free_space[n] = A (avec A une adresse différente de 0), alors le bloc
// situé à l'adresse A est un bloc prêt à être alloué. De même, si le champ
// next_record du bloc situé à l'adresse A pointe vers B (avec B != 0), alors le bloc
// situé à l'adresse B est disponible, et ainsi de suite jusqu'au dernier
// élément de la chaine (dont le champ next_record == 0).
//
// Si un bloc est alloué, alors il ne sera plus présent ni dans le tableau
// free_space, ni dans aucune des sous-chaines. Dans ce cas, seul le champ data
// du bloc devient utile.
union record *free_space = 0;

#define MIN_SIZE_ALLOC sizeof(record)

/* ecrire votre code ici */

int mem_init()
{
    if (!zone_memoire) {
        zone_memoire = (void *) malloc(ALLOC_MEM_SIZE*MIN_SIZE_ALLOC +
                sizeof(record)*BUDDY_MAX_INDEX);
        free_space   = zone_memoire + ALLOC_MEM_SIZE;
    }
    if (zone_memoire == 0) {
        perror("mem_init:");
        return -1;
    }

    // À l'initialisation, seul un bloc de de taille maximal (faisant
    // MIN_SIZE_ALLOC*BUDDY_MAX_INDEX octets) est disponible.
    for(i = 0; i < BUDDY_MAX_INDEX - 2; i++) {
        free_space[i] = (union record *) 0;
    }
    free_space[BUDDY_MAX_INDEX] = zone_memoire;
    return 0;
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

    free(zone_memoire);
    zone_memoire = 0;
    return 0;
}
