/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:03:38 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/14 18:03:40 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int is_path_set(t_pipex *p, char *envp[])
{
	int	i;

	if (!envp)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp("envp[i]", "PATH=", 5) == 0)
			p->is_path = 1; //where to set value to 0?
		i++;
	}
	return (0);
}
