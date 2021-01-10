/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:59:05 by gbaud             #+#    #+#             */
/*   Updated: 2021/01/10 13:24:57 by gbaud            ###   ########lyon.fr   */
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

void sub(char **argv, char **av, int i, int j) {
	int k = 0;
	while (i < j)
		argv[k++] = av[i++];
	argv[k] = NULL;
}

int cd(char **av, int len) {
    if (len != 2)
        return (put_err(ERR_CD_ARG, NULL));
    if (chdir(av[1]))
        return (put_err(ERR_CD_DIR, av[1]));
    return (0);
}

int main(int ac, char **av, char **env) {
	int i=1,j,k,l;
	while (i < ac) {
		j=i, k=i, l=i;
		while (j < ac && strcmp(av[j], ";")) // j = limite semicolon
			j++;
		int   p[2];
		pid_t pid;
		int   fd_in = 0;
		while (k < j) { // Tant qu'il y a des pipes
			l=k;
			while (l < j && strcmp(av[l], "|")) // [k - l] -> troncon cmd + arg
				l++;
			char *argv[l - k + 1];
			sub(argv, av, k, l);
			if (!strcmp(argv[0], "cd"))
				cd(argv, l-k);
			else {
				pipe(p);
				if ((pid = fork()) == -1)
					return (put_err(ERR_FATAL, NULL));
				else if (pid == 0) {
					dup2(fd_in, 0);
					if (l < j)
						dup2(p[1], 1);
					close(p[0]);
					if (execve(argv[0], argv, env))
						put_err(ERR_EXEC, argv[0]);
					exit(EXIT_FAILURE);
				} else {
					waitpid(pid, NULL, 0);
					close(p[1]);
					fd_in = p[0];
        		}
			}
			k=l+1;
		}
		i=j+1;
	}
	return (0);
}
