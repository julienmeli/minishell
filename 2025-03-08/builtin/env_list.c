/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:05:54 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/07 16:23:08 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_before_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	init_env(t_mini *mini, char **environ)
{
	t_env	*env;
	t_env	*new;
	int	len;
	int	i;

	//puts("check");
	new = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return ;
	len = len_before_equal_sign(environ[0]);
	//printf("checkos: %s\n", environ[0]);
	env->value = ft_substr(environ[0], 0, len);
	env->result = ft_substr(environ[0], len + 1, (ft_strlen(environ[0]) - len -1));
	env->next = NULL;
	//printf("check2: %s\n", env->value);
	mini->env = env;
	i = 0;
	while (environ[i])
	{
		new = malloc(sizeof(t_env));
		if (new == NULL)
			return ;
		len = len_before_equal_sign(environ[i]);
		new->value = ft_substr(environ[i], 0, len);
		new->result = ft_substr(environ[i], len + 1, (ft_strlen(environ[0]) - len -1));
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
}
