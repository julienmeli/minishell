#include "../../include/minishell.h"           

int	count_strings_pointer(char ***array_ptr)
{
	int count = 0;
    
    // Check if pointer to array is NULL
	if (array_ptr == NULL)
		return 0;    
    // Get the actual array
	char **array = *array_ptr;
    // Check if array itself is NULL
	if (array == NULL)
		return 0;
    // Count until NULL terminator is found

	while (array[count] != NULL)
	{
		count++;
	}
	return count;
}

void	ft_print_array_of_strings(char **array, int size)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		ft_putstr_fd("array[", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("]: ", 1);
		ft_putstr_fd(array[i], 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(size, 1);
		ft_putchar_fd('\n', 1);
		//printf("array[%d]: %s %d\n", i, array[i], size);
		i++;
	}
} 

int	size_of_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	*my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	unsigned char	*src;
	unsigned char	*dst;
	void		*new_ptr;
	size_t		copy_size;
	size_t		i;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	printf("old & new_size in my_realloc: %ld %ld\n", old_size, new_size);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	src = (unsigned char *)ptr;
	dst = (unsigned char *)new_ptr;
	i = 0;
	while (i < copy_size)
	{
		dst[i] = src[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

int	insert_string(char ***array, int *size, const char *str, int position)
{
	char	**new_array;
	char	*new_str;
	int	i;

	// Validate inputs
	if (array == NULL || size == NULL || str == NULL || position < 0 || position > *size)
		return (-1);
	printf("array[0]: %s, size: %d, str: %s, position: %d\n", (*array)[0], *size, str, position);
	// Allocate memory for the new string
	new_str = strdup(str);
	if (new_str == NULL)
		return (-1);
		// Memory allocation failed
	// Allocate memory for the new array
	new_array = (char **)my_realloc(*array, (*size) * sizeof(char *), (*size + 1) * sizeof(char *));
	if (new_array == NULL)
	{
		free(new_str);
		return (-1);
		// Memory allocation failed
	}
	*array = new_array;
	// Shift elements to make space for the new string
	i = *size;
	while (i > position) 
	{
		(*array)[i] = (*array)[i - 1];
		//printf("i: %d (*array)[i]: %s (*array)[i - 1]: %s i - 1: %d\n", i, (*array)[i], (*array)[i - 1], i - 1);
		i--;
	}
	// Insert the new string
	(*array)[position] = new_str;
	(*array)[*size + 1] = NULL;
	//printf("array position: %s\n", (*array)[position]);
	// Update the size
	(*size)++;
	return (0);
}

int	create_new_array(char ***array, char *arg, int index)
{
	//char	**result;
	char	**new_intermediate_array;
	int	i;
	int	size;
	int	size_new_array;
	//int	current_size;

	size = count_strings_pointer(array);
	printf("size in create new array: %d\n", size);
	new_intermediate_array = ft_split(arg, ' ');
	size_new_array = size_of_array(new_intermediate_array);
	ft_print_array_of_strings(new_intermediate_array, size_new_array);
	i = 0;
	while (i < size_new_array)
	{
		insert_string(array, &size, new_intermediate_array[i], index);
		i++;
		index++;
	}
	return (size_new_array);
}

int	desert_string(char ***array, int *size, const char *str, int position)
{
	char	**current_array;
	//char	**new_array;
	int	i;
	//int	j;
	
	(void)str;
	if (array == NULL || *array == NULL || size == NULL || *size <= 0 || position < 0 || position > *size)
		return (-1);
	current_array = *array;
	free(current_array[position]);
	printf("position: %d size: %d\n", position, *size);
	i = position;
	while (i < *size - 1)
	{
		current_array[i] = current_array[i + 1];
		printf("oh putain %s %d\n", current_array[i], i);                                 printf("oh putain %s\n", current_array[i + 1]);
		i++;
	}
	if (position == *size - 1)
		current_array[position] = NULL;
	//free(current_array[i + 1]);
	current_array[i + 1] = NULL;
	//(*size)--;
	//new_array = (char **)malloc((*size - 1) * sizeof(char *));
	/*
	new_array = (char **)my_realloc(*array, (*size) * sizeof(char *), (*size - 1) * sizeof(char *));
       if (new_array == NULL || *size - 1 == 0)
	       *array = new_array;
	*/
	(*size)--;
	return (0);
}

int	delete_old_string(char ***array, char *arg, int pos)
{
	int	size;

	ft_putstr_fd("nous sommes ici\n", 1);
	size = count_strings_pointer(array);
	ft_putnbr_fd(size, 1);
	ft_putstr_fd(" prev nb is size in delete old string\n", 1);
	return (desert_string(array, &size, arg, pos));
}

void	echo_check(char ***args)
{
	//char	**temp;
	int	size;
	int	i;
	int	jump;
	
	puts("here");
	size = count_strings_pointer(args);
	ft_putnbr_fd(size, 1);
	puts((*args)[0]);
	i = 0;
	while (i < size)
	{
		if (there_is_space((*args)[i]))
		{
			//ft_print_array_of_strings(*args, size_of_array(*args));
			ft_putstr_fd("\n size: ", 1);
                        ft_putnbr_fd(size_of_array(*args), 1);
                        ft_putstr_fd("\n", 1);
			jump = create_new_array(args, (*args)[i], i);
			ft_putstr_fd("\n size: ", 1);
                        ft_putnbr_fd(size_of_array(*args), 1);
                        ft_putstr_fd("\n", 1);
			ft_putnbr_fd(delete_old_string(args, (*args)[i + jump], jump + i), 1);
			ft_putstr_fd("\n size: ", 1);
                        ft_putnbr_fd(size_of_array(*args), 1);
                        ft_putstr_fd("\n", 1);
			printf("jump: %d %s size: %d i: %d\n", i + jump - 1, (*args)[i + jump - 1], size, i);
			i = i + jump - 1;
			size = size + jump - 1;
			ft_putstr_fd("i: ", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd("\n size: ", 1);
			ft_putnbr_fd(size_of_array(*args), 1);
			ft_putstr_fd("\n", 1);
			if (i > 10)
				break ;
			//write(1, "cici", 4);
			//printf("size of args: %d args[0]: %s\n", size_of_array(*args), (*args)[0]);
			//ft_print_array_of_strings(*args, size_of_array(*args));
		}
		i++;		
	}
	puts("out");
}
