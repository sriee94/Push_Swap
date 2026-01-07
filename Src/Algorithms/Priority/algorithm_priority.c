/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_priority.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:54:38 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:19:24 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_top_element(t_list *b, int *sorted, int size)
{
	int	current_index;
	int	threshold;

	if (!b)
		return (0);
	current_index = get_index(sorted, size, *(int *)b->content);
	threshold = size - (size / 4);
	return (current_index >= threshold);
}

static void	push_big_first(t_list **a, t_list **b, int *sorted, int size)
{
	int	pos;
	int	b_size;

	while (*b)
	{
		if (is_top_element(*b, sorted, size))
		{
			pa(a, b);
			continue ;
		}
		pos = find_position(*b, get_max(*b));
		b_size = ft_lstsize(*b);
		if (pos <= b_size / 2)
		{
			while (*(int *)(*b)->content != get_max(*b))
				rb(b);
		}
		else
		{
			while (*(int *)(*b)->content != get_max(*b))
				rrb(b);
		}
		pa(a, b);
	}
}

void	push_back_optimized(t_list **a, t_list **b, int *sorted, int size)
{
	push_big_first(a, b, sorted, size);
}
