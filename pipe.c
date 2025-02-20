#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(void)
{
	int	pipefd[2];
	pid_t	pid;
	char	buf;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pipefd[1]);
		write(1, "Child: I don't know.\n", 21);
		write(1, ":\"", 2);
		while (read(pipefd[0], &buf, 1) > 0)
			write(1, &buf, 1);
		write(1, "\"\n", 2);
		write(1, "Child: but of course!", 21);
	       	close(pipefd[0]);
		exit(EXIT_SUCCESS);	
	}
	else
	{
		close(pipefd[0]);
		write(1, "Parent: 1 + 1?\n", 15);
	       	write(pipefd[1], "Parent: the answer is 2.", 24);
		close(pipefd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);	
	}
}
