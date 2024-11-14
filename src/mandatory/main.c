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
#include <time.h>
#include <string.h>

int main(int argc, char* argv[], char *envp[])
{
	t_pipex	*p;
	if (argc != 5)
		args_number_error();

	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		error(ERR_MALLOC);
	return 0; 
}

//simulation of: "ping -c 5 google.com | grep rtt"
//./pipex file1 cmd1 cmd2 file2
/*
int	main(int argc, char *argv[])
{
	int	fd[2];
	int	pid1;
	int pid2;

	if (pipe(fd) == -1)
		return (1);

	pid1 = fork();
	if (pid1 < 0)
		return (1);
	
	if (pid1 == 0) //child 1 for ping (right end of pipe, writing end)
	{
		dup2(fd[1], STDOUT_FILENO); //it takes fd[1] and duplicates it into stout
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}

	//bc of execlp (which replaces everything in the process) we don't need "else", cause everything will be in main
	pid2 = fork();
	if (pid2 == 0) //child 2 for grep (left end of pipe, reading end)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}*/
