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
	if (close(fd1) == -1)
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
	if (close(fd2) == -1)
		error_clean_exit_code(ERR_CLOSE, EXIT_FAILURE, &p);
}

//vot slomalsya perviy close, i chto so vtorym?
