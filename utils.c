#include <unistd.h>
#include "utils.h"

void	ft_putstr_endl(char const *s)
{
	while (*s)
		write(1, s++, 1);
	write (1, "\n", 1);
}

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	else 
		return (x);
}
