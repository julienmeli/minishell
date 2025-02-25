/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:01:27 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/25 16:49:27 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_remove_var(char **environ, int index)
{
	char	**new_environ;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	if (!(new_environ = (char **)malloc(i * sizeof(char *))))
	{
		perror("memory allocation failed.");
		return (NULL);
	}
	i = 0;
	while (i < index)
	{
		new_environ[i] = ft_strdup(environ[i]);
		if (!new_environ[i])
		{
			free_array(new_environ, i);
			return (NULL);
		}
		i++;
	}
	while (environ[index + 1])
	{
		new_environ[i] = ft_strdup(environ[index + 1]);
		if (!new_environ[i])
		{
			free_array(new_environ, i);
			return (NULL);
		}
		i++;
		index++;
	}
	new_environ[i] = NULL;
	ft_free(environ);
	return (new_environ);
}

int	jsh_unset(char **args)
{
	extern char	**environ;
	int			i;
	int			k;

	if (!args[1] || args[1] == NULL)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	k = 1;
	while (args[k])
	{
		i = 0;
		while (environ[i])
		{
			if ((ft_strncmp(environ[i], args[k], ft_strlen(args[k])) == 0)
				&& environ[i][ft_strlen(args[k])] == '=')
			{
				environ = ft_remove_var(environ, i);
			}
			i++;
		}
		k++;
	}
	ft_free(environ);
	return (0);
}
