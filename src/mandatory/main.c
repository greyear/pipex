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

void	init_p(t_pipex	*p)
{
	p->cmds = NULL;
	p->cmd_num = 0;
	p->cur_fd = -1;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*p;
	int		status;

	if (argc != 5)
		args_number_error();
	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		error_exit_code(ERR_MALLOC, EXIT_FAILURE);
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
	init_p(p);
	p->pids = (pid_t *)malloc((p->argc - 3) * sizeof(pid_t)); //calloc?
	if (!p->pids) //clean p
		error_clean_exit_code(ERR_MALLOC, EXIT_FAILURE, &p);
	status = waiting(p);
	clean_struct(&p);
	return (status);
}

// ft_printf(2, "argc: %d\n", argc);
/*for (int i = 0; i < argc; i++)
	printf("argv[%d]: %s\n", i, argv[i]);*/
/*for (int i = 0; p->envp[i]; i++)
	ft_printf(2, "envp[%d]: %s\n", i, p->envp[i]);*/
// ft_putstr_fd("test main\n", 2);
//printf("Allocated p->pids for %d processes\n", p->argc - 3); //delete
