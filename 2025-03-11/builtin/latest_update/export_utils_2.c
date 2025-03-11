/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:42:21 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/11 16:11:53 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_brute_force_equal(char *arg1, char *arg2)
{
	char	*result;

	if (ft_strchr(arg2, ' '))
	{
		result = ft_strjoin("'", arg2);
		//free(arg2);
		result = ft_strjoin(result, "'");
		result = ft_strjoin(arg1, result);
	}
	else
		result = ft_strjoin(arg1, arg2);
	free(arg1);
	return (result);	
}

int	ft_is_oper(char c)
{
	if (c <= 47 && c >= 42)
		return (1);
	return (0);
}
