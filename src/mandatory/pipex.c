/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:12:59 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/15 15:13:00 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//simulation of: "ping -c 5 google.com | grep rtt"

//cmd1 < file1 | cmd2 > file2
//./pipex file1 cmd1 cmd2 file2


static void	child1(char* argv[], char *envp[], t_pipex *p)
{
	int	in;

	in = open(argv[1], O_RDONLY);
	if (in < 0)
	{
		close_fds(fd[0], fd[1], p);
		error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
	}
	if (close(fd[0]) == -1)
	{
		close_fds(in, fd[1], p);
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
	}

	if (dup2(in, STDIN_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);

	close_fds(in, fd[1], p);

	//execlp("ping", "ping", "-c", "5", "google.com", NULL);
	//execve(const char *pathname, char *const argv[], char *const envp[]);
}

static void	child2(int argc, char* argv[], char *envp[], t_pipex *p)
{
	int	out;

	out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out < 0)
	{
		close_fds(fd[0], fd[1], p);
		error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
	}
	if (close(fd[1]) == -1)
	{
		close_fds(fd[0], out, p);
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
	}

	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	if (dup2(out, STDOUT_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);

	close_fds(fd[0], out, p);
	
	execlp("grep", "grep", "rtt", NULL);
}

int	pipex(char* argv[], char *envp[], t_pipex *p)
{
	int	fd[2];
	int	pid1;
	int pid2;

	if (pipe(fd) == -1)
		error_clean_exit_code(ERR_PIPE, EXIT_FAILURE, &p);

	pid1 = fork();
	if (pid1 < 0)
		error_clean_exit_code(ERR_FORK, EXIT_FAILURE, &p);
	
	if (pid1 == 0)
	{
		//child 1 for cmd1 (right end of pipe, writing end)
	}

	pid2 = fork();
	if (pid2 < 0)
		error_clean_exit_code(ERR_FORK, EXIT_FAILURE, &p);
	if (pid2 == 0)
	{
		//child 2 for cmd2 (left end of pipe, reading end)
	}
	
	close_fds(fd[0], fd[1], p);
	
	if (waitpid(pid1, NULL, 0) == -1)
		error_clean_exit_code(ERR_WAITPID, EXIT_FAILURE, &p);
	if (waitpid(pid2, NULL, 0) == -1)
		error_clean_exit_code(ERR_WAITPID, EXIT_FAILURE, &p);
	return (0);
}
