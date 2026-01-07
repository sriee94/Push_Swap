/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:52:45 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:19:54 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_number(char *str)
{
	int		i;
	long	num;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	num = ft_atol(str);
	return (num <= INT_MAX && num >= INT_MIN);
}

int	has_duplicates(t_list *a)
{
	t_list	*i;
	t_list	*j;

	i = a;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (*(int *)i->content == *(int *)j->content)
				return (1);
			j = j->next;
		}
		i = i->next;
	}
	return (0);
}

static int	add_num(char *str, t_list **a)
{
	int		*num;
	t_list	*new;

	if (!is_valid_number(str))
		return (0);
	num = malloc(sizeof(int));
	if (!num)
		return (0);
	*num = (int)ft_atol(str);
	new = ft_lstnew(num);
	if (!new)
		return (free(num), 0);
	ft_lstadd_back(a, new);
	return (1);
}

static int	parse_single_arg(char *arg, t_list **a)
{
	char	**split;
	int		i;

	if (!is_valid_string(arg))
		return (0);
	split = ft_split(arg, ' ');
	if (!split || !split[0])
		return (ft_free_split(split), 0);
	i = -1;
	while (split[++i])
	{
		if (!add_num(split[i], a))
			return (ft_free_split(split), 0);
	}
	ft_free_split(split);
	return (!has_duplicates(*a));
}

int	parse_args(int argc, char **argv, t_list **a)
{
	int	i;

	if (argc == 2)
		return (parse_single_arg(argv[1], a));
	i = 1;
	while (i < argc && add_num(argv[i], a))
		i++;
	if (i != argc && argc > 2)
		return (0);
	return (!has_duplicates(*a));
}
