/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:16:22 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 16:36:40 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	if (!arg || !*arg)
		return (NULL);
	new_elem = (t_env *)malloc(sizeof(t_env));
	new_elem->value = NULL;
	new_elem->result = NULL;
	new_elem->next = NULL;
	//ft_bzero(&new_elem, sizeof(new_elem));
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
	}
	return (new_elem);
}

int     arg_is_not_alphanum(char *str)
{
        while (*str)
        {
                if (ft_isalnum(*str) == 0 && *str != '=' && *str != '!' && *str != '#' && *str != '%' && ft_is_oper(*str) == 0 && *str != '_')
                        return (1);
                str++;
        }
        return (0);
}

int     error_msg_not_valid_in_cntxt(char *arg)
{
        char    *str;

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

int	export(char **args, t_env **env)
{
	int	i;
	int	index;
	int	j;

	index = -1;
	if (!args[1])
		return (print_export(env));
	else
	{
		i = 1;
		j = 0;
		while (args[i])
		{
			if (ft_isdigit(args[i][0]) || arg_is_not_alphanum(args[i])
                                || ft_strcmp(args[i], "=") == 0)
                                error_msg_not_valid_in_cntxt(args[i]);
			else
			{
				index = index_existing_var(args[i], env);
				j = 0;
				if (args[i][ft_strlen(args[i]) - 1] == '=')
				{
					args[i] = ft_brute_force_equal(args[i], args[i + 1]);
					j++;
				}
				if (index >= 0)
					update(args[i], index, env);
				else
					ft_env_push_back(env, args[i]);
			}
			i = i + 1 + j;
		}
	}
	return (0);
}
