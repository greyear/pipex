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

# include "../../libft/include/libft.h"
# include "../../libft/include/ft_printf.h"
# include "../../libft/include/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# define ERR_MALLOC "memory allocation failed"
# define ERR_FORK "fork function failed"
# define ERR_PIPE "pipe creation failed"
# define ERR_DUP2 "dup2 function failed"
# define ERR_EXECVE "execve failed"
# define ERR_OPEN "opening failed"
# define ERR_CLOSE "closing failed"
# define NO_FILE_DIR "no such file or directory"
# define ZSH_NO_FILE "zsh: no such file or directory:"
# define CMD_NOT_FOUND "zsh: command not found:"
# define PERM_DENIED "zsh: permission denied:"

# define CMD_EXEC 126
# define CMD_NF 127

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	*pids;
	char	**cmds;
	int		cmd_num;
	int		fd[2];
	int		cur_fd;
	int		is_path;
	char	*path;
}	t_pipex;

//Main
void	pipex(t_pipex *p);
void	init_p(t_pipex	*p);
int		waiting(t_pipex *p);
char	**path_from_envp(t_pipex *p);
char	*find_path(char **cmd_split, t_pipex *p);
char	**split_cmd(char *cmd, t_pipex *p);
void	handle_command(char *cmd, t_pipex *p);

//Utils
void	close_fds(int fd1, int fd2);
int		length_inside_quotes(char *str, t_pipex *p);
int		word_length(char *str);

//Errors
void	args_number_error(void);
void	execve_fail(char **path, char **cmd_split, t_pipex **p);
void	cmd_error(char *reason, char *cmd, int exit_code, t_pipex **p);
void	missing_quote_error(char quote, t_pipex **p);
void	error_exit_code(char *reason, int exit_code);
void	error_clean_exit_code(char *reason, int exit_code, t_pipex **p);

//Checks
void	check_first_file(t_pipex *p);
void	check_second_file(t_pipex *p);

//Cleaners
void	clean_arr(char ***arr);
void	clean_struct(t_pipex **p);

#endif
