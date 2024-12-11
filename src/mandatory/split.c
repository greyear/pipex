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

#include "pipex.h"

//check the case with "\\ \\ \\ \\ ".
//Mine gives 1, chatgpt thinks it should be 4
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
			i += length_inside_quotes(&str[i]) + 2;
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

static char	*one_word(char *str, int len)
{
	int		i;
	int		j;
	char	*word;

	word = (char *)ft_calloc((len + 1), sizeof(char));
	if (!word)
		return (NULL); //what else
	i = 0;
	j = 0;
	//what about $ symbol and ` symbol?
	while (i < len)
	{
		if (ft_isquote(str[0]) && str[i] == str[0])
			i++;
		else if (!ft_isquote(str[0]) && (str[i] == ' ' || str[i] == '\\'))
			i++;
		else
			word[j++] = str[i++];
	}
	word[j] = '\0';
	return (word);
}

static char	**all_words(char *str, int count)
{
	int		w;
	int		len;
	char	**array;

	array = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!array)
		return (NULL);
	w = 0;
	while (*str && w < count)
	{
		if (*str == ' ')
			str++;
		if (ft_isquote(*str))
			len = length_inside_quotes(str) + 2;
		else
			len = word_length(str);
		array[w] = one_word(str, len);
		if (!array[w])
		{
			clean_arr(&array);
			return (NULL);
		}
		str += len;
		w++;
	}
	return (array);
}

char	**split_cmd(char *cmd)
{
	char	**res;
	int		count;

	if (!cmd || *cmd == '\0')
		return (NULL);
	count = count_words(cmd);
	if (count == 0)
		return (NULL);
	res = all_words(cmd, count);
	if (!res)
		return (NULL);
	return (res);
}
