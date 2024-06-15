/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** free double tab
*/

#include "stdlib.h"

void free_double_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i]; i++)
        if (tab[i])
            free(tab[i]);
    free(tab);
}
