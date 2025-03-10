/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:04:39 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/10 13:25:37 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	index_existing_var(char *arg, t_env **env)
{
	int		len;
	int		i;
	t_env	*ptr;

	if (ft_strchr(arg, '='))
	{
		len = 0;
		while (arg[len] && (arg[len] != '='))
			len++;
	}
	else
		len = ft_strlen(arg);
	i = 0;
	ptr = *env;
	while (ptr)
	{
		if (ft_strncmp(ptr->value, arg, len) == 0)
			return (i);
		i++;
		ptr = ptr->next;
	}
	return (-1);
}

int	equal_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	update(char *arg, int index, t_env **env)
{
	int		i;
	t_env	*ptr;

	i = 0;
	ptr = *env;
	while (i < index)
	{
		ptr = ptr->next;
		i++;
	}
	if (ft_strchr(arg, '='))
	{
		free(ptr->value);
		free(ptr->result);
		ptr->value = ft_substr(arg, 0, equal_pos(arg));
		ptr->result = ft_substr(arg, equal_pos(arg) + 1, ft_strlen(arg) - 1);
	}
	return (0);
}

t_env	*ft_create_var(char *arg)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (new_elem == NULL)
		return (NULL);
	if (ft_strchr(arg, '='))
	{
		new_elem->value = ft_substr(arg, 0, equal_pos(arg));
		new_elem->result = ft_substr(arg, equal_pos(arg) + 1, ft_strlen(arg)
				- 1);
	}
	else
	{
		new_elem->value = ft_strdup(arg);
		new_elem->result = ft_strdup("''");
		new_elem->next = NULL;
	}
	return (new_elem);
}

int	add_var(char *arg, t_env **env)
{
	ft_env_push_back(env, arg);
	return (0);
}

int	jsh_export(t_commands **temp, t_env **env)
{
	char	**args;
	int		i;
	int		index;

	index = -1;
	args = (*temp)->command;
	if (!args[1])
		return (print_export(env));
	else
	{
		i = 1;
		while (args[i])
		{
			index = index_existing_var(args[i], env);
			if (index >= 0)
				update(args[i], index, env);
			else
			{
				add_var(args[i], env);
			}
			i++;
		}
	}
	return (0);
}
