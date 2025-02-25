/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:28:38 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/25 16:48:50 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export(void)
{
	extern char	**environ;
	char		**temp;
	int			j;

	temp = copy_environ(environ);
	sort_env_alphabetically(temp);
	j = 0;
	while (temp[j])
	{
		// printf("declare -x %s\n", environ[j]);
		printf("%s\n", temp[j]);
		j++;
	}
	free_array(temp, j);
	return (0);
}

int	update_existing_var(char *var, size_t len)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			environ[i] = strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_new_var(char *var)
{
	char	*new_var;

	if (!ft_strchr(var, '='))
		new_var = ft_strjoin(var, "=''");
	else
		new_var = var;
	return (new_var);
}

char	**ft_new_environ(char *var, char **new_environ, char **environ, int env_size, int i)
{
	char	*new_var;
	
	while (i < env_size)
	{
		new_environ[i] = ft_strdup(environ[i]);
		if (!new_environ[i])
		{
			free_array(new_environ, i);
			return (NULL);
		}
		i++;
	}
	new_var = ft_new_var(var);
	if (!new_var)
		return (NULL);
	new_environ[env_size] = ft_strdup(new_var);
	if (!new_environ[env_size])
	{
		free_array(new_environ, env_size);
		return (NULL);
	}
	free(new_var);
	return (new_environ);
}

int	add_new_var(char *var)
{
	char		**new_environ;
	extern char	**environ;
	size_t		env_size;
	size_t		i;

	env_size = 0;
	while (environ[env_size])
		env_size++;
	if (!(new_environ = (char **)malloc((env_size + 2) * sizeof(char *))))
	{
		perror("memory allocation failed.");
		return (1);
	}
	i = 0;
	new_environ = ft_new_environ(var, new_environ, environ, env_size, i);
	new_environ[env_size + 1] = NULL;
	ft_free(environ);
	environ = new_environ;
	ft_free(new_environ);
	return (0);
}

int	jsh_export(char **args)
{
	char	*equal_sign;
	int		i;
	size_t	len;

	if (!args[1])
		return (print_export());
	else
	{
		i = 1;
		while (args[i])
		{
			equal_sign = ft_strchr(args[i], '=');
			len = equal_sign - args[i];
			if (!update_existing_var(args[i], len))
				add_new_var(args[i]);
			i++;
		}
	}
	return (0);
}
