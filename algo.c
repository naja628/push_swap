#include "t_emul.h"
#include "t_destack.h"
#include "algo.h"

/****** DEBUG ****/
#include <stdio.h>
void print_stack(t_destack *t)
{
	t_node *it = t->top;

	while (it)
	{
		printf("%d_", it->x);
		it = it->down;
	}
	printf("\n");
}
/*	END DEBUG */

static void	ft_sort2orless(t_emul *t, t_aorb aorb)
{
	t_destack	*u;
	
	u = ft_getaorb(t, aorb);
	if (!ft_atleast_n(u, 2))
		return ;
	if (ft_nth(u, 0) > ft_nth(u, 1))
		ft_sx(t, aorb);
}

static void	ft_split(t_emul *t, t_aorb aorb, size_t n)
{
	n /= 2;
	while (n)
	{
		ft_px(t, ft_other(aorb));
		--n;
	}
}

static void	ft_merge(t_emul *t, t_aorb aorb, size_t naorb, size_t nbora)
{
	t_destack	*taorb;
	t_destack	*tbora;

	if (nbora == 0)
		return ;
	taorb = ft_getaorb(t, aorb);
	tbora = ft_getaorb(t, ft_other(aorb));
	if (naorb == 0 || ft_nth(taorb, 0) > ft_nth(tbora, 0))
	{
		ft_px(t, aorb);
		--nbora;
	}
	else 
		--naorb;
	if (nbora != 0)
		ft_rx(t, aorb);
	ft_merge(t, aorb, naorb, nbora);
	if (nbora != 0)
		ft_rrx(t, aorb);
}

void	ft_subpb_szs(size_t *buff, size_t n)
{
	unsigned int	i;

	buff[0] = n / 4;
	buff[1] = n / 4;
	buff[2] = n / 2;
	n -= buff[0] + buff[1] + buff[2];
	i = 2;
	while (n)
	{
		++(buff[i--]);
		--n;
	}
}	

/* sort the n topmost element of the stack a or b 
 * expects n to be no greater than the size of the 
 * stack a or b 
 * and a valid t_emul struct */
void	ft_merge_sort(t_emul *t, t_aorb aorb, size_t n)
{
	//print_stack(ft_getaorb(t, aorb));
	size_t	szs[3];

	ft_subpb_szs(szs, n);
	if (ft_nfstsorted(ft_getaorb(t, aorb), n))
		return ;
	if (n <= 2)
	{
		ft_sort2orless(t, aorb);
		return ;
	}
	ft_split(t, aorb, szs[0] + szs[1]);
	ft_merge_sort(t, ft_other(aorb), szs[0]);
	ft_merge_sort(t, aorb, szs[1]);
	ft_merge(t, ft_other(aorb), szs[0], szs[1]);
	ft_merge_sort(t, aorb, szs[2]);
	ft_merge(t, aorb, szs[2], szs[0] + szs[1]);
}
