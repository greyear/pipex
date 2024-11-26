/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:00:08 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/07 19:00:19 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <time.h>
#include <string.h>

int main(int argc, char* argv[], char *envp[])
{
	t_pipex	*p;
	int		status;

	if (argc != 5)
		args_number_error();
	p = (t_pipex *)malloc(sizeof(t_pipex)); //should we allocate it?
	if (!p)
		error_exit_code(ERR_MALLOC, EXIT_FAILURE);
	p->argc = argc; //and use pointer?
	p->argv = argv;
	p->envp = envp;
	p->pids = (pid_t *)malloc((p->argc - 3) * sizeof(pid_t)); //calloc?
	if (!p)
		error_clean_exit_code(ERR_MALLOC, EXIT_FAILURE, p);
	status = pipex(p);
	//freeing
	return (status);
}
