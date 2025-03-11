/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:05:54 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/10 16:04:51 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	equal_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	arg_is_not_alphanum(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str) == 0 && *str != '=')
			return (1);
		str++;
	}
	return (0);
}

int	len_before_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	ft_list_size(t_env *begin_list)
{
	int		size;
	t_env	*current;

	size = 0;
	current = begin_list;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

void	ft_env_push_back(t_env **begin_list, char *data)
{
	t_env	*new_elem;
	t_env	*current;

	new_elem = ft_create_var(data);
	if (*begin_list == NULL)
	{
		*begin_list = new_elem;
	}
	else
	{
		current = *begin_list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_elem;
	}
}
