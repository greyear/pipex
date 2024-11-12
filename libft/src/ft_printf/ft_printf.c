/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:50:12 by azinchen          #+#    #+#             */
/*   Updated: 2024/05/10 13:50:16 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	ft_specifier(int c, va_list arg)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = ft_print_char(va_arg(arg, int));
	if (c == 's')
		len = ft_print_str(va_arg(arg, char *));
	if (c == 'p')
		len = ft_print_pointer(va_arg(arg, void *));
	if (c == 'd' || c == 'i')
		len = ft_print_int(va_arg(arg, int));
	if (c == 'u')
		len = ft_print_unsign(va_arg(arg, unsigned int));
	if (c == 'x')
		len = ft_print_hexa(va_arg(arg, unsigned int), 0);
	if (c == 'X')
		len = ft_print_hexa(va_arg(arg, unsigned int), 1);
	if (c == '%')
		len = ft_print_char('%');
	return (len);
}

static int	ft_print_specif(const char	*str, va_list arg, int i)
{
	int	len;
	int	res;

	len = 0;
	res = ft_specifier(str[i + 1], arg);
	if (res == -1)
		return (-1);
	len += res;
	return (len);
}

static int	ft_print_not_specif(const char	*str, int i)
{
	int	len;

	len = 0;
	if (write(1, &str[i], 1) == -1)
		return (-1);
	len++;
	return (len);
}

static int	ft_total(const char	*str, va_list arg)
{
	int		i;
	int		len;
	int		res;

	i = -1;
	len = 0;
	while (str[++i])
	{
		res = 0;
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				break ;
			res = ft_print_specif(str, arg, i++);
		}
		else
			res = ft_print_not_specif(str, i);
		if (res == -1)
			return (-1);
		len += res;
	}
	return (len);
}

int	ft_printf(const char	*str, ...)
{
	va_list	arg;
	int		len;

	va_start(arg, str);
	len = ft_total(str, arg);
	va_end(arg);
	return (len);
}
