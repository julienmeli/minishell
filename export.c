/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:55:14 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/26 16:37:55 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_strings(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

void	sort_env_alphabetically(char **array)
{
	int	i;
	int	j;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
				swap_strings(&array[i], &array[j]);
			j++;
		}
		i++;
	}
}

void	free_array(char **array, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**copy_environ(char **environ)
{
	char	**array;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	array = (char **)malloc(sizeof(*array) * (i + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		array[i] = ft_strdup(environ[i]);
		if (!array[i])
			free_array(array, i);
		i++;
	}
	array[i] = NULL;
	return (array);
}

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
		printf("%s\n", temp[j]);
		j++;
	}
	free_array(temp, j);
	return (0);
}

/*
char	*ft_strjoin(char *str, char *buf)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str) + ft_strlen(buf);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	j = 0;
	while (buf[j])
	{
		result[i + j] = buf[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

void	ft_realloc(char **environ, int n)
{
	char	**temp;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	temp = (char **)malloc(sizeof(*environ) * (i + n));
	if (!temp)
		return ;
	i = 0;
	while (environ[i])
	{
		temp[i] = ft_strdup(environ[i]);
		i++;
	}
	while (i < n)
		temp[i++] = NULL;
	environ = temp;
	free(temp);
}

void	add_var_to_env(char **environ, char *arg)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		i++;
	}
	ft_realloc(environ, 1);
	environ[i] = ft_strdup(arg);
	puts("here");
}

int	check_if_var_exists(char **environ, char *arg)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	str = ft_substr(arg, 0, i);
	j = 0;
	while (environ[j])
	{
		if (ft_strncmp(environ[j], str, i) == 0)
			return (1);
		j++;
	}
	return (0);
}

int	get_environ_index(char ***environ, char *arg)
{
	int	len;
	int	i;

	len = 0;
	while (arg[len] && (ft_isalnum(arg[len]) > 0) &&  arg[len] != '=')
		len++;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(*environ[i], arg, len))
			return (i);
		i++;
	}
	return (-1);
}

void	replace_existing_var(char ***environ, char *arg)
{
	char	*replacement;
	int		index;
	int		j;

	index = get_environ_index(environ, arg);
	if (index < 0)
		return ;
	replacement = ft_strchr(arg, '=');
	j = 0;
	while (arg[j])
	{
		*environ[index][j] = arg[j];
		j++;
	}
}

int	jsh_export(char **args)
{
	int			i;
	int			j;
	extern char	**environ;
	char		*equal_sign;
	char		**temp;

	temp = copy_environ(environ);
	i = 1;
	if (!(args[i]))
	{
		sort_env_alphabetically(temp);
		j = 0;
		while (temp[j])
		{
			//printf("declare -x %s\n", environ[j]);
			printf("%s\n", temp[j]);
			j++;
		}
		return (0);
	}
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (!equal_sign)
		{
			//puts("not ready yet");
			add_var_to_env(environ, args[i]);
			return (1);
		}
		else
		{
			if (check_if_var_exists(environ, args[i]))
				replace_existing_var(&environ, args[i]);
			else
			{
				//puts("Ready? Nope.");
				add_var_to_env(environ, args[i]);
			}
		}
		i++;
	}
	return (0);
}
*/
