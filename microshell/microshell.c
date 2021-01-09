/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:59:05 by gbaud             #+#    #+#             */
/*   Updated: 2021/01/09 18:12:46 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

#define ERR_FATAL "error: fatal\n"
#define ERR_EXEC "error: cannot execute "
#define ERR_CD_ARG "error: cd: bad arguments\n"
#define ERR_CD_DIR "error: cd: cannot change directory to "

int ft_strlen(char *str) {
	int i = 0;
	while (str[i++]);
	return (i);
}

int put_err(char *err, char *path) {
	write(2, err, ft_strlen(err));
	if (path) {
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
	return (1);
}

int main(int ac, char **av, char **env) {
	pid_t pid;

	if ((pid = fork()) < 0)
		return (put_err(ERR_FATAL, NULL));
	else if (pid == 0) {
		if (execve(av[1], &av[1], env))
			put_err(ERR_EXEC, av[1]);
	} else {
		waitpid(pid, NULL, 0);
	}
	return (0);
}
