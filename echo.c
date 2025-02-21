/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:04:58 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/21 12:11:01 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jsh_echo(char **args)
{
	int	i;
	int	newline;
	int	j;

	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		j = 1;
		while (args[1][j] && args[1][j] == 'n')
		{
			j++;
		}
		if (args[1][j] == '\0')
		{
			newline = 0;
			i++;
		}
	}
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
        {
                j = 1;
                while (args[i][j] && args[i][j] == 'n')
                {
                        j++;
                }
                if (args[i][j] == '\0')
                        i++;
		else
			break ;
        }
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
