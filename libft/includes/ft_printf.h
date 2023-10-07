/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:08:12 by rshay            #+#    #+#             */
/*   Updated: 2022/12/27 04:05:21 by rshay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define CONVS "cspdiuxX%"
# define FLAGS "-0# +"
# define MINUS 0b000001
# define ZERO  0b000010
# define SHARP 0b000100
# define SPACE 0b001000
# define PLUS  0b010000
# define DOT   0b100000

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

/* flags:
1st bit = -
2nd bit = 0
3th bit = #
4th bit = space
5th bit = +
6th bit = .
*/
typedef struct s_flag
{
	unsigned char	flags;
	int				minimal_width;
	int				precision;
}				t_flag;

int	handle_conv(int fd, const char *s, va_list args, t_flag *flag);
int	handle_flags(const char *s, t_flag *flag);
int	putchar_c(int fd, char c, t_flag *flag);
int	putstr(int fd, char *str, t_flag *flag);
int	putptr(int fd, void *ptr, t_flag *flag);
int	putint(int fd, int n, t_flag *flag);
int	putui(int fd, unsigned int n, t_flag *flag);
int	putul_hex(int fd, unsigned long n, int upper, t_flag *flag);
int	fill_after(int fd, t_flag *flag, int already_printed);
int	fill_before(int fd, t_flag *flag, int nextlen);
int	putzeros(int fd, t_flag *flag, int elen, int already_printed);
int	make_compatibility(int flags);
int	hexlen(unsigned long n);

#endif
