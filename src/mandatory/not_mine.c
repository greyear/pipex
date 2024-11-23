#include <stdio.h>
#include <stdlib.h>

void	missing_quote(void)//can I put the quote as an input and show which is missing?
{
	printf("missing quote");
	exit(1);
}

int	skip_quotes(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] != quote)
	{
		missing_quote();
	}
	return (i);
}

int	skip_word(char *str, int i)
{
	while (str[i] && str[i] != 32 && str[i] != 34 && str[i] != 39)
	{
		if (str[i] == '\\' && str[i + 1] != '\0')
			i += 2;
		else
			i++;
	}
	return (i);
}

static int	count_words(char *command)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == 39 || command[i] == 34)
		{
			words++;
			i = skip_quotes(command, i) + 1;
		}
		else if (command[i] != 32)
		{
			words++;
			i = skip_word(command, i);
		}
		else
			i++;
	}
	return (words);
}

int	main(void)
{
	char *str;

	str = "\\ \\ \\ \\ ";
	printf("words in a string: %d\n", count_words(str));
}
