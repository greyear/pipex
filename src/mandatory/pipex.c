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

//debug: "args": ["infile", "grep a1", "wc -w", "outfile"],

static int	open_infile(t_pipex *p)
{
	int	fd_in;

	check_first_file(p);
	fd_in = open(p->argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		//ft_printf(2, "cmd: %d: SHOULD BE PERM DENIED ISSUE\n", p->cmd_num);
		close_fds(p->fd[0], p->fd[1], p);
		error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p);
	}
	return (fd_in);
}

static int	open_outfile(t_pipex *p)
{
	int fd_out;

	check_second_file(p);
	fd_out = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		close_fds(p->fd[0], p->fd[1], p);
		if (close(p->cur_fd) == -1)
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		//ft_printf(2, "cmd: %d: ERR_OPEN\n", p->cmd_num);
		error_clean_exit_code(ERR_OPEN, EXIT_FAILURE, &p);
	}
	return (fd_out);
}

static void	child(t_pipex *p)
{
	int	fd_out;

	if (p->cmd_num == 0) //the first process
	{
		p->cur_fd = open_infile(p);
		//ft_printf(2, "cmd: %d: cur_fd opened infile: %d\n", p->cmd_num, p->cur_fd);
	}
	if (dup2(p->cur_fd, STDIN_FILENO) == -1)
		error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
	if (p->cmd_num == 0)
		close(p->cur_fd);
		

	if (p->cmd_num == p->argc - 4) //the last process
	{
		fd_out = open_outfile(p);
		//ft_printf(2, "cmd: %d: fd_out opened outfile: %d\n", p->cmd_num, fd_out);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
		if (close(fd_out) == -1)
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		close(p->fd[1]);
		close(p->cur_fd);
		//printf("cmd: %d: fd_out will close after dup2: %d\n", p->cmd_num, fd_out);
	}
	else //all except the last
	{
		if (dup2(p->fd[1], STDOUT_FILENO) == -1)
			error_clean_exit_code(ERR_DUP2, EXIT_FAILURE, &p);
		close(p->fd[1]);
	}

	//printf("cmd: %d: fd0 will close before exec: %d\n", p->cmd_num, p->fd[0]);
	//ft_printf(1, "%s[%d] fd[0] = %d\n", p->argv[p->cmd_num + 2], p->cmd_num, p->fd[0]);
	if (close(p->fd[0]) == -1)
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
	//ft_printf(1, "%s[%d] fd[0] = %d\n", p->argv[p->cmd_num + 2], p->cmd_num, p->fd[0]);
	handle_command(p->argv[p->cmd_num + 2], p);
	exit(EXIT_SUCCESS);
}

void	pipex(t_pipex *p)
{
	while (p->cmd_num < p->argc - 3)
	{
		if (pipe(p->fd) == -1)
			error_clean_exit_code(ERR_PIPE, EXIT_FAILURE, &p);
		//ft_printf(2, "cmd: %d: fd0 opened after pipe: %d\n", p->cmd_num, p->fd[0]);
		//ft_printf(2, "cmd: %d: fd1 opened after pipe: %d\n", p->cmd_num, p->fd[1]);

		p->pids[p->cmd_num] = fork();
		if (p->pids[p->cmd_num] < 0)
			error_clean_exit_code(ERR_FORK, EXIT_FAILURE, &p);
		if (p->pids[p->cmd_num] == 0)
			child(p);
		//printf("cmd: %d: cur_fd will be closed after child: %d\n", p->cmd_num, p->cur_fd);
		//printf("cmd: %d: fd1 will be closed after child: %d\n", p->cmd_num, p->fd[1]);
		//fflush(stdout);
		close_fds(p->cur_fd, p->fd[1], p);
		p->cur_fd = p->fd[0];
		//ft_printf(2, "cmd: %d: cur_fd has turned into: %d at the end of pipex\n", p->cmd_num, p->cur_fd);
		p->cmd_num++;
	}
	//ft_printf(2, "---->fd0: %d<--- \n", p->fd[0]);
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
		//printf("pid_counter: %d, p->pids[pid_counter]: %d\n", pid_counter, p->pids[pid_counter]);
		// if (waitpid(p->pids[pid_counter], &status, 0) == -1)
		// 	error_clean_exit_code(ERR_WAITPID, EXIT_FAILURE, &p);
		if (wait(&status) == p->pids[p->cmd_num - 1])
			exit_code = status;
		pid_counter++;
	}
	//return ((status >> 8) & 255);
	return ((exit_code >> 8) & 255);
}
