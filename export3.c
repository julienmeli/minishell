/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:28:38 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/27 17:21:18 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
*/

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

char	**ft_new_environ(char *var, char **environ, int env_size, int i)
{
	char	*new_var;
	char	**new_environ;

	if (!(new_environ = (char **)malloc((env_size + 2) * sizeof(char *))))
        {
                perror("memory allocation failed.");
                return (NULL);
        }
	printf("%p\n", (void *)new_environ); 	
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
	//environ = new_environ;
	/*
	i = 0;
	//env_size = ft_size_env(environ);
	while (i < env_size)
	{
		free(environ[i]);
		i++;
	}
	*/
	free(environ);
	environ = new_environ;
	/*
	while (env_size >= -1)
	{
		//free(new_environ[env_size]);
		free(new_environ[env_size + 1]);
		env_size--;
	}
	*/
	new_environ = NULL;
	//i = 0;
	//free(new_environ[i]);
	//new_environ[env_size] = NULL;
	free(new_environ);
	/*
        while (env_size >= 0)
        {
                //free(new_environ[env_size]);
                free(new_environ[env_size]);
                env_size--;
        }
	*/
	//ft_free(new_environ);
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
	//free(environ);
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
