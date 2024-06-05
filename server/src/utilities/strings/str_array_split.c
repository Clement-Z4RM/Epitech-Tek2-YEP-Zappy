/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** str array split
*/

#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

/**
* @brief check if it's a new word
* @param str: string to check
* @param in_word: pointer to a flag
* @param separator: separator
* @return 1 if it's a new word, 0 otherwise
**/
static bool compare_with_separator(const char c, char *separator)
{
    for (int i = 0; separator[i]; i++) {
        if (c == separator[i])
            return true;
    }
    return false;
}

int add_count(const char *str, int *in_word, char *separator)
{
    if (compare_with_separator(*str, separator)){
        *in_word = 0;
    } else if (*in_word == 0) {
        *in_word = 1;
        return 1;
    }
    return 0;
}

/**
* @brief count number of words separated by space in the string
* @param str: string to check
* @return number of words
**/
int count_words(const char *str, char *separator)
{
    int count = 0;
    int in_word = 0;

    while (*str) {
        count += add_count(str, &in_word, separator);
        str++;
    }
    return count;
}

/**
* @brief Free allocated words
* @param free array of words
* @param i number of words
* @return NULL
**/
char **free_words(char **words, int i)
{
    for (int j = 0; j < i; j++)
        free(words[j]);
    free(words);
    return NULL;
}

/**
* @brief split string into array of string separated by space
* @param str: string to split
* @return array of words or Null in case of error
**/
char **str_array_split(char *str, char *separator)
{
    int num_words = count_words(str, separator);
    char **words = malloc((num_words + 1) * sizeof(char *));
    char *token = strtok(str, separator);
    int i = 0;

    if (str == NULL || words == NULL)
        return NULL;
    while (token != NULL) {
        words[i] = malloc(sizeof(char) * (strlen(token) + 1));
        if (words[i] == NULL) {
            free_words(words, i);
            return NULL;
        }
        strcpy(words[i], token);
        words[i][strlen(token)] = '\0';
        token = strtok(NULL, separator);
        i++;
    }
    words[num_words] = NULL;
    return words;
}
