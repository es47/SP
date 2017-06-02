#include "apue.h"
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

static void	sig_int(int);		/* our signal-catching function */
	int
main(void)
{
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;
		char *ptr, *argv[100];
	int i;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	printf("## ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		ptr = strtok(buf, " ");
		i = 0;
		while(ptr != NULL)
		{
			argv[i++] =  ptr;
			ptr = strtok(NULL, " ");
		}
		argv[i] = (char*)0;
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */
		if (strcmp(argv[0], "cd") == 0)
			chdir(argv[1]);
		else{
			if ((pid = fork()) < 0) 
			{
				err_sys("fork error");
			} 
			else if (pid == 0) {		/* child */
				execvp(argv[0],argv);
				memset(argv, 0, sizeof(argv));
				err_ret("couldn't execute: %s", buf);
				exit(127);
			}

			/* parent */
			if ((pid = waitpid(pid, &status, 0)) < 0)
				err_sys("waitpid error");
		}
		printf("## ");
	}
	exit(0);
}

	void
sig_int(int signo)
{
	printf("interrupt\n%% ");
}

