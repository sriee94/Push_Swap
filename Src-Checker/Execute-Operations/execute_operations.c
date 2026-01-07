/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 14:03:30 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:18:05 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	execute_swap(char *line, t_list **a, t_list **b)
{
	if (ft_strcmp(line, "sa\n") == 0)
		silent_sa(a);
	else if (ft_strcmp(line, "sb\n") == 0)
		silent_sb(b);
	else if (ft_strcmp(line, "ss\n") == 0)
		silent_ss(a, b);
	else
		return (0);
	return (1);
}

static int	execute_push(char *line, t_list **a, t_list **b)
{
	if (ft_strcmp(line, "pa\n") == 0)
		silent_pa(a, b);
	else if (ft_strcmp(line, "pb\n") == 0)
		silent_pb(a, b);
	else
		return (0);
	return (1);
}

static int	execute_rotate(char *line, t_list **a, t_list **b)
{
	if (ft_strcmp(line, "ra\n") == 0)
		silent_ra(a);
	else if (ft_strcmp(line, "rb\n") == 0)
		silent_rb(b);
	else if (ft_strcmp(line, "rr\n") == 0)
		silent_rr(a, b);
	else if (ft_strcmp(line, "rra\n") == 0)
		silent_rra(a);
	else if (ft_strcmp(line, "rrb\n") == 0)
		silent_rrb(b);
	else if (ft_strcmp(line, "rrr\n") == 0)
		silent_rrr(a, b);
	else
		return (0);
	return (1);
}

int	execute_operation(char *line, t_list **a, t_list **b)
{
	if (!line)
		return (0);
	if (execute_swap(line, a, b))
		return (1);
	if (execute_push(line, a, b))
		return (1);
	if (execute_rotate(line, a, b))
		return (1);
	return (0);
}
