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
	//ft_putstr_fd("test\n", 2);
	if (ft_putstr_fd("AAAAInvalid number of arguments\n", 2) == -1)
	{
		perror("write error");//specify?
		exit(EXIT_FAILURE);
	}		
	//perror()
	exit(EXIT_FAILURE);
}

void	execve_fail(char *reason, char *path, char **cmd_split)
{
	if (ft_putstr_fd(reason, 2) == -1)
	{
		perror("write error");//specify?
		exit(EXIT_FAILURE);
	}
	if (ft_putstr_fd(*cmd_split, 2) == -1)
	{
		perror("write error");//specify?
		exit(EXIT_FAILURE);
	}
	free(path);
	path = NULL; //check if I need it
	//clean_arr(&cmd_split);
	exit(EXIT_CMD_CANNOT_EXECUTE); //or 127?
}

void	cmd_error(char *reason, char **cmd_split, int if_clean)
{
	ft_printf(2, "Pipex: %s, %s", cmd_split[0], reason);
	if (if_clean)
		ft_putstr_fd(*cmd_split, 2);
		//clean_arr(&cmd_split);
	exit(EXIT_CMD_NOT_FOUND);
}

void	file_error(char *reason, char *file, int exit_code, t_pipex **p) // **?
{
	if (p)
		ft_printf(2, "Pipex: %s, %s", reason, file);
	//clean_struct(p);
	exit(exit_code);
}

void	missing_quote(char quote)
{
	if (ft_printf(2, "Pipex: missing quote: %c\n", quote) == -1)
	{
		perror("write error");//specify?
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	error_code(char *reason)
{
	if (ft_putstr_fd(reason, 2) == -1)
	{
		perror("write error");//specify?
		exit(EXIT_FAILURE);
	}
}

void	error_exit_code(char *reason, int exit_code)
{
	if (ft_putstr_fd(reason, 2) == -1)
	{
		perror("write error");//specify?
		exit(EXIT_FAILURE);
	}
	exit(exit_code);
}

void	error_clean_exit_code(char *reason, int exit_code, t_pipex **p) //do I rly need ** everywhere?
{
	printf("Calling clean_struct\n");
	//clean_struct(p);
	if (p)
		perror(reason); //why perror here and fd_putstr_fd there?
	exit(exit_code);
}
