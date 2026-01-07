/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_advanced.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:53:49 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:19:10 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_index(int *sorted, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (sorted[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

static void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = -1;
	while (++i < size - 1)
	{
		j = i;
		while (++j < size)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int	*create_sorted_array(t_list *a, int size)
{
	int		*arr;
	int		i;
	t_list	*current;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	current = a;
	i = 0;
	while (current)
	{
		arr[i++] = *(int *)current->content;
		current = current->next;
	}
	sort_array(arr, size);
	return (arr);
}

int	get_chunk_size(int size)
{
	if (size <= 100)
		return (size / 5);
	if (size <= 500)
		return (29);
	return (size / 11);
}
