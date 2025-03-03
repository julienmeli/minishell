/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:30:22 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/03 17:38:10 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_builtin(char **args)
{
	static	int	change_env;
	//extern char	**environ;

	puts("hello");
	if (!args || args[0] == NULL)
		return (1);
	else if (strcmp(args[0], "cd") == 0)
		return (jsh_cd(args));
	else if (strcmp(args[0], "exit") == 0)
	{
		/*
		if (change_env != 0)
			ft_free(environ);
		*/
		return (0);
	}
	else if (ft_strcmp(args[0], "echo") == 0)
		return(jsh_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (jsh_pwd());
	else if (ft_strcmp(args[0], "env") == 0)
        	return (jsh_env());
	else if (ft_strcmp(args[0], "export") == 0)
        	return (jsh_export(args, &change_env));
	else if (ft_strcmp(args[0], "unset") == 0)
        	return (jsh_unset(args));
	else
		return (1);
}
