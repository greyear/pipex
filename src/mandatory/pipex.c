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


static void	child(t_pipex *p)
{
	int	fd_in;
	int fd_out;

	fd_in = p->fd[0]; //for every case
	if (p->cmd_num == 0) //sprecial case for the 1st process
	{
		fd_in = open(p->argv[1], O_RDONLY);
		if (fd_in < 0)
		{
			close_fds(p->fd[0], p->fd[1], p);
			error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
		}
		if (close(p->fd[0]) == -1)
		{
			close_fds(fd_in, p->fd[1], p);
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		}

	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	
	fd_out = p->fd[1]; //for every case
	if (p->cmd_num == p->argc - 4) //for the last process
	{
		fd_out = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			close_fds(p->fd[0], p->fd[1], p);
			error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
		}
		if (close(p->fd[1]) == -1)
		{
			close_fds(p->fd[0], fd_out, p);
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		}
		
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	close_fds(fd_in, fd_out, p);

	//execlp("ping", "ping", "-c", "5", "google.com", NULL);
	//execve(const char *pathname, char *const argv[], char *const envp[]);
}

int	pipex(t_pipex *p)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	p->cmd_num = 0;
	while (p->cmd_num < p->argc - 3)
	{
		if (pipe(p->fd) == -1)
			error_clean_exit_code(ERR_PIPE, EXIT_FAILURE, &p);
		p->pids[p->cmd_num] = fork();
		if (p->pids[p->cmd_num] < 0)
			error_clean_exit_code(ERR_FORK, EXIT_FAILURE, &p);
		if (p->pids[p->cmd_num] == 0)
		{
			child(p); //child 1 for cmd1 (right end of pipe, writing end)
		}
		p->cmd_num++;
	}
		
	
	close_fds(p->fd[0], p->fd[1], p);
	status = waiting(pid1, pid2, p);
	return (status);
}

int	waiting(t_pipex *p)
{
	int	status;
	int	pid_counter;

	pipex(p);
	while (pid_counter < p->cmd_num)
	{
		if (waitpid(p->pids[pid_counter], &status, 0) == -1)
			error_clean_exit_code(ERR_WAITPID, EXIT_FAILURE, &p);
		pid_counter++;
	}
	return ((status >> 8) & 255);
}
