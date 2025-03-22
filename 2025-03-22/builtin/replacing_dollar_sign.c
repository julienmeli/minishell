/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing_dollar_sign.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 09:34:19 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/22 16:47:16 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// say export HOLA=bonjour
// command echo $=HOLA (or echo $====HOLA) will print bonjour i.e. the same result as echo $HOLA
// command echo $9HOLA or $99HOLA will print HOLA
// echo $$HOLA will print 24435HOLA (even number of $)
// echo $$$HOLA will print 24435bonjour (odd numbers of $)
// list of pure separators: " ;" (space and semicolon)
// list of separators that will be read as a new character : "]=+-{^%$#@!:,./". So echo $HOLA{ will print bonjour{
// echo $HOLA% will print bonjour%
// list of NON-separators: _ and digits (0 ... 9), i.e. echo $HOLA_ will print nothing (environment not found for HOLA_)
// list of separators that result in error message: [, (, ), *, ?, <, >, \, |

char	*ft_is_regular_string(char *str, int i)
{
	char	*separators;
	int		j;

	// puts("is reg string");
	separators = " ;]=+-{^%$#@!:,./[()*?<>\\|";
	j = 0;
	while (str[j + i] && !ft_strchr(separators, str[j + i]))
		j++;
	return (ft_substr(str, i, j - i + 2));
}

char	*ft_strjoin_null(char *s1, char *s2)
{
	char	*temp;

	if (!s1)
		temp = s2;
	else
		temp = ft_strjoin(s1, s2);
	return (temp);
}
char	*ft_temp_and_free(char *string, char *easy_separators, char *str, int i)
{
	char	*temp;
	char	*substr;

	//substr = ft_substr(str, i, ft_strlen(str) - i + 1);
	if (ft_strchr(easy_separators, str[i]))
	{
		substr = ft_substr(str, i, ft_strlen(str) - i + 1);
		temp = ft_strjoin_null(string, substr);
		free (substr);
	}
	else
	{
		if (!string)
			return (NULL);
		temp = string;
	}
	//free (string);
	//free (substr);
	return (temp);
}

char	*ft_string_after_dollar(char *str, int i, t_env *env)
{
	char	*all_separators;
	char	*easy_separators;
	char	*string;
	char	*temp;
	int		j;

	all_separators = " ;]=+-{^%$#@!:,./[()*?<>\\|";
	easy_separators = "]=+-{^%$#@!:,./";
	temp = NULL;
	while (str[i] && str[i] == '$')
		i++;
	while (str[i] && str[i] == '=')
		i++;
	j = i;
	while (str[i] && !ft_strchr(all_separators, str[i]))
		i++;
	temp = ft_substr(str, j, i - j);
	string = ft_getenv(env, temp);
	free(temp);
	temp = ft_temp_and_free(string, easy_separators, str, i);
	//free(string);
	return (temp);
}

char	*replace_dollar_sign(char *str, int i, t_env *env)
{
	char	*all_separators;
	int		j;

	all_separators = " ;]=+-{^%$#@!:,./[()*?<>\\|";
	//printf("string!: %s\n", ft_string_after_dollar(str, i, env));
	j = i;
	while (str[i] && str[i] == '$')
		i++;
	if (i % 2 == 0)
		return (ft_is_regular_string(str, i));
	while (str[i] && str[i] == '=')
		i++;
	if (ft_isdigit(str[i]))
		return (ft_is_regular_string(str, i + 1));
	else
		return (ft_string_after_dollar(str, j, env));
}
/*
char	*replace(char *str, int i, t_env *env)
{
	char	*buffer;
	char	*buff2;
	int		j;

	j = i;
	j = ft_strlen_j(str, j);
	i = i + ft_dollar_start(str);
	j = j - i + ft_dollar_length(str);
	buffer = ft_substr(str, i, j);
	printf("buffer:%s, i:%d, j:%d\n", buffer, i, j);
	buff2 = str;
	str = ft_getenv(env, &buffer[1]);
	if (!str)
	{
		free(buffer);
		free(buff2);
		buffer = malloc(1 * sizeof(char));
		buffer[0] = '\0';
		return (buffer);
	}
	str = ft_replacesubstr(buff2, buffer, str);
	free(buff2);
	free(buffer);
	return (str);
}
*/