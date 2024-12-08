/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:12:33 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/15 15:12:35 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_arr(char ***arr)
{
	int	i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
		{
			free((*arr)[i]);
			i++;
		}
		free(*arr);
		*arr = NULL;
	}	
}
/*
static void	clean_arr2(char **arr)
{
	int	i;

	i = 0;
	if (*arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}	
}*/
void	clean_struct(t_pipex **p)
{
	if (!p || !*p)
		return ;
	if ((*p)->pids) //is this valid?
	{
		free((*p)->pids);
		(*p)->pids = NULL;
	}
	if ((*p)->cmds)
	{
		clean_arr(&((*p)->cmds));
		(*p)->cmds = NULL;
	}
	/*if ((*p)->cmds)
		clean_arr(&((*p)->cmds));*/
	/*if ((*p)->cmds)
		clean_arr2((*p)->cmds);
	(*p)->cmds = NULL;*/
	// what else
	free(*p);
	*p = NULL;
}
