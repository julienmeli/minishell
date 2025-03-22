/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:25:45 by aharder           #+#    #+#             */
/*   Updated: 2025/03/22 09:27:24 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env(t_env **env, char **cmd)
{
	t_env	*ptr;

	ptr = *env;
	if (cmd[1])
	{
		ft_putendl_fd("Error: env: too many arguments.", 2);
		exit(1);
	}
	while (ptr)
	{
		if ((strcmp(ptr->value, "?") != 0) && (strcmp(ptr->value, "&") != 0)
			&& (strcmp(ptr->value, "+") != 0))
			printf("%s=%s\n", ptr->value, ptr->result);
		ptr = ptr->next;
	}
	return (0);
}
