#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

void	handle_signal(int sig)
{
	if (sig == SIGUSR1 || sig == SIGUSR2)
		write(1, "This part is working\n", 22);
}

int	main(void)
{
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);

	pid_t pid = getpid();
	write(1, "Server PID: ", 12);
	char buffer[20];
	int len = snprintf(buffer, 20, "%d\n", pid);
	write(1, buffer, len);

	while (1)
		pause();
}
