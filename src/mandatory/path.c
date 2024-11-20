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

static void	handle_command(char *cmd, t_pipex *p)
{
	char	**cmd_split;
	char	*path;

	cmd_split = custom_split(cmd);
	if (!cmd_split)
		//clean?
	path = find_path(cmd_split, p);
	if (!path)
		//error
	execve(path, cmd_split, p->envp); //store envp?
	//if execve failed what to do?
}

char	**path_from_envp(t_pipex *p)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], "PATH=", 5) == 0)
			return (ft_split(p->envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*make_full_path(char *one_path, char *cmd)
{
	char	*premade;
	char	*made;

	premade = ft_strjoin(one_path, "/");
	if (!premade)
		//malloc protection
	made = ft_strjoin(premade, cmd);
	if (!made)
		//another protection
	//free cmd?
	return (made);
}

char	*find_path(char **cmd_split, t_pipex *p)
{
	char	*res;
	char	**path;
	int		i;

	if (ft_strchr(cmd_split[0], '/') != NULL)
	{
		if (access(cmd_split, F_OK) == 0)
			return (ft_strdup(cmd_split));
		else
			//error: "No such file or directory"
	}
	path = path_from_envp(p);
	//check (?)
	i = 0;
	while (path[i])
	{
		res = make_full_path(path[i], cmd_split[0]);
		if (!res)
			//protection
		if (access(res, F_OK) == 0)
			return (res);
		//I think freeing paths shouldn't be here
		i++;
	}
	clean_arr(&path);;
	return (NULL);
}



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

/usr/local/sbin:
/usr/local/bin:
/usr/sbin:
/usr/bin:
/sbin:
/bin:
/snap/bin


/usr/local/bin:
/usr/bin:
/bin:
/usr/sbin:
/sbin


/bin:
/usr/bin:
/sbin:
/usr/sbin:
/usr/local/bin
