/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:04:58 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/25 15:29:03 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

int	jsh_echo_intermed(char **args, int index)
{
	int	i;
	int	j;

	i = index;
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
	return (i);
}

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
	i = jsh_echo_intermed(args, i);
	print_echo(args, i);
	if (newline)
		printf("\n");
	return (0);
}
