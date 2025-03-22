/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing_dollar_sign.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 09:34:19 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/22 11:23:10 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// say export HOLA=bonjour
//command echo $=HOLA (or echo $====HOLA) will print bonjour i.e. the same result as echo $HOLA 
//command echo $9HOLA or $99HOLA will print HOLA
//echo $$HOLA will print 24435HOLA (even number of $)
//echo $$$HOLA will print 24435bonjour (odd numbers of $)
//list of pure separators: " ;" (space and semicolon)
//list of separators that will be read as a new character : "]=+-{^%$#@!:,./". So echo $HOLA{ will print bonjour{
//echo $HOLA% will print bonjour%
// list of NON-separators: _ and digits (0 ... 9), i.e. echo $HOLA_ will print nothing (environment not found for HOLA_)
//list of separators that result in error message: [, (, ), *, ?, <, >, \, |

int ft_dollar_length(char *str)
{
    if (str[1] && str[1] == '=')
        return (-1);
    if (str[1] && ft_isdigit(str[1]))
        return (-1);
    return (0);
}

int ft_dollar_start(char *str)
{
    if (str[1] && str[1] == '=')
        return (1);
    if (str[1] && ft_isdigit(str[1]))
        return (1);
    return (0);
}
int	ft_strlen_j(char *str, int j)
{
	while (str[j] == '$' && ft_isalnum(str[j]))
		j++;
	return (j);
}

char	*replace_dollar_sign(char *str, int i, t_env *env)
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
