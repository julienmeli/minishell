#include "minishell.h"

int	ft_putenv(char *string)
{

}

int	jsh_export(char **args)
{
	int	i;
	int	j;
	extern char	**environ;
	char		*equal_sign;
	
	i = 1;
	if (!(args[i]))
	{
		j = 0;
		while (environ[j])
		{
			printf("declare -x %s\n", environ[j]);
			j++;
		}
		return (0);
	}
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			if (putenv
		}
}
