/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:04:39 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/07 15:37:59 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	index_existing_var(char *arg, t_env **env)
{
	int		len;
	int		i;
	t_env		*ptr;

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
		if (ft_strncmp(ptr->value, arg, len))
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
	int	i;
	t_env	*ptr;
	//t_env	*save;

	i = 1;
	ptr = *env;
	//save = env;
	while (i < index)
	{
		ptr = ptr->next;
		i++;
	}
	printf("string apres i < index:%s\n", (*env)->value);
	free(ptr->value);
	free(ptr->result);
	if (ft_strchr(arg, '='))
	{
		ptr->value = ft_substr(arg, 0, equal_pos(arg));
	       	printf("string apres cutting =:%s\n", (ptr->value));
		ptr->result = ft_substr(arg, equal_pos(arg), ft_strlen(arg));
	}
	else
	{
		ptr->value = ft_strdup(arg);
		ptr->result = ft_strdup("=''");
	}	
	printf("strings at the end of update:%s%s\n", (*env)->value, (*env)->result);
	//env = save;
	return (0);
}

t_env  *ft_create_var(char *arg)
{
    t_env  *new_elem;

    new_elem = (t_env *)malloc(sizeof(t_env));
    if (new_elem == NULL)
        return (NULL);
    if (ft_strchr(arg, '='))
    {
	    new_elem->value = ft_substr(arg, 0, equal_pos(arg));
	    printf("string apres cutting =:%s\n", new_elem->value);
	    new_elem->result = ft_substr(arg, equal_pos(arg), ft_strlen(arg));
    }
    else
    {                                                                                        new_elem->value = ft_strdup(arg);
	    new_elem->result = ft_strdup("=''");
	    new_elem->next = NULL;
    }
    return (new_elem);
}

void ft_env_push_back(t_env **begin_list, char *data)
{
    t_env *new_elem;
    t_env *current;

    new_elem = ft_create_var(data);  // Create a new element
    if (*begin_list == NULL)
    {
        *begin_list = new_elem;  // If the list is empty, make the new element the first one
    }
    else
    {
        current = *begin_list;
        // Traverse to the last element
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_elem;  // Append the new element at the end
    }
}

int	add_var(char *arg, t_env **env)
{
	puts("on est la");
	ft_env_push_back(env, arg);
	return (0);
}	

int	jsh_export(t_commands **temp, t_env **env)
{
	char	**args;
	int	i;
	int	index;
	//int	fd;
	
	//new_environ = ft_copy_env(envp);
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
			printf("index: %d\n", index);
			if (index >= 0)
				update(args[i], index, env);
			else
			{
				add_var(args[i], env);
				//fd = open("environ_log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
        			//ft_putstr_fd(args[i], fd);

			}
			i++;
		}
	}
	return (0);
}
