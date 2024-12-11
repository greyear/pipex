/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:03:57 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/14 18:03:59 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	args_number_error(void)
{
	if (ft_putstr_fd("Invalid number of arguments\n", 2) == -1)
	{
		perror("write error");//specify?
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

//do we need to write pipex in error messages?

void	execve_fail(char *path, char **cmd_split, t_pipex **p)
{
	if (ft_printf(2, "%s %s\n", ERR_EXECVE, cmd_split[0]) == -1)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}
	free(path);
	path = NULL; //check if I need it
	//close_fds(p->cur_fd, p->fd[1], p); //Can I put it inside cmd_error function?
	clean_struct(p);
	exit(EXIT_CMD_CANNOT_EXECUTE); //or 127?
}

void	cmd_error(char *reason, char *cmd, int exit_code, t_pipex **p)
{
	if (ft_printf(2, "%s %s\n", reason, cmd) == -1)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}
	clean_struct(p); //move this to be the 1st instruction
	//close_fds((*p)->cur_fd, (*p)->fd[1], *p);
	exit(exit_code);
}

void	file_error(char *reason, char *file, int exit_code, t_pipex **p) // **?
{
	if (ft_printf(2, "%s %s", reason, file) == -1)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}
	clean_struct(p);
	exit(exit_code);
}

void	missing_quote_error(char quote)
{
	if (ft_printf(2, "Pipex: missing quote: %c\n", quote) == -1)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	error_code(char *reason)
{
	if (ft_putstr_fd(reason, 2) == -1)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}
}

void	error_exit_code(char *reason, int exit_code)
{
	if (ft_putstr_fd(reason, 2) == -1)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}
	exit(exit_code);
}

void	error_clean_exit_code(char *reason, int exit_code, t_pipex **p) //do I rly need ** everywhere?
{
	clean_struct(p);
	perror(reason); //why perror here and fd_putstr_fd there?
	exit(exit_code);
}
