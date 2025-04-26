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
	if (argc != 3)
		return (1);

	pid_t pid = ft_atoi(argv[1]);
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
