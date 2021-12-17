/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_emul1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:27:31 by najacque          #+#    #+#             */
/*   Updated: 2021/12/17 14:28:32 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
