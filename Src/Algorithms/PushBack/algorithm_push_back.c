/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_push_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:03:21 by samuelriee        #+#    #+#             */
/*   Updated: 2026/01/08 00:19:29 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_target_pos(t_list *a, int value)
{
	int		pos;
	int		target_pos;
	int		target_value;
	t_list	*current;

	pos = 0;
	target_pos = 0;
	target_value = INT_MAX;
	current = a;
	while (current)
	{
		if (*(int *)current->content > value
			&& *(int *)current->content < target_value)
		{
			target_value = *(int *)current->content;
			target_pos = pos;
		}
		pos++;
		current = current->next;
	}
	if (target_value == INT_MAX)
		return (find_position(a, get_min(a)));
	return (target_pos);
}
