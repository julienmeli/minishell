/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:22:05 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/07 16:22:04 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	jsh_env(t_commands **cmd)
{
	//extern char	**environ;
	int			i;
	t_env		*ptr;

	ptr = (*cmd)->env;
	i = 0;
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
		printf("%s %s\n", ptr->value, ptr->result);
		ptr = ptr->next;
	}
	return (0);
}
