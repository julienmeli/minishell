/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:29:13 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 01:18:45 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_root_directory(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "HOME=", 5) == 0)
			return (ft_substr(environ[i], 5, ft_strlen(environ[i]) - 5));
		i++;
	}
	return (NULL);
}

void	save_oldpwd(t_env **env)
{
	char	buf[1024];
	char	*wd;
	char	*oldpwd;
	int	index;

	wd = getcwd(buf, 1024);
	oldpwd = ft_strjoin("OLDPWD=", wd);
	//free(wd);
	index = index_existing_var("OLDPWD", env);
	update(oldpwd, index, env);
	free(oldpwd);
}

void    save_newpwd(t_env **env)
{
        char    buf[1024];
        char    *wd;
        char    *newpwd;
	int	index;

        wd = getcwd(buf, 1024);
        newpwd = ft_strjoin("PWD=", wd);
        //free(wd);
        index = index_existing_var("PWD", env);
        update(newpwd, index, env);
	free(newpwd);
}

int	cd(char **args, t_env **env)
{
	char	*root;

	save_oldpwd(env);
	if (!args[1] && args[1] == NULL)
	{
		root = get_root_directory();
		if (chdir(root) != 0)
			printf("cd: root error\n");
		else
		{
			free(root);
			return (0);
		}
		return (1);
	}
	else if (args[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else if (chdir(args[1]) != 0)
	{
		printf("cd : error\n");
		return (1);
	}
	save_newpwd(env);
	return (0);
}
