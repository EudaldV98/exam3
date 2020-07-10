/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 14:20:42 by jvaquer           #+#    #+#             */
/*   Updated: 2020/07/10 14:21:28 by jvaquer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int ft_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        ++i;
    return (i);
}
int ft_naze(char *str)
{
    write(2, str, ft_strlen(str));
    return (1);
}
char *readline(struct __sFILE *fd)
{
    int i = 1;
    int p = 0;
    char *line;
    line = malloc(10000000 * sizeof(char));
    memset(line, 0, 10000000);
    while (i == 1)
    {
        i = fread(&line[p], 1, 1, fd);
        if (i == 0 && p == 0)
        {
            free(line);
            return(NULL);
        }
        if (line[p] == '\n')
            return (line);
        ++p;
    }
    return (line);
}
int ft_atoi(char *str)
{
    int i = 0;
    int res = 0;
    float tes = 0;
    while (str[i] == ' ')
        ++i;
    while (str[i] == '+' || str[i] == '-')
        ++i;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        ++i;
    }
    if (str[i] == '.')
    {
        ++i;
        while (str[i] >= '0' && str[i] <= '9')
        {
            tes = tes / 10 + (str[i] - '0');
            ++i;
        }
        res = res + (int)tes;
    }
    return (res);
}
int first_line(int *w_x, int *w_y, int *character, char *line)
{
    int i = 0;
    *w_x = ft_atoi(line);
    while (line[i] == ' ')
        ++i;
    while (line[i] >= '0' && line[i] <= '9')
        ++i;
    *w_y = ft_atoi(&line[i]);
    while (line[i] == ' ')
        ++i;
    while (line[i] >= '0' && line[i] <= '9')
        ++i;
    if (line[i] != ' ')
        return (1);
    while (line[i] == ' ')
        ++i;
    *character = line[i];
    if ((line[i + 1] != '\n' && line[i + 1] != '\0') || *w_x <= 0 || *w_y <= 0 || *w_x >= 300 || *w_y >= 300 || *character == 0)
        return (1);
    return (0);
}
int all_line(int *is, int *w_x, int *w_y, int *wid, int *len, int *character, char *line)
{
    int i = 0;
    while (line[i] == ' ')
        ++i;
    *is = line[i];
    ++i;
    while (line[i] == ' ')
        ++i;
    *w_x = ft_atoi(&line[i]);
    while (line[i] == ' ')
        ++i;
    while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
        ++i;
    *w_y = ft_atoi(&line[i]);
    while (line[i] == ' ')
        ++i;
    while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
        ++i;
    *wid = ft_atoi(&line[i]);
    while (line[i] == ' ')
        ++i;
    while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
        ++i;
    *len = ft_atoi(&line[i]);
    while (line[i] == ' ')
        ++i;
    while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
        ++i;
    while (line[i] == ' ')
        ++i;
    *character = line[i];
    if ((line[i + 1] != '\n' && line[i + 1] != '\0') || *w_x <= -1 || *w_y <= -1 || *w_x >= 300 || *w_y >= 300 || *character == -1 || *character == '\n')
        return (1);
    return (0);
}
void ft_show_tab(int w_x, int w_y, char **tab)
{
    int i = 0;
    int j = 0;
    while (i < w_x)
    {
        j = 0;
        while (j < w_y)
        {
            write(1, &tab[i][j], 1);
            ++j;
        }
        printf("\n");
        ++i;
    }
}
void ft_fill_tab_big(int w_x, int w_y, char **tab, int x, int y, char character, int lenx, int leny)
{
    int save_y = w_y;
    int bw_x = w_x;
    int bw_y = w_y;
    while (w_x < (x + bw_x) && w_x < lenx)
    {
        w_y = save_y;
        while (w_y < (y + bw_y) && w_y < leny)
        {
            //printf("%d   %d\n", w_x, w_y);
            tab[w_x][w_y] = character;
            ++w_y;
        }
        ++w_x;
    }
}
void ft_fill_tab_small(int w_x, int w_y, char **tab, int x, int y, char character, int lenx, int leny)
{
    int save_y = w_y;
    int bw_x = w_x;
    int bw_y = w_y;
    while (w_x < (x + bw_x) && w_x < lenx)
    {
        w_y = save_y;
        while (w_y < (y + bw_y) && w_y < leny)
        {
            //printf("%d   %d\n", w_x, w_y);
            if (w_x == bw_x || w_y == bw_y || w_x == (x + bw_x - 1) || w_y == (y + bw_y - 1))
                tab[w_x][w_y] = character;
            ++w_y;
        }
        ++w_x;
    }
}
char **mal_tab(int x, int y)
{
    char **tab;
    int i = 0;
    tab = malloc(x * sizeof(char *));
    while (i < x)
    {
        tab[i] = malloc(y * sizeof(char));
        ++i;
    }
    return (tab);
}
int main(int argc, char **argv)
{
    struct __sFILE *fd;
    int w_x = -1;
    int w_y = -1;
    int startx;
    int starty;
    int wid = 0;
    int len = 0;
    int is;
    int character = 0;
    char *line;
    char **tab;
    if (argc != 2)
        return (ft_naze("Wrong number of arg\n"));
    fd = fopen(argv[1], "r");
    if (fd == NULL)
        return (ft_naze("bad file\n"));
    line = readline(fd);
    if (line == NULL)
        return (ft_naze("bad file\n"));
    if (1 == first_line(&w_x, &w_y, &character, line))
        return(ft_naze("bad file\n"));
    free(line);
    tab = mal_tab(w_x, w_y);
    //printf("%d  %d  %c\n", w_x, w_y, character);
    ft_fill_tab_big(0, 0, tab, w_x, w_y, character, w_x, w_y);
    while (NULL != (line = readline(fd)))
    {
        is = -1;
        startx = -1;
        starty = -1;
        wid = -1;
        len = -1;
        character = -1;
        if (1 == all_line(&is, &startx, &starty, &wid, &len, &character, line))
            return(ft_naze("bad file\n"));
        if (is != 'r' && is != 'R')
            return(ft_naze("bad file\n"));
        if (is == 'R')
            ft_fill_tab_big(startx, starty, tab, wid, len, character, w_x, w_y);
        else
            ft_fill_tab_small(startx, starty, tab, wid, len, character, w_x, w_y);
        free(line);
    }
    ft_show_tab(w_x, w_y, tab);
    return (0);
}
