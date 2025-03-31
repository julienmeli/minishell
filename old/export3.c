/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:28:38 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/05 16:11:00 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	update_existing_var(char *var, size_t len)
{
	int			i;
	extern char	**environ;
	char		*new_var;
	
	i = 0;
	//printf("%zu\n", len);
	//puts("b");
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			if (!ft_strchr(var, '='))
			{
				new_var = ft_strjoin(var, "=''");
				environ[i] = ft_strdup(new_var);
			}
			else
				environ[i] = ft_strdup(var);
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
	{
		new_var = ft_strdup(var);
		return(new_var);
	}
	return (new_var);
}

char	**ft_new_environ(char *var, char **environ, int env_size, int i)
{
	char	*new_var;
	char	**new_environ;

	if (!(new_environ = (char **)malloc((env_size + 2) * sizeof(char *))))
        {
                perror("memory allocation failed.");
                return (NULL);
        }
	//printf("%p\n", (void *)new_environ); 	
	while (i < env_size)
	{
		new_environ[i] = ft_strdup(environ[i]);	
		if (!new_environ[i])
		{
			free_array(new_environ, i);
			return (NULL);
		}
		
		//free(environ[i]);
		i++;
	}
	new_var = ft_new_var(var);
	if (!new_var)
	{
		free_array(new_environ, i);
		return (NULL);
	}
	new_environ[env_size] = ft_strdup(new_var);
	if (!new_environ[env_size])
	{
		free(new_var);
		free_array(new_environ, env_size);
		return (NULL);
	}
	free(new_var);
	new_environ[env_size + 1] = NULL;
	free(environ);
	environ = new_environ;
	new_environ = NULL;
	free(new_environ);
	return (environ);
}

int	add_new_var(char *var)
{
	extern char	**environ;
	size_t		env_size;
	size_t		i;

	env_size = 0;
	while (environ[env_size])
		env_size++;
	i = 0;
	environ = ft_new_environ(var, environ, env_size, i);
	environ[env_size + 1] = NULL;
	return (0);
}

int	jsh_export(char **args, int *change_env)
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
			if (!ft_strchr(args[i], '='))
				len = ft_strlen(args[i]);
			else
				len = equal_sign - args[i];
			if (update_existing_var(args[i], len) == 0)
			{
				add_new_var(args[i]);
				(*change_env)++;
			}
			i++;
		}
	}
	return (0);
}
