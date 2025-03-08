/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:01:27 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/07 15:23:04 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_list_remove_if(t_env **begin_list, char *arg, int (*ft_strcmp)())
{
	t_env	*current;

	if (*begin_list == NULL || begin_list == NULL)
		return ;
	current = *begin_list;
	if (ft_strcmp(current->value, arg) == 0)
	{
		*begin_list = current->next;
		free(current->value);
		free(current->result);
		free(current);
		ft_list_remove_if(begin_list, arg, ft_strcmp);
		
	}
	else
	{
		current = *begin_list;
		ft_list_remove_if(&current->next, arg, ft_strcmp);
	}
}

int	jsh_unset(t_commands **temp, t_env **env)
{
	int	i;

	if (!(*temp)->command[1])
		return (1);
	else
	{
		i = 1;
		while ((*temp)->command[i])
		{
			ft_list_remove_if(env, (*temp)->command[i], ft_strcmp);
			i++;
		}
	}
	return (0);
}
