/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:01:57 by samuelriee        #+#    #+#             */
/*   Updated: 2026/01/08 00:19:21 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_smart_rotations(t_list **a, t_list **b, int *ca, int *cb)
{
	while (*ca > 0 && *cb > 0)
	{
		rr(a, b);
		(*ca)--;
		(*cb)--;
	}
	while (*ca < 0 && *cb < 0)
	{
		rrr(a, b);
		(*ca)++;
		(*cb)++;
	}
}

static void	finish_b_rotation(t_list **b, int cost_b)
{
	while (cost_b > 0)
	{
		rb(b);
		cost_b--;
	}
	while (cost_b < 0)
	{
		rrb(b);
		cost_b++;
	}
}

static void	rotate_a_smart(t_list **a, int target_pos, int a_size)
{
	if (target_pos <= a_size / 2)
	{
		while (target_pos-- > 0)
			ra(a);
	}
	else
	{
		while (target_pos++ < a_size)
			rra(a);
	}
}

void	push_all_back_to_a(t_list **a, t_list **b)
{
	int	cost_a;
	int	cost_b;
	int	target_pos;

	while (*b)
	{
		cost_a = 0;
		cost_b = 0;
		find_cheapest_move(*b, *a, &cost_a, &cost_b);
		do_smart_rotations(a, b, &cost_a, &cost_b);
		finish_b_rotation(b, cost_b);
		target_pos = find_target_pos(*a, *(int *)(*b)->content);
		rotate_a_smart(a, target_pos, ft_lstsize(*a));
		pa(a, b);
	}
}

void	final_rotation(t_list **a)
{
	int	min_pos;
	int	size;

	min_pos = find_position(*a, get_min(*a));
	size = ft_lstsize(*a);
	if (min_pos <= size / 2)
	{
		while (min_pos-- > 0)
			ra(a);
	}
	else
	{
		while (size - min_pos > 0)
		{
			rra(a);
			size--;
		}
	}
}
