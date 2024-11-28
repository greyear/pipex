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


static void	child1(t_pipex *p)
{
	int	in;

	in = open(p->argv[1], O_RDONLY);
	if (in < 0)
	{
		close_fds(p->fd[0], p->fd[1], p);
		error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
	}
	if (close(p->fd[0]) == -1)
	{
		close_fds(in, p->fd[1], p);
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
	}

	if (dup2(in, STDIN_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	if (dup2(p->fd[1], STDOUT_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);

	close_fds(in, p->fd[1], p);

	//execlp("ping", "ping", "-c", "5", "google.com", NULL);
	//execve(const char *pathname, char *const argv[], char *const envp[]);
}

static void	child2(t_pipex *p)
{
	int	out;

	out = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out < 0)
	{
		close_fds(p->fd[0], p->fd[1], p);
		error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
	}
	if (close(p->fd[1]) == -1)
	{
		close_fds(p->fd[0], out, p);
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
	}

	if (dup2(p->fd[0], STDIN_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	if (dup2(out, STDOUT_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);

	close_fds(p->fd[0], out, p);
	
	execlp("grep", "grep", "rtt", NULL);
}

int	pipex(t_pipex *p)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(p->fd) == -1)
		error_clean_exit_code(ERR_PIPE, EXIT_FAILURE, &p);

	pid1 = fork();
	if (pid1 < 0)
		error_clean_exit_code(ERR_FORK, EXIT_FAILURE, &p);
	
	if (pid1 == 0)
	{
		child1(p); //child 1 for cmd1 (right end of pipe, writing end)
	}

	pid2 = fork();
	if (pid2 < 0)
		error_clean_exit_code(ERR_FORK, EXIT_FAILURE, &p);
	if (pid2 == 0)
	{
		child2(p); //child 2 for cmd2 (left end of pipe, reading end)
	}
	
	close_fds(p->fd[0], p->fd[1], p);
	
	status = waiting(pid1, pid2, p);
	return (status);
}

int	waiting(pid_t pid1, pid_t pid2, t_pipex *p)
{
	int	status;
	int	pid_counter;

	while (pid_counter < cmd_num)
	{
		if (waitpid(pid2, &status, 0) == -1)
			error_clean_exit_code(ERR_WAITPID, EXIT_FAILURE, &p);
		pid_counter++;
	}
	return ((status >> 8) & 255);
}
