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

static int	open_infile(t_pipex *p)
{
	int	fd_in;

	check_first_file(p);
	fd_in = open(p->argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		close_fds(p->fd[0], p->fd[1]);
		error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p);
	}
	return (fd_in);
}

static int	open_outfile(t_pipex *p)
{
	int	fd_out;

	check_second_file(p);
	fd_out = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		close_fds(p->fd[0], p->fd[1]);
		if (close(p->cur_fd) == -1)
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p);
	}
	return (fd_out);
}

static void	child(t_pipex *p)
{
	int	fd_out;

	if (p->cmd_num == 0)
		p->cur_fd = open_infile(p);
	if (dup2(p->cur_fd, STDIN_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	if (p->cmd_num == 0)
		close(p->cur_fd);
	if (p->cmd_num == p->argc - 4)
	{
		fd_out = open_outfile(p);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
		close(fd_out);
		close_fds(p->cur_fd, p->fd[1]);
	}
	else
	{
		if (dup2(p->fd[1], STDOUT_FILENO) == -1)
			error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
		close(p->fd[1]);
	}
	close(p->fd[0]);
	handle_command(p->argv[p->cmd_num + 2], p);
	exit(EXIT_SUCCESS);
}

void	pipex(t_pipex *p)
{
	while (p->cmd_num < p->argc - 3)
	{
		if (pipe(p->fd) == -1)
			error_clean_exit_code(ERR_PIPE, EXIT_FAILURE, &p);
		p->pids[p->cmd_num] = fork();
		if (p->pids[p->cmd_num] < 0)
			error_clean_exit_code(ERR_FORK, EXIT_FAILURE, &p);
		if (p->pids[p->cmd_num] == 0)
			child(p);
		close_fds(p->cur_fd, p->fd[1]);
		p->cur_fd = p->fd[0];
		p->cmd_num++;
	}
	if (close(p->cur_fd) == -1)
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
}

int	waiting(t_pipex *p)
{
	int	status;
	int	exit_code;
	int	pid_counter;

	pipex(p);
	pid_counter = 0;
	while (pid_counter < p->cmd_num)
	{
		if (wait(&status) == p->pids[p->cmd_num - 1])
			exit_code = status;
		pid_counter++;
	}
	return ((exit_code >> 8) & 255);
}
