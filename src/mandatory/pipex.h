
#ifndef PIPEX_H
# define PIPEX_H

//check if needed?
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
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
# define ERR_CLOSE "Closing failed"

typedef struct s_pipex
{
	pid_t	*pids;
	char	*cmds;
	int		fd[2];
	char	*path;
}	t_pipex;

//Errors
void	args_number_error(void);
void	error(char *reason);

#endif