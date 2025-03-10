/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:55:14 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/10 13:25:35 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**copy_environ(t_env **env)
{
	char	**array;
	char	*temp;
	t_env	*ptr;
	int		i;

	array = (char **)malloc(sizeof(*array) * (ft_list_size(*env) + 1));
	if (array == NULL)
		return (NULL);
	ptr = *env;
	i = 0;
	while (ptr)
	{
		temp = ft_strjoin(ptr->value, "=");
		if (ft_strlen(ptr->result))
			array[i] = ft_strjoin(temp, ptr->result);
		else
			array[i] = ft_strjoin(temp, "''");
		free(temp);
		if (!array[i])
			free_array(array, i);
		ptr = ptr->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	print_export(t_env **env)
{
	char	**temp;
	int		j;

	temp = copy_environ(env);
	sort_env_alphabetically(temp);
	j = 0;
	while (temp[j])
	{
		printf("%s\n", temp[j]);
		j++;
	}
	ft_free(temp);
	return (0);
}
