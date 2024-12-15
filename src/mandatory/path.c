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

void	handle_command(char *cmd, t_pipex *p)
{
	char	*path;

	p->cmds = split_cmd(cmd);
	if (!p->cmds)
		cmd_error(CMD_NOT_FOUND, cmd, EXIT_CMD_NOT_FOUND, &p); //The error msg in real bash looks different, it says about the previous one
	path = find_path(p->cmds, p);
	if (!path)
		cmd_error(CMD_NOT_FOUND, p->cmds[0], EXIT_CMD_NOT_FOUND, &p);
	execve(path, p->cmds, p->envp);
	execve_fail(path, p->cmds, &p);
}

//if (ppx->cmd_args[0] && ft_strncmp(ppx->cmd_args[0], "exit", 4) == 0) - exit(ft_atoi(ppx->cmd_args[1]));
//is a directory

char	**path_from_envp(t_pipex *p)
{
	int	i;

	if (!p->envp)
		return (0); //should I throw an error here?
	i = 0;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], "PATH=", 5) == 0) //strcmp if empty argument?
			return (ft_split(p->envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

static char	*make_full_path(char *one_path, char *cmd)
{
	char	*premade;
	char	*made;

	premade = ft_strjoin(one_path, "/");
	if (!premade)
		return (NULL);
	made = ft_strjoin(premade, cmd);
	if (!made)
	{
		free(premade);
		return (NULL);
	}
	free(premade);
	return (made);
}

char	*find_path(char **cmd_split, t_pipex *p)
{
	char	*res;
	char	**path;
	int		i;

	if (ft_strchr(cmd_split[0], '/') != NULL)
	{
		if (access(cmd_split[0], F_OK) == 0)
		{
			if (access(cmd_split[0], X_OK) == -1)
				cmd_error(PERM_DENIED, cmd_split[0], EXIT_CMD_CANNOT_EXECUTE, &p);
			return (ft_strdup(cmd_split[0]));
		}
		else
			cmd_error(NO_FILE_DIR, cmd_split[0], EXIT_CMD_NOT_FOUND, &p);
	}
	path = path_from_envp(p);
	if (!path)
		return (NULL); //clean?
	i = 0;
	while (path[i])
	{
		res = make_full_path(path[i], cmd_split[0]);
		if (!res)
		{
			clean_arr(&path);
			error_clean_exit_code(ERR_MALLOC, EXIT_FAILURE, &p);
		}
		if (access(res, F_OK) == 0)
		{
			clean_arr(&path);
			return (res);
		}	
		free(res);
		i++;
	}
	clean_arr(&path);
	return (NULL);
}

/*
Взяли команду как строку, разделили ее по словам, сделали массив: "ls -l /home" становится ["ls", "-l", "/home"].
Проверили, есть ли в этом массиве / (путь )
Если есть: 
	проверили, исполняется ли команда сама по себе - если да, вернули ее, если нет, выбросили ошибку, так как команда содержит путь, но некорректный

Поискали, есть ли среди envp PATH=, если есть - вернули сплит массив путей, разделенных :, например, ["/usr/local/bin", "/usr/bin", "/bin"].
									если нет - выбросили ошибку
Собрали весь путь таким образом для каждого пути: части пути, соединенные через / плюс сама команда.
Получили несколько вариантов
/usr/bin/ls
/bin/ls
Для каждой такой сборки поочередно проверили, исполняемая ли она
Если да:
	вернули результат сборки
Если нет: ошибка
Всё освободили

В итоге вызвали execve с аргументами: итоговый путь, разделенная команда как массив строк, envp 
*/

//ft_printf(2, "CMD BROKE:>%s<\n", cmd);
//ft_printf(2, "PATH---->%s<--- \n", path);
//ft_printf(2, "PATH FROM FIND_PATH BROKE:>%s<\n", cmd);
//ft_printf(2, "cmd %d: CLOSE WHICH CAUSES PROBLEMS: cur_fd: %d and fd1: %d\n", p->cmd_num, p->cur_fd, p->fd[1]);
//ft_printf(2, "ACCESS IS NOT 0:>%s<\n", cmd_split[0]);
//ft_printf(2, "EXECVE FAILED with path---->%s<--- \n", path);
//ft_printf(2, "PATH FROM ENVP BROKE:>%s<\n", cmd_split[0]);
//ft_printf(2, "ACCESS---->%s<--- \n", res);
//ft_printf(2, "PATH---->%s<--- \n", path[0]);