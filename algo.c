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
		//printf("%d_", it->x);
		it = it->down;
	}
	//printf("\n");
}
/*	END DEBUG */

// opt masks
#define REVO 1
#define ATBOT 2

// goes to utils
int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	else 
		return (x);
}

static int	ft_lucky(t_emul *t, t_aorb to, size_t n, int opt)
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


// goes somewhere... maybe with the masks and ft_lucky...
int	ft_less(int x, int y, int rev)
{
	if (rev)
		return (x > y);
	else 
		return (x < y);
}
// TODO file for these funs
/* get the index of the maximum (min if rev)
 * of the 3 topmost vals of t */
static int	ft_imax3(t_destack *t, int rev)
{
	int	imax;

	if (ft_less(ft_nth(t, 1), ft_nth(t, 0), rev)
			&& ft_less(ft_nth(t, 2), ft_nth(t, 0), rev))
		imax = 0;
	else if (ft_less(ft_nth(t, 0), ft_nth(t, 1), rev) &&
			ft_less(ft_nth(t, 2), ft_nth(t, 1), rev))
		imax = 1;
	else 
		imax = 2;
	return (imax);
}


/* note : just the else part of the first if would suffice
 * (correctness wise)
 * but checking if the stack is small allows us to 
 * not temper with the time complexity of the whole algorithm...
 *
 * another solution would be to keep track of the size of the stacks
 */
void	ft_smart_rotate(t_emul *t, t_aorb aorb, int shift)
{
	int			rshift;
	t_destack	*u;

	u = ft_getaorb(t, aorb);
	if (ft_atleast_n(u, 2 * ft_abs(shift)))
			rshift = -shift;
	else 
	{
		shift %= ft_stacksz(u);
		if (shift <= 0)
			shift += ft_stacksz(u);
		rshift = ft_stacksz(u) - shift;
	}
	if (rshift < 0 || (shift <= rshift && shift >= 0))
	{
		while (--shift + 1)
			ft_rx(t, aorb);
	}
	else
	{
		while (--rshift + 1)
			ft_rrx(t, aorb);
	}
}
	
/* sort the stack a or b when sz <= 3 
 * if rev == 1 sort in reverse order
 * note : ad hoc, non-general implementation
 * when sz = 3, this function implements the following table :
 * 1 2 3 : /
 * 1 3 2 : rrx sx
 * 2 1 3 : sx
 * 2 3 1 : rrx
 * 3 1 2 : rx
 * 3 2 1 : rx sx */
static void	ft_sort3orless(t_emul *t, t_aorb aorb, int rev)
{
	t_destack	*u;
	int			imax;

	u = ft_getaorb(t, aorb);
	if (ft_stacksz(u) == 2 && ft_less(ft_nth(u, 1), ft_nth(u, 0), rev))
		ft_sx(t, aorb);
	if (!(ft_stacksz(u) == 3))
		return ;
	imax = ft_imax3(u, rev);
	if (imax == 1)
		ft_rrx(t, aorb);
	if (imax == 0)
		ft_rx(t, aorb);
	if (ft_less(ft_nth(u, 1), ft_nth(u, 0), rev))
		ft_sx(t, aorb);
}

/* note : ad hoc, non-general implementation */
static int 	ft_sorttop_helper(t_emul *t, t_aorb aorb, int rot, int rev)
{
	t_destack *u;

	u = ft_getaorb(t, aorb);
	if (rot == 0 && ft_imax3(u, rev) == 1)
	{
		ft_rx(t, aorb);
		return (ft_sorttop_helper(t, aorb, 1 + rot, rev));
	}
	if (rot <= 1 && ft_less(ft_nth(u, 1), ft_nth(u, 0), rev))
	{
		ft_sx(t, aorb);
		return (ft_sorttop_helper(t, aorb, rot, rev));
	}
	if (rot == 1
		   	&& ft_less(ft_nth(u, 0), ft_nth(u, 1), rev)
			&& ft_less(ft_nth(u, 0), ft_rnth(u, 0), rev)
			&& ft_less(ft_rnth(u, 0), ft_nth(u, 1), rev))
	{
		ft_rrx(t, aorb);
		return (ft_sorttop_helper(t, aorb, rot - 1, rev));
	}
	return (rot);
}

/* sort the topmost 3 elements of the stack a or b 
 * (if there are less than 3 elems just sort it)
 * if (opt & REVO) sort in reverse order 
 * if (opt & ATBOT) place them at the bottom
 * before rotating to the desired place this function implements the 
 * following table:
 * perm : ops - final layout (where | is the rest of the list)
 * 1 2 3 : / - 1 2 3 |
 * 1 3 2 : rx sx - 2 3 | 1
 * 2 1 3 : sx - 1 2 3 |
 * 2 3 1 : rx sx rrx sx - 1 2 3 |
 * 3 1 2 : sx rx sx - 2 3 | 1
 * 3 2 1 : sx rx sx rrx sx - 1 2 3 | */
static void	ft_sort_topmost3max(t_emul *t, t_aorb aorb, size_t n, int opt)
{
	t_destack	*u;
	int			rot;

	u = ft_getaorb(t, aorb);
	if (!ft_atleast_n(u, 4))
	{
		ft_sort3orless(t, aorb, (opt & REVO));
		return ;
	}
	rot = 0;
	if (n < 3)
	{
		if (n == 2 && ft_less(ft_nth(u, 1), ft_nth(u, 0), (opt & REVO)))
			ft_sx(t, aorb);
	}
	else 
		rot = ft_sorttop_helper(t, aorb, 0, (opt & REVO));
	if (opt & ATBOT)
		ft_smart_rotate(t, aorb, n - rot);
	else 
		ft_smart_rotate(t, aorb, 0 - rot);
}
		
// TODO file for these 5 fun
static void	ft_split(t_emul *t, t_aorb to, size_t n)
{
	while (n)
	{
		ft_px(t, to);
		--n;
	}
}

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

void	ft_subpb_szs(size_t *buff, size_t n)
{
	buff[B] = n / 2;
	buff[A] = n - n / 2;
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

/* sort the n topmost element of the stack a 
 * and put them at the top or bottom (depending on (opt & ATBOT))
 * of stack 'to' (in reverse order if (opt & REVO))
 * expects n to be no greater than the size of the 
 * stack a,
 * and t to be valid (not Null etc)  */
void	ft_merge_sort(t_emul *t, t_aorb to, size_t n, int opt)
{
	//printf("sorting %zu to %c with opt %u:\n", n, (to == A)? 'a' : 'b', opt);
	//print_stack(ft_getaorb(t, A));
	//print_stack(ft_getaorb(t, B));
	size_t	szs[2];

	if (ft_lucky(t, to, n, opt))
		return ;
	if (n <= 3)
	{
		if (to == B)
			ft_split(t, B, n);
		ft_sort_topmost3max(t, to, n, opt);
		return ;
	}
	ft_subpb_szs(szs, n);
	if (opt & ATBOT)
	{
		ft_merge_sort(t, B, szs[B], (opt & REVO));
		ft_merge_sort(t, A, szs[A], (opt & REVO));
		//printf("merging to %c\n", (to == A)? 'a' : 'b');
		ft_merge_atbot(t, to, szs, (opt & REVO));
	}
	else 
	{
		if (to == A)
		{
			ft_merge_sort(t, ft_other(to), szs[ft_other(to)], (~opt & REVO));
			ft_merge_sort(t, to, szs[to], ATBOT | (opt & REVO));
		}
		else 
		{
			ft_merge_sort(t, to, szs[to], ATBOT | (opt & REVO));
			ft_merge_sort(t, ft_other(to), szs[ft_other(to)], (~opt & REVO));
		}
		//printf("merging to %c\n", (to == A)? 'a' : 'b');
		ft_merge_attop(t, to, szs, (opt & REVO));
	}
	//printf("out :\n");
	//print_stack(ft_getaorb(t, A));
	//print_stack(ft_getaorb(t, B));
}

//TODO
// make a 'interface' fun for ft_merge_sort
// deal with num of lines for ft_merge_sort
// best solution is probably to have ft_set_opts(a_opt, b_opt) type thing
