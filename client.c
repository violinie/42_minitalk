#include <signal.h>
#include <unistd.h>

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

	kill(pid, SIGUSR1);
	return (0);
}
