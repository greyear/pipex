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
	ft_putstr_fd("Invalid number of arguments\n", 2);//specify?
	exit(EXIT_FAILURE);
}

void	error(char *reason)
{
	perror(reason);
	exit(EXIT_FAILURE);
}
