/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:18:11 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/14 19:18:13 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_first_file(char **argv, t_pipex *p)
{
	if (access(argv[1], F_OK) == -1)
		//file doesn't exist
	if (access(argv[1], R_OK) == -1)
		//no reading permission
	
}

int	check_second_file(int argc, char **argv, t_pipex *p)
{
	if (access(argv[argc - 1], F_OK) == -1)
		//file doesn't exist
	if (access(argv[argc - 1], W_OK) == -1)
		//no writing permission
	
}
