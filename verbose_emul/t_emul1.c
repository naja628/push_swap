#include "../t_emul.h"

void	ft_sa(t_emul *t)
{
	ft_putstr_endl("sa");
	ft_swap(t->a);
}

void	ft_sb(t_emul *t)
{
	ft_putstr_endl("sb");
	ft_swap(t->b);
}

void	ft_ss(t_emul *t)
{
	ft_putstr_endl("ss");
	ft_swap(t->b);
	ft_swap(t->a);
}

void	ft_pa(t_emul *t)
{
	ft_px(t, A);
}

void	ft_pb(t_emul *t)
{
	ft_px(t, B);
}
