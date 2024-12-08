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
# define ERR_EXECVE "Execve failed"
# define ERR_OPEN "Opening failed" //do I need to specify?
# define ERR_CLOSE "Closing failed"
# define NO_FILE_DIR "No such file or directory"
# define ZSH_NO_FILE "zsh: no such file or directory: "
# define ZSH_PERM "zsh: permission denied: "

# define EXIT_CMD_CANNOT_EXECUTE 126
# define EXIT_CMD_NOT_FOUND 127

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
char	**split_cmd(char *cmd);
void	handle_command(char *cmd, t_pipex *p);

//Utils
void	close_fds(int fd1, int fd2, t_pipex *p);

//Errors
void	args_number_error(void);
void	execve_fail(char *reason, char *path, char **cmd_split, t_pipex **p);
void	cmd_error(char *reason, char *cmd, int if_clean, t_pipex **p);
void	file_error(char *reason, char *file, int exit_code, t_pipex **p);
void	missing_quote_error(char quote);
void	error_code(char *reason);
void	error_exit_code(char *reason, int exit_code);
void	error_clean_exit_code(char *reason, int exit_code, t_pipex **p);

//Checks
void	check_first_file(t_pipex *p);
void	check_second_file(t_pipex *p);

//Cleaners
void	clean_arr(char ***arr);
void	clean_struct(t_pipex **p);

//Utils
void	close_fds(int fd1, int fd2, t_pipex *p);

#endif
