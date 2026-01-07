/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse_rotate_both.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:51:36 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:19:43 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_rra(t_list **a)
{
	t_list	*last;
	t_list	*prev;

	prev = NULL;
	last = *a;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *a;
	*a = last;
}

static void	do_rrb(t_list **b)
{
	t_list	*last;
	t_list	*prev;

	prev = NULL;
	last = *b;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *b;
	*b = last;
}

// rrr : rra et rrb en même temps
void	rrr(t_list **a, t_list **b)
{
	if (a && *a && (*a)->next)
		do_rra(a);
	if (b && *b && (*b)->next)
		do_rrb(b);
	ft_printf("rrr\n");
}
