/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanacop <hanacop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:57:51 by hanacop           #+#    #+#             */
/*   Updated: 2025/04/27 11:59:54 by hanacop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	current_char = 0;
	static int				bit_count = 0;
	static char				buffer[10000];
	static int				buf_index = 0;

	(void)info;
	(void)context;
	current_char <<= 1;
	if (sig == SIGUSR1)
		current_char |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (buf_index < 9999)
			buffer[buf_index++] = current_char;
		if (current_char == '\0')
		{
			write(1, buffer, buf_index - 1);
			write(1, "\n", 1);
			buf_index = 0;
		}
		current_char = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	printf("Server PID: %d\n", pid);
	while (1)
		pause();
}
