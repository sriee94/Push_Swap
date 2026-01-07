/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:53:49 by sariee            #+#    #+#             */
/*   Updated: 2026/01/08 00:20:23 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../Libsriee/Include/libsriee.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <string.h>

/* ==================== OPERATIONS DE BASE ==================== */
void	sa(t_list **a);
void	sb(t_list **b);
void	ss(t_list **a, t_list **b);
void	pa(t_list **a, t_list **b);
void	pb(t_list **a, t_list **b);
void	ra(t_list **a);
void	rb(t_list **b);
void	rr(t_list **a, t_list **b);
void	rra(t_list **a);
void	rrb(t_list **b);
void	rrr(t_list **a, t_list **b);

/* ==================== PARSING ET VALIDATION ==================== */
int		parse_args(int argc, char **argv, t_list **a);
int		is_valid_number(char *str);
long	ft_atol(const char *str);
int		has_duplicates(t_list *a);

/* ==================== UTILITAIRES ==================== */
int		is_sorted(t_list *a);
int		get_min(t_list *stack);
int		get_max(t_list *stack);
int		find_position(t_list *stack, int value);
void	free_stack(t_list **stack);
int		is_valid_string(char *str);

/* ==================== ALGORITHMES DE TRI ==================== */
void	sort_three(t_list **a);
void	sort_small(t_list **a, t_list **b);
void	sort_large(t_list **a, t_list **b);
void	sort_medium(t_list **a, t_list **b);

/* ==================== ALGORITHME AVANCE - Helpers ==================== */
int		*create_sorted_array(t_list *a, int size);
int		get_index(int *sorted, int size, int value);
int		get_chunk_size(int size);

/* ==================== ALGORITHME AVANCE - Chunks ==================== */
void	push_chunks_to_b(t_list **a, t_list **b, int *sorted, int size);

/* ==================== ALGORITHME AVANCE - Push back ==================== */
int		find_target_pos(t_list *a, int value);
int		calc_cost_b(int pos, int size);
int		calc_cost_a(int target_pos, int size_a);
void	find_cheapest_move(t_list *b, t_list *a, int *cost_a, int *cost_b);
void	execute_move(t_list **a, t_list **b, int cost_a, int cost_b);
void	push_all_back_to_a(t_list **a, t_list **b);
void	push_back_optimized(t_list **a, t_list **b, int *sorted, int size);

/* ==================== ALGORITHME AVANCE - Final ==================== */
void	final_rotation(t_list **a);

/* ==================== CHECKER - FONCTIONS ==================== */
int		execute_operation(char *line, t_list **a, t_list **b);

/* ================== CHECKER - OPERATIONS SILENCIEUSES ================== */
void	silent_sa(t_list **a);
void	silent_sb(t_list **b);
void	silent_ss(t_list **a, t_list **b);
void	silent_pa(t_list **a, t_list **b);
void	silent_pb(t_list **a, t_list **b);
void	silent_ra(t_list **a);
void	silent_rb(t_list **b);
void	silent_rr(t_list **a, t_list **b);
void	silent_rra(t_list **a);
void	silent_rrb(t_list **b);
void	silent_rrr(t_list **a, t_list **b);

#endif
