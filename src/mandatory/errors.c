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
	//perror()
	exit(EXIT_FAILURE);
}

void	execve_fail(char *path, char **cmd_split)
{
	//what should be printed??????????????????
	if (ft_putstr_fd("pipex: ........", 2) == -1)
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
	clean_arr(&cmd_split);
	exit(EXIT_CMD_CANNOT_EXECUTE); //or 127?
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
	clean_struct(p);
	perror(reason);
	exit(exit_code);
}
