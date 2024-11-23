/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:43:23 by azinchen          #+#    #+#             */
/*   Updated: 2024/11/22 14:43:25 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

void	missing_quote(void)//can I put the quote as an input and show which is missing?
{
	printf("missing quote");
	exit(1);
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
		missing_quote();
	return (len);
}

int	word_length(char *str)
{
	int	len;
	//if

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

//check the case with "\\ \\ \\ \\ ". Mine gives result 1, chatgpt thinks it should be 4
static int	count_words(char *str)
{
	int	i;
	int	res;

	if (!str || str[0] == '\0')
		return (0);
	res = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			res++;
			i += length_inside_quotes(&str[i]) + 2; //or 1?
		}
		else if (str[i] != ' ')
		{
			res++;
			i += word_length(&str[i]);
		}
		else
			i++;
	}
	return (res);
}
/*
static char	*one_word(char *str, int len)
{
	int	i;

	dest = (char *)ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL); //what else
	i = 0;
	//needs changes!
	while (str[start] != ' ' && str[start] != '\0')
	{
		dest[i] = str[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

static char **all_words(const char *str)
{
	int		i;
	int		j;
	int		index;

	index = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else
		{
			j = 0;
			while (str[i + j] != ' ' && str[i + j] != '\0')
				j++;
			array[index] = (char *)malloc((j + 1) * sizeof(char));
			if (!array[index])
			{
				clean_arr(&array);
				return (NULL);
			}
			one_word(str, i);
			i = i + j;
			index++;
		}
	}
	return (array);
}
*/
char	**split_cmd(char *cmd)
{
	char	**res;
	int		count;

	if (!cmd)
		return (NULL);
	count = count_words(cmd);
	//if (count == 0)
	//	return (NULL);
	res = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!res)
		return (NULL);
	//if (ft_array(res, cmd) == -1)
	//	return (NULL);
	res[count] = 0;
	return (res);
}
/*
int	main(void)
{
	char *str;

	str = "\\ \\ \\ \\ ";
	printf("words in a string: %d\n", count_words(str));
}*/
