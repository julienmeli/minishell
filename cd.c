/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:44:10 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/25 15:19:01 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_root_directory(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "OLDPWD=", 7) == 0)
			return (ft_substr(environ[i], 7, ft_strlen(environ[i]) - 8 + 1));
		i++;
	}
	return (NULL);
}

int	jsh_cd(char **args)
{
	char	*root;

	if (!args[1] && args[1] == NULL)
	{
		root = get_root_directory();
		if (chdir(root) != 0)
			perror("cd:root");
		else
		{
			free(root);
			return (0);
		}
		return (1);
	}
	else if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
