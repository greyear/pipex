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

//cmd1 < file1 | cmd2 > file2 
//e.g. ls -l < infile | wc -l > outfile 

//./pipex file1 cmd1 cmd2 file2
//./pipex infile "grep a1" "wc -w" outfile

//debug: "args": ["infile", "grep a1", "wc -w", "outfile"],

static void	child(t_pipex *p)
{
	int	fd_in;
	int fd_out;

	fd_in = p->fd[0]; //for every case
	if (p->cmd_num == 0) //special case for the 1st process
	{
		fd_in = open(p->argv[1], O_RDONLY);
		if (fd_in < 0)
		{
			//close_fds(p->fd[0], p->fd[1], p);
			error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
		}
		if (close(p->fd[0]) == -1)
		{
			//close_fds(fd_in, p->fd[1], p);
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
			//close_fds(p->fd[0], p->fd[1], p);
			error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
		}
		if (close(p->fd[1]) == -1)
		{
			//close_fds(p->fd[0], fd_out, p);
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		}
		
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	close_fds(fd_in, fd_out, p);
	//ft_printf(2, "Executing command: %s\n", p->argv[p->cmd_num + 2]); //delete
	//ft_printf(2, "---->%s<--- \n", p->argv[p->cmd_num + 2]);
	handle_command(p->argv[p->cmd_num + 2], p);
	exit(EXIT_SUCCESS);
}

void	pipex(t_pipex *p)
{
	//p->cmd_num = 0;
	while (p->cmd_num < p->argc - 3)
	{
		//printf("cmd_num: %d, p->cmd_num: %d\n", p->cmd_num, p->argc - 3);
		if (pipe(p->fd) == -1)
		{
			error_clean_exit_code(ERR_PIPE, EXIT_FAILURE, &p);
		}
		//printf("Created pipe: fd[0] = %d, fd[1] = %d\n", p->fd[0], p->fd[1]); //delete
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
}

int	waiting(t_pipex *p)
{
	int	status;
	int	pid_counter;

	p->cmd_num = 0;
	pipex(p);
	pid_counter = 0;
	while (pid_counter < p->cmd_num)
	{
		if (waitpid(p->pids[pid_counter], &status, 0) == -1)
			error_clean_exit_code(ERR_WAITPID, EXIT_FAILURE, &p);
		pid_counter++;
	}
	return ((status >> 8) & 255);
}
