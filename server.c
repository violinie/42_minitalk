#include <signal.h>    // for sigaction, siginfo_t, SA_SIGINFO
#include <unistd.h>    // for write, pause, getpid
#include <stdio.h>     // for printf, snprintf
#include <sys/types.h>

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1 || sig == SIGUSR2)
		write(1, "This part is working\n", 22);
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
