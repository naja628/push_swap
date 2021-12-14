#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

typedef unsigned char	t_uchar;

void	ft_putstr_endl(char const *s);
int		ft_atoi_errcode(char const *s, int *errcode);
int		ft_abs(int n);
int		ft_less(int x, int y, int rev);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
