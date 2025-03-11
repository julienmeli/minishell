/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:04:39 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/10 16:04:54 by jmeli            ###   ########.fr       */
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
		puts("erer");
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
int	error_msg_not_valid_in_cntxt(char *arg)
{
	char	*str;
	
	if (ft_strcmp(arg, "=") == 0)
		printf("zsh: bad assignment\n");
	else if (ft_isdigit(arg[0]))
	{
		if (ft_strchr(arg, '='))
		{
			str = ft_substr(arg, 0, equal_pos(arg));
			printf("export: not an identifier: %s\n", str);
			free(str);
		}
		else
			printf("export: not an identifier: %s\n", arg);
	}
	else if (ft_strchr(arg, '='))
	{
		str = ft_substr(arg, 0, equal_pos(arg));
		printf("export: not valid in this context: %s\n", str);
		free(str);
	}
	else
		printf("export: not valid in this context: %s\n", arg);
	return (1);
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
			if (ft_isdigit(args[i][0]) || arg_is_not_alphanum(args[i])
				|| ft_strcmp(args[i], "=") == 0)
				return (error_msg_not_valid_in_cntxt(args[i]));
			index = index_existing_var(args[i], env);
			if (index >= 0)
				update(args[i], index, env);
			else
				ft_env_push_back(env, args[i]);
			i++;
		}
	}
	return (0);
}
