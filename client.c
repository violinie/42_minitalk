/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanacop <hanacop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:57:54 by hanacop           #+#    #+#             */
/*   Updated: 2025/04/26 14:58:12 by hanacop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int i = 0;
	int result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	send_char(pid_t pid, unsigned char c)
{
	int i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500); // wait to not overwhelm server
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t pid = ft_atoi(argv[1]);

	if (argc != 3)
	{
		write(2, "Error: Wrong number of arguments\n", 33);
		return (1);
	}
	if (kill(pid, 0) == -1)
	{
		write(2, "Error: Invalid PID\n", 19);
		return (1);
	}
	char *message = argv[2];
	int i = 0;

	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\0'); // send end of message
	return (0);
}
