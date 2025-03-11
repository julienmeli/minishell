/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:30:22 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/10 14:13:09 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			if (array[i])
			{
				free(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

int	ft_builtin(t_commands **temp, t_env **env)
{
	char	**args;

	args = (*temp)->command;
	if (!args || args[0] == NULL)
		return (1);
	else if (strcmp(args[0], "cd") == 0)
		return (jsh_cd(args));
	else if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
		/*
		if (change_env != 0)
			ft_free(environ);
		*/
		return (0);
	}
	else if (ft_strcmp(args[0], "echo") == 0)
		return (jsh_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (jsh_pwd());
	else if (ft_strcmp(args[0], "env") == 0)
		return (jsh_env(temp, env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (jsh_export(temp, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (jsh_unset(temp, env));
	else
		return (1);
}
