/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:51:12 by azinchen          #+#    #+#             */
/*   Updated: 2024/05/10 13:51:17 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_print_char(char c);
int	ft_print_str(char *str);
int	ft_print_int(int n);
int	ft_print_unsign(unsigned int n);
int	ft_print_hexa(unsigned int n, int flag);
int	ft_print_pointer(void *n);

#endif
