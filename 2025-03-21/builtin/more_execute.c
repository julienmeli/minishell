/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:20:52 by aharder           #+#    #+#             */
/*   Updated: 2025/03/12 00:35:50 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long long	ft_atoi_long(char *str)
{
	long long	result;
	int		sign;
	int		i;

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
	while(arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	commandbuiltin(char **arg, t_env *env)
{
	int	exit_status;
	long long	exit_code;

	(void)env;
	exit_status = 0;
	if (strcmp(arg[0], "cd") == 0)
	{
		exit_status = cd(arg, &env);
	}
	else if (strcmp(arg[0], "export") == 0)
		exit_status = export(arg, &env);
	else if (strcmp(arg[0], "unset") == 0)
		exit_status = unset(arg, &env);
	else if (strcmp(arg[0], "exit") == 0)
	{
		if (arg[2])
		{
			ft_putstr_fd("error: exit: too many arguments.", 2);
			exit(1);
		}
		if (arg[1] && check_arg_is_numeric(arg[1]) == 1)
		{
			exit_code = ft_atoi_long(arg[1]);
			(void)exit_code;			
		}
		ft_exit(env);
	}
	return (exit_status);
}

char	*get_path(char *cmd, t_env *env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(ft_getenv(env, "PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_split(s_cmd);
			return (exec);
		}
		free(exec);
	}
	free_split(allpath);
	free_split(s_cmd);
	return (cmd);
}
