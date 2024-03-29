#include "t_emul.h"
#include "t_destack.h"
#include "algo.h"
#include "sort_utils.h"

//should split be here instead?

static void	ft_merge_atbot(t_emul *t, t_aorb aorb, size_t *szs, int rev)
{
	t_destack	*taorb;
	t_destack	*tbora;

	if (szs[A] == 0 && szs[B] == 0)
		return ;
	taorb = ft_getaorb(t, aorb);
	tbora = ft_getaorb(t, ft_other(aorb));
	if (szs[aorb] == 0 || (szs[!aorb] != 0 
			&& ft_less(ft_nth(tbora, 0), ft_nth(taorb, 0), rev)))
	{
		ft_px(t, aorb);
		--(szs[!aorb]);
	}
	else 
		--(szs[aorb]);
	ft_rx(t, aorb);
	ft_merge_atbot(t, aorb, szs, rev);
}

static void	ft_merge_attop(t_emul *t, t_aorb aorb, size_t *szs, int rev)
{
	t_destack	*taorb;
	t_destack	*tbora;

	if (szs[A] == 0 && szs[B] == 0)
		return ;
	taorb = ft_getaorb(t, aorb);
	tbora = ft_getaorb(t, ft_other(aorb));
	if (szs[aorb] == 0 || (szs[!aorb] != 0
				&& ft_less(ft_rnth(taorb, 0), ft_nth(tbora, 0), rev)))
	{
		ft_px(t, aorb);
		--(szs[!aorb]);
	}
	else
	{
		ft_rrx(t, aorb);
		--(szs[aorb]);
	}
	ft_merge_attop(t, aorb, szs, rev);
}

/* Merging must happen according to the following table.
 * (eg to get (opt 0) in stack a, after splitting
 * the half in a must be sorted using opt ATBOT
 * and the half in b using opt REVO)
 * table :
 * opt 			to : from
 * (0)			->| : |->, <-|
 * REVO			<-| : |<-, ->|
 * ATBOT		|-> : ->|, ->|
 * REVO | ATBOT	|<- : <-|, <-| */
void	ft_decomp_opt(int *opts, int opt, t_aorb to)
{ 
	if (opt & ATBOT)
	{
		opts[!to] = (opt & REVO);
		opts[to] = (opt & REVO);
	}
	else
	{
		opts[to] = ATBOT | (opt & REVO);
		opts[!to] = (~opt & REVO);
	}
}

/* sort the n topmost element of the stack a 
 * and put them at the top or bottom (depending on (opt & ATBOT))
 * of stack 'to' (in reverse order if (opt & REVO))
 * expects n to be no greater than the size of the 
 * stack a,
 * and t to be valid (not Null etc)  */
void	ft_merge_sort(t_emul *t, t_aorb to, size_t n, int opt)
{
	size_t	sub_szs[2];
	int		sub_opts[2];

	if (ft_lucky(t, to, n, opt))
		return ;
	if (n <= 3)
	{
		if (to == B)
			ft_split(t, B, n);
		ft_sort_topmost3max(t, to, n, opt);
		return ;
	}
	sub_szs[B] = n / 2;
	sub_szs[A] = n - n / 2;
	ft_decomp_opt(sub_opts, opt, to);
	ft_merge_sort(t, B, sub_szs[B], sub_opts[B]);
	ft_merge_sort(t, A, sub_szs[A], sub_opts[A]);
	if (opt & ATBOT)
	   ft_merge_atbot(t, to, sub_szs, (opt & REVO));
	else
		ft_merge_attop(t, to, sub_szs, (opt & REVO));
}
