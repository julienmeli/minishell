#include <stdlib.h>
#include <stdio.h>

int	ft_is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_words(char *str, char *charset)
{
	int	count;
	int	trigger;

	count = 0;
	trigger = 0;
	while (*str)
	{
		if (!ft_is_in_charset(*str, charset) && trigger == 0)
		{
			count++;
			trigger++;
		}
		if (ft_is_in_charset(*str, charset))
		{
			trigger = 0;
		}
		str++;
	}
	return (count);
}

int	ft_wrdlen(char *str, char *charset)
{
	int	len;

	len = 0;
	while (str[len] && !ft_is_in_charset(str[len], charset))
		len++;
	return (len);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strdup(char *str, int len)
{
	char	*string;
	int	i;

	string = malloc((len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (i < len)
	{
		string[i] = str[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	**ft_split2(char *str, char *charset)
{
	char	**result;
	int	words;
	int	len;
	int	i;

	words = ft_words(str, charset);
	result = (char **)malloc((words + 1) * sizeof(*result));
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (!ft_is_in_charset(*str, charset))
		{
			len = ft_wrdlen(str, charset);
			//printf("%d\n", len);
			result[i] = ft_strdup(str, len);
			//printf("%s\n", result[i]);
			if (result[i] == NULL)
			{
				ft_free(result);
				return (NULL);
			}
			str = str + len;
			i++;
		}
		else
			str++;
	}
	result[i] = NULL;
	return (result);
}
/*
int	main(void)
{
	char	**array;
	char	*str;
	int	len;
	int	k;

	str = "On m'appelle le Chevalier Blanc, je vais et je viens au secours des gens.";
	len = ft_words(str, " \a\b\t\n\v\f\r");
	printf("%d\n", len);
	array = ft_split(str, " \a\b\t\n\v\f\r");
	k = 0;
	while (array[k])
	{
		printf("%s\n", array[k]);
		k++;
	}
	return (0);
}
*/
