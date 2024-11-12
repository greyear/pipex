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

#include "../include/pipex.h"

int main(int argc, char* argv[], char *envp[])
{
	if (argc != 5)
		args_number_error();
	while (*envp != NULL)
	{
		printf("%s\n", *envp++); 
	}
	return 0; 
} 
