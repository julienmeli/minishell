/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:22:05 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/10 11:11:02 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	jsh_env(t_commands **cmd, t_env **env)
{
	//extern char	**environ;
	//int			i;
	t_env		*ptr;
	
	(void)cmd;
	ptr = *env;
	//i = 0;
	/*
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	*/
	puts("je suis la");
	while (ptr)
	{
		printf("%s=%s\n", ptr->value, ptr->result);
		ptr = ptr->next;
	}
	return (0);
}
