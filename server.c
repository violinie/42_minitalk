/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanacop <hanacop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:57:51 by hanacop           #+#    #+#             */
/*   Updated: 2025/04/26 13:57:52 by hanacop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char current_char = 0;
	static int bit_count = 0;

	(void)info;
	(void)context;

	current_char <<= 1; // move bits to left

	if (sig == SIGUSR1)
		current_char |= 1; // set last bit if received 1

	bit_count++;

	if (bit_count == 8)
	{
		write(1, &current_char, 1);
		if (current_char == '\0')
			write(1, "\n", 1);
		current_char = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pid_t pid = getpid();
	printf("Server PID: %d\n", pid);

	while (1)
		pause();
}
