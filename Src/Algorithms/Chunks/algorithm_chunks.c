/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_chunks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:07:14 by samuelriee        #+#    #+#             */
/*   Updated: 2026/01/08 00:19:15 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_chunks_to_b(t_list **a, t_list **b, int *sorted, int size)
{
	int	chunk_size;
	int	range;
	int	current_index;

	chunk_size = get_chunk_size(size);
	range = chunk_size;
	while (*a)
	{
		current_index = get_index(sorted, size, *(int *)(*a)->content);
		if (current_index < range)
		{
			pb(a, b);
			if (range < size)
				range += chunk_size;
		}
		else
			ra(a);
	}
}
