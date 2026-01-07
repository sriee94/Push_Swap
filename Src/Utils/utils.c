/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:54:33 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:20:01 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Libère toute la mémoire d'une stack
void	free_stack(t_list **stack)
{
	t_list	*current;
	t_list	*next;

	current = *stack;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*stack = NULL;
}

// Vérifie si la stack est triée en ordre croissant
int	is_sorted(t_list *a)
{
	int	prev;
	int	curr;

	if (!a)
		return (1);
	prev = *(int *)a->content;
	a = a->next;
	while (a)
	{
		curr = *(int *)a->content;
		if (prev > curr)
			return (0);
		prev = curr;
		a = a->next;
	}
	return (1);
}

// Trouve la valeur minimum dans la stack
int	get_min(t_list *stack)
{
	int	min;

	if (!stack)
		return (0);
	min = *(int *)stack->content;
	stack = stack->next;
	while (stack)
	{
		if (*(int *)stack->content < min)
			min = *(int *)stack->content;
		stack = stack->next;
	}
	return (min);
}

// Trouve la valeur maximum dans la stack
int	get_max(t_list *stack)
{
	int	max;

	if (!stack)
		return (0);
	max = *(int *)stack->content;
	stack = stack->next;
	while (stack)
	{
		if (*(int *)stack->content > max)
			max = *(int *)stack->content;
		stack = stack->next;
	}
	return (max);
}

// Trouve la position d'une valeur dans la stack
int	find_position(t_list *stack, int value)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (*(int *)stack->content == value)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}
