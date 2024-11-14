
#include "pipex.h"

//simulation of: "ping -c 5 google.com | grep rtt"

//cmd1 < file1 | cmd2 > file2
//./pipex file1 cmd1 cmd2 file2

int	pipex(char* argv[], char *envp[], t_pipex *p)
{
	int	fd[2];
	int	pid1;
	int pid2;

	if (pipe(fd) == -1)
		//ERR_PIPE

	pid1 = fork();
	if (pid1 < 0)
		//ERR_FORK
	
	if (pid1 == 0)
	{
		//child 1 for cmd1 (right end of pipe, writing end)
	}

	pid2 = fork();
	if (pid2 < 0)
		//ERR_FORK
	if (pid2 == 0)
	{
		//child 2 for cmd2 (left end of pipe, reading end)
	}
	
	close(fd[0]);
	close(fd[1]);

	if (waitpid(pid1, NULL, 0) == -1)
		//ERR_WAITPID
	if (waitpid(pid2, NULL, 0) == -1)
		//ERR_WAITPID
	return (0);
}