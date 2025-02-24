int	jsh_unset(char *var)
{
	extern	char	**environ;
	int		i;
	int		j;

	if (!var || !*var)
	{
		printf("unset: error: missing argument.");
		return (1);
	}
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) && environ[i][ft_strlen(var)] == '=')
		{
			j = 0;
			
}
