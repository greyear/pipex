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
	int fd_out;

	if (p->cmd_num == 0) //the 1st process
	{
		p->cur_fd = open(p->argv[1], O_RDONLY);
		if (p->cur_fd < 0)
		{
			//close_fds(p->fd[0], p->fd[1], p);
			error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
		}
	}
	if (dup2(p->cur_fd, STDIN_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	if (p->cmd_num != p->argc - 4) //all except the last
	{
		if (dup2(p->fd[1], STDOUT_FILENO) == -1)
			error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	}
	else if (p->cmd_num == p->argc - 4) //the last process
	{
		fd_out = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			//close_fds(p->fd[0], p->fd[1], p);
			error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p); //error?
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
		if (close(fd_out) == -1)
		{
			ft_printf(2, "Here1");
			//close_fds(p->fd[0], fd_out, p);
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		}
	}
	if (close(p->fd[0]) == -1)
	{
		ft_printf(2, "Here2");
		//close_fds(fd_in, p->fd[1], p);
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
	}
	handle_command(p->argv[p->cmd_num + 2], p);
	exit(EXIT_SUCCESS);
}

void	pipex(t_pipex *p)
{
	p->cur_fd = -1;
	while (p->cmd_num < p->argc - 3)
	{
		if (pipe(p->fd) == -1)
			error_clean_exit_code(ERR_PIPE, EXIT_FAILURE, &p);

		p->pids[p->cmd_num] = fork();
		if (p->pids[p->cmd_num] < 0)
			error_clean_exit_code(ERR_FORK, EXIT_FAILURE, &p);
		//ft_printf(2, "%d", p->pids[p->cmd_num]);
		if (p->pids[p->cmd_num] == 0)
		{
			child(p); //child 1 for cmd1 (right end of pipe, writing end)
			close_fds(p->cur_fd, p->fd[1], p);
		}
		else if (close(p->fd[1]) == -1)
		{
			//ft_printf(2, "Here2");
			//close_fds(fd_in, p->fd[1], p);
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		}
		//close_fds(p->cur_fd, p->fd[1], p);
		p->cur_fd = p->fd[0];
		p->cmd_num++;
	}
	if (close(p->fd[0]) == -1)
	{
		//close_fds(fd_in, p->fd[1], p);
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
	}
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
		//printf("pid_counter: %d, p->pids[pid_counter]: %d\n", pid_counter, p->pids[pid_counter]);
		if (waitpid(p->pids[pid_counter], &status, 0) == -1)
			error_clean_exit_code(ERR_WAITPID, EXIT_FAILURE, &p);
		pid_counter++;
	}
	return ((status >> 8) & 255);
}
