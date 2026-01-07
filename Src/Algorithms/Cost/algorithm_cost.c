/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_cost.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:01:33 by samuelriee        #+#    #+#             */
/*   Updated: 2026/01/08 00:19:19 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calc_cost_b(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (-(size - pos));
}

int	calc_cost_a(int target_pos, int size_a)
{
	if (target_pos <= size_a / 2)
		return (target_pos);
	return (-(size_a - target_pos));
}

static int	abs_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	calc_combined_cost(int cost_a, int cost_b)
{
	if ((cost_a > 0 && cost_b > 0) || (cost_a < 0 && cost_b < 0))
	{
		if (abs_value(cost_a) > abs_value(cost_b))
			return (abs_value(cost_a));
		return (abs_value(cost_b));
	}
	return (abs_value(cost_a) + abs_value(cost_b));
}

void	find_cheapest_move(t_list *b, t_list *a, int *cost_a, int *cost_b)
{
	int		pos;
	int		min_cost;
	int		tmp_cost_a;
	int		tmp_cost_b;
	t_list	*current;

	pos = 0;
	min_cost = INT_MAX;
	current = b;
	while (current)
	{
		tmp_cost_b = calc_cost_b(pos, ft_lstsize(b));
		tmp_cost_a = calc_cost_a(find_target_pos(a, *(int *)current->content),
				ft_lstsize(a));
		if (calc_combined_cost(tmp_cost_a, tmp_cost_b) < min_cost)
		{
			min_cost = calc_combined_cost(tmp_cost_a, tmp_cost_b);
			*cost_a = tmp_cost_a;
			*cost_b = tmp_cost_b;
		}
		pos++;
		current = current->next;
	}
}
