
#ifndef PIPEX_H
# define PIPEX_H

//check if needed?
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	*pids;
	char	*cmds;
	int		fd[2];
}	t_pipex;

//Errors
void	args_number_error(void);

#endif