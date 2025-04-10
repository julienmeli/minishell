/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigquit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:06:37 by jmeli             #+#    #+#             */
/*   Updated: 2025/04/10 15:12:31 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void	disable_ctrl_backslash_echo(void)
{
	struct termios	term;

	// Get current terminal attributes
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	// Disable the quit character (Ctrl+\)
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	// Apply the modified terminal settings
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
	}
}
