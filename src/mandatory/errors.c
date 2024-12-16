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

void	execve_fail(char **path, char **cmd_split, t_pipex **p)
{
	perror(cmd_split[0]);
	free(*path);
	*path = NULL;
	clean_struct(p);
	exit(CMD_EXEC);
}

void	cmd_error(char *reason, char *cmd, int exit_code, t_pipex **p)
{
	if (ft_printf(2, "%s %s\n", reason, cmd) == -1)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}
	clean_struct(p);
	exit(exit_code);
}

void	missing_quote_error(char quote, t_pipex **p)
{
	if (ft_printf(2, "Pipex: missing quote: %c\n", quote) == -1)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}
	clean_struct(p);
	exit(EXIT_FAILURE);
}

void	error_exit_code(char *reason, int exit_code)
{
	perror(reason);
	exit(exit_code);
}

void	error_clean_exit_code(char *reason, int exit_code, t_pipex **p)
{
	clean_struct(p);
	perror(reason);
	exit(exit_code);
}
