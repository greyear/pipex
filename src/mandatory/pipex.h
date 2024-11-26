/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:14:22 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/14 19:14:25 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//check if needed?
# include "../../libft/include/libft.h"
# include "../../libft/include/ft_printf.h"
# include "../../libft/include/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# define ERR_WRITE "Write function failed"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_FORK "Fork function failed"
# define ERR_PIPE "Pipe creation failed"
# define ERR_DUP2 "Dup2 function failed"
# define ERR_WAITPID "Waitpid function failed"
# define ERR_OPEN "Opening failed" //do I need to specify?
# define ERR_CLOSE "Closing failed"

# define EXIT_CMD_CANNOT_EXECUTE 126
# define EXIT_CMD_NOT_FOUND 127

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	*pids;
	char	**cmds;
	int		fd[2];
	int		is_path;
	char	*path;
}	t_pipex;

//Main
int		pipex(t_pipex *p);
int		path_from_envp(t_pipex *p, char *envp[]);

//Utils
void	close_fds(int fd1, int fd2, t_pipex *p);

//Errors
void	args_number_error(void);
void	execve_fail(char *path, char **cmd_split);
void	missing_quote(char quote);
void	error_clean_exit_code(char *reason, int exit_code, t_pipex **p);

//Checks
int		check_first_file(char **argv, t_pipex *p);
int		check_second_file(int argc, char **argv, t_pipex *p);

//Cleaners
void	clean_arr(char ***arr);
void	clean_struct(t_pipex **p);

//Utils
void	close_fds(int fd1, int fd2, t_pipex *p);

#endif
