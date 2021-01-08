/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@42lyon.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:37:54 by gbaud             #+#    #+#             */
/*   Updated: 2021/01/08 17:06:53 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>


int main(int ac, char const *av[]) {
    for (int i = 1; i < ac; i++)
        dprintf(1, "[%s]\n", av[i]);
    dprintf(1, "========\n");
    return (0);
}
