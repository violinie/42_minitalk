#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void send_char(pid_t pid, char c)
{
	int i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1) // shift the bit by i places & print the rightmost
			kill(pid, SIGUSR1); // send 1
		else
			kill(pid, SIGUSR2); // send 0
		usleep(100);
		i--;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	int pid = 0;
	int i = 0;
	while (argv[1][i])
	{
		pid = pid * 10 + (argv[1][i] - '0');
		i++;
	}
	send_char(pid, 'A');
	kill(pid, SIGUSR1);
	return (0);
}
