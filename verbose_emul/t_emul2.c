/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_emul2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:27:40 by najacque          #+#    #+#             */
/*   Updated: 2021/12/17 14:27:40 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_emul.h"

void	ft_ra(t_emul *t)
{
	ft_putstr_endl("ra");
	ft_rotate(t->a);
}

void	ft_rb(t_emul *t)
{
	ft_putstr_endl("rb");
	ft_rotate(t->b);
}

void	ft_rr(t_emul *t)
{
	ft_putstr_endl("rr");
	ft_rotate(t->a);
	ft_rotate(t->b);
}

void	ft_rra(t_emul *t)
{
	ft_putstr_endl("rra");
	ft_rrotate(t->a);
}

void	ft_rrb(t_emul *t)
{
	ft_putstr_endl("rrb");
	ft_rrotate(t->b);
}
