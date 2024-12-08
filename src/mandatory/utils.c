/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:13:17 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/15 15:13:19 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int fd1, int fd2, t_pipex *p)
{
	if (fd1 != -1)
	{
		if (close(fd1) == -1)
		{
			printf("TO CLOSE---->fd1: %d<--- \n", fd1);
			fflush(stdout);
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		}
	}
	if (fd2 != -1)
	{
		if (close(fd2) == -1)
		{
			printf("TO CLOSE---->fd2: %d<--- in cmd %d\n",fd2, p->cmd_num);
			fflush(stdout);
			error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
		}
	}
	
}

//vot slomalsya perviy close, i chto so vtorym?
