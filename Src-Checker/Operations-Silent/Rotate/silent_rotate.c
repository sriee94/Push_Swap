/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silent_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:52:09 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:17:54 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// ra : décale tous les éléments vers le haut
void	silent_ra(t_list **a)
{
	t_list	*first;
	t_list	*last;

	if (!a || !*a || !(*a)->next)
		return ;
	first = *a;
	*a = first->next;
	first->next = NULL;
	last = ft_lstlast(*a);
	last->next = first;
}

// rb : décale tous les éléments vers le haut
void	silent_rb(t_list **b)
{
	t_list	*first;
	t_list	*last;

	if (!b || !*b || !(*b)->next)
		return ;
	first = *b;
	*b = first->next;
	first->next = NULL;
	last = ft_lstlast(*b);
	last->next = first;
}

// rr : ra et rb en même temps
void	silent_rr(t_list **a, t_list **b)
{
	t_list	*first;
	t_list	*last;

	if (a && *a && (*a)->next)
	{
		first = *a;
		*a = first->next;
		first->next = NULL;
		last = ft_lstlast(*a);
		last->next = first;
	}
	if (b && *b && (*b)->next)
	{
		first = *b;
		*b = first->next;
		first->next = NULL;
		last = ft_lstlast(*b);
		last->next = first;
	}
}
