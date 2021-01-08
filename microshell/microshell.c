/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:37:54 by gbaud             #+#    #+#             */
/*   Updated: 2021/01/08 18:34:11 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ERR_CD_ARG "error: cd: bad arguments\n"
#define ERR_CD_MOV "error: cd: cannot change directory to "
#define STDERR 2

int ft_strlen(char *str) {
    int i = 0;
    while (str[i++]);
    return (i);
}

int put_error(char *err, char *path) {
    write(STDERR, err, ft_strlen(err));
    if (path) {
        write(STDERR, path, ft_strlen(path));
        write(STDERR, "\n", 1);
    }
    return (1);
}

int cd(char **path, int s, int e) {
    int i = s;
    while (i < e && strcmp(path[i], ";")) i++;
    if (i - s != 2)
        return (put_error(ERR_CD_ARG, NULL));
    if (chdir(path[i - 1]))
        return (put_error(ERR_CD_MOV, path[i - 1]));
    return (0);
}

int main(int ac, char **av) {
    for (int i = 1; i < ac; i++)
        dprintf(1, "[%s]\n", av[i]);
    dprintf(1, "========\n");

    cd(av, 1, ac);

    return (0);
}
