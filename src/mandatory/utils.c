/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:13:17 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/15 15:13:19 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

int	length_inside_quotes(char *str)
{
	char	any_quote;
	int		len;

	if (!str || (*str != '\'' && *str != '\"'))
		return (0);
	any_quote = *str;
	len = 0;
	str++;
	while (*str != '\0' && *str != any_quote)
	{
		len++;
		str++;
	}
	if (*str != any_quote)
		missing_quote_error(any_quote);
	return (len);
}

int	word_length(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != ' ' && *str != '\'' && *str != '\"')
	{
		if (*str == '\\' && *(str + 1) != '\0')
		{
			len += 2;
			str += 2;
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}
