/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:09:08 by samuelriee        #+#    #+#             */
/*   Updated: 2026/01/08 00:19:13 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_list **a)
{
	int	first;
	int	second;
	int	third;

	if (ft_lstsize(*a) != 3)
		return ;
	first = *(int *)(*a)->content;
	second = *(int *)(*a)->next->content;
	third = *(int *)(*a)->next->next->content;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

void	sort_small(t_list **a, t_list **b)
{
	int	min;
	int	pos;
	int	size;

	while (ft_lstsize(*a) > 3)
	{
		min = get_min(*a);
		pos = find_position(*a, min);
		size = ft_lstsize(*a);
		if (pos <= size / 2)
		{
			while (*(int *)(*a)->content != min)
				ra(a);
		}
		else
		{
			while (*(int *)(*a)->content != min)
				rra(a);
		}
		pb(a, b);
	}
	sort_three(a);
	while (*b)
		pa(a, b);
}

void	sort_large(t_list **a, t_list **b)
{
	int	*sorted;
	int	size;

	size = ft_lstsize(*a);
	sorted = create_sorted_array(*a, size);
	if (!sorted)
		return ;
	push_chunks_to_b(a, b, sorted, size);
	push_all_back_to_a(a, b);
	final_rotation(a);
	free(sorted);
}
