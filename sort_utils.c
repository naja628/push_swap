#include "sort_utils.h"
#include "t_emul.h"

int	ft_lucky(t_emul *t, t_aorb to, size_t n, int opt)
{
	t_node	*it;
	t_node	*down;

	if (to == B)
		return (0);
	it = ft_getaorb(t, A)->top;
	if (opt & ATBOT)
		it = ft_getaorb(t, A)->bot;
	while (n > 1)
	{
		if (opt & ATBOT)
			it = it->up;
		down = it->down;
		if (ft_less(down->x, it->x, (opt & REVO)))
			return (0);
		--n;
		if (!(opt & ATBOT))
			it = it->down;
	}
	return (1);
}


int	ft_less(int x, int y, int rev)
{
	if (rev)
		return (x > y);
	else 
		return (x < y);
}

void	ft_split(t_emul *t, t_aorb to, size_t n)
{
	while (n)
	{
		ft_px(t, to);
		--n;
	}
}
