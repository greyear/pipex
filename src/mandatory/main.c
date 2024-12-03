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

	// printf("argc: %d\n", argc);
	if (argc != 5)
	{
		// ft_printf(2, "argc: %d\n", argc);
		// ft_printf(2, "argv: %s\n", argv[1]);
		// ft_putstr_fd("test main\n", 2);
		args_number_error();
	}
	// printf("argc after check: %d\n", argc);
	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		error_exit_code(ERR_MALLOC, EXIT_FAILURE);
	p->argc = argc;
	/*printf("argc: %d\n", argc);
	for (int i = 0; i < argc; i++)
    	printf("argv[%d]: %s\n", i, argv[i]);*/
	p->argv = argv;
	p->envp = envp;
	/*for (int i = 0; p->envp[i]; i++)
	{
		ft_printf(2, "envp[%d]: %s\n", i, p->envp[i]);
	}*/
	p->pids = (pid_t *)malloc((p->argc - 3) * sizeof(pid_t)); //calloc?
	if (!p->pids)
		error_clean_exit_code(ERR_MALLOC, EXIT_FAILURE, &p);
	//printf("Allocated p->pids for %d processes\n", p->argc - 3); //delete
	status = waiting(p);
	//happy path freeing
	return (status);
}
