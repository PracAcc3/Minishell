/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:26:54 by synoshah          #+#    #+#             */
/*   Updated: 2026/04/16 22:26:54 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_words(char *str)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (str[i] != '\0')
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
        {
            count++;
            while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
                i++;
        }
    }
    return (count);
}

int get_word_length(char *str, int i)
{
    int len;

    len = 0;
    while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
    {
        len++;
        i++;
    }
    return (len);
}

char *allocate_word(char *str, int start, int len)
{
    char    *word;
    int     k;

    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    k = 0;
    while (len > 0)
    {
        word[k] = str[start];
        k++;
        start++;
        len--;
    }
    word[k] = '\0';
    return (word);
}

void free_tokens(char **tokens, int current_j)
{
    int i;

    i = 0;
    while (i < current_j)
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

char **tokenize_input(char *input)
{
    int     words;
    char    **tokens;
    int     i;
    int     j;
    int     len;

    i = 0;
    j = 0;
    words = count_words(input);
    tokens = malloc(sizeof(char *) * (words + 1));
    if (!tokens)
        return (NULL);
    while (input[i] != '\0')
    {
        while (input[i] == ' ' || input[i] == '\t')
            i++;
        if (input[i] != '\0')
        {
            len = get_word_length(input, i);
            tokens[j] = allocate_word(input, i, len);
            if (!tokens[j])
            {
                free_tokens(tokens, j);
                return (NULL);
            }
            i = i + len;
            j++;
        }
    }
    tokens[j] = NULL;
    return (tokens);
}

void free_array(char **array)
{
    int i;

    i = 0;
    if (!array)
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

int main(int ac, char **av)
{
    char    *input;
    char    **tokens;
    int     i;

    (void)ac;
    (void)av;
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            printf("exit\n");
            break ;
        }
        if (input[0] != '\0')
        {
            add_history(input);
            tokens = tokenize_input(input);
            i = 0;
            if (tokens)
            {
                while (tokens[i])
                {
                    printf("Token %d: [%s]\n", i, tokens[i]);
                    i++;
                }
            }
        }
        free(input);
    }
    return (0);
}