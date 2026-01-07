/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silent_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:58:42 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:17:52 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// sa : échange les 2 premiers éléments de a
void	silent_sa(t_list **a)
{
	void	*temp;

	if (!a || !*a || !(*a)->next)
		return ;
	temp = (*a)->content;
	(*a)->content = (*a)->next->content;
	(*a)->next->content = temp;
}

// sb : échange les 2 premiers éléments de b
void	silent_sb(t_list **b)
{
	void	*temp;

	if (!b || !*b || !(*b)->next)
		return ;
	temp = (*b)->content;
	(*b)->content = (*b)->next->content;
	(*b)->next->content = temp;
}

// ss : sa et sb en même temps
void	silent_ss(t_list **a, t_list **b)
{
	void	*temp;

	if (a && *a && (*a)->next)
	{
		temp = (*a)->content;
		(*a)->content = (*a)->next->content;
		(*a)->next->content = temp;
	}
	if (b && *b && (*b)->next)
	{
		temp = (*b)->content;
		(*b)->content = (*b)->next->content;
		(*b)->next->content = temp;
	}
}
