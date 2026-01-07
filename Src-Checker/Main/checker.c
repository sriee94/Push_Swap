/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:32:33 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:18:01 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_list	*a;
	t_list	*b;
	char	*line;

	if (ac < 2)
		return (0);
	a = NULL;
	b = NULL;
	if (!parse_args(ac, av, &a))
		return (free_stack(&a), ft_putendl_fd("Error", 2), 1);
	line = get_next_line(0);
	while (line)
	{
		if (!execute_operation(line, &a, &b))
			return (free(line), free_stack(&a),
				free_stack(&b), ft_putendl_fd("Error", 2), 1);
		free(line);
		line = get_next_line(0);
	}
	if (is_sorted(a) && b == NULL)
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
	return (free_stack(&a), free_stack(&b), 0);
}
