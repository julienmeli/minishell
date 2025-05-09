/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:46:57 by aharder           #+#    #+#             */
/*   Updated: 2025/03/22 15:57:00 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long long	ft_atoi_long(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		sign = sign * -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		if (result > LONG_MAX || (result * sign) < LONG_MIN)
			break ;
		i++;
	}
	return (result * sign);
}

int	check_arg_is_numeric(char *arg)
{
	int	i;

	if (!arg || arg[0] == '\0')
		return (0);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_env *env, char **arg)
{
	void		*red;
	void		*commands;
	long long	exit_code;
	
	if (arg[2] != NULL)
	{
		ft_putstr_fd("error: exit: too many arguments.", 2);
		exit(1);
	}
	exit_code = 0;
	if (arg[1] && check_arg_is_numeric(arg[1]) == 1)
	{
		exit_code = ft_atoi_long(arg[1]);
		if (exit_code >= 0)
			exit_code = exit_code % 256;
		else
			exit_code = exit_code % 256 + 256;
	}
	red = str_to_ptr(ft_getenv(env, "&"));
	commands = str_to_ptr(ft_getenv(env, "+"));
	free_red(red);
	free_cmd(commands);
	free_env(env);
	exit(exit_code);
}
