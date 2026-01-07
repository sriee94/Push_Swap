# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 11:27:27 by sariee            #+#    #+#              #
#    Updated: 2026/01/08 00:18:23 by sariee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

# Main
SRC_MAIN		=	Main/main.c

# Parsing
SRC_PARSING		=	Parsing/parsing.c

# Operations - Push
SRC_OP_PUSH		=	Operations/Push/operations_push.c

# Operations - Swap
SRC_OP_SWAP		=	Operations/Swap/operations_swap.c

# Operations - Rotate
SRC_OP_ROTATE	=	Operations/Rotate/operations_rotate.c

# Operations - Reverse
SRC_OP_REVERSE	=	Operations/Reverse/operations_reverse_rotate.c \
					Operations/Reverse/operations_reverse_rotate_both.c

# Algorithms - Basic
SRC_ALG_BASIC	=	Algorithms/Basic/algorithm.c

# Algorithms - Advanced
SRC_ALG_ADV		=	Algorithms/Advanced/algorithm_advanced.c

# Algorithms - Chunks
SRC_ALG_CHUNKS	=	Algorithms/Chunks/algorithm_chunks.c

# Algorithms - Cost
SRC_ALG_COST	=	Algorithms/Cost/algorithm_cost.c

# Algorithms - Execute
SRC_ALG_EXEC	=	Algorithms/Execute/algorithm_execute.c

# Algorithms - Push Back
SRC_ALG_PUSH	=	Algorithms/PushBack/algorithm_push_back.c

# Algorithms - Rotate
SRC_ALG_ROTATE	=	Algorithms/Rotate/algorithm_smart_rotate.c

# Algorithms - Priority
SRC_ALG_PRIO	=	Algorithms/Priority/algorithm_priority.c

# Utils
SRC_UTILS		=	Utils/utils.c Utils/utils2.c

# All sources (push_swap)
SRC				=	$(SRC_MAIN) $(SRC_PARSING) $(SRC_OP_PUSH) $(SRC_OP_SWAP) \
					$(SRC_OP_ROTATE) $(SRC_OP_REVERSE) $(SRC_ALG_BASIC) \
					$(SRC_ALG_ADV) $(SRC_ALG_CHUNKS) $(SRC_ALG_COST) \
					$(SRC_ALG_EXEC) $(SRC_ALG_PUSH) $(SRC_ALG_ROTATE) \
					$(SRC_ALG_PRIO) $(SRC_UTILS)

# **************************************************************************** #
#                                BONUS CHECKER                                 #
# **************************************************************************** #

# Checker main
CHECKER_MAIN	=	Main/checker.c

# Operation - Check/Valid
EXECUTE_OP_VAL	=	Execute-Operations/execute_operations.c

# Ope - Silent - Push
CHECKER_OP_PUSH	=	Operations-Silent/Push/silent_push.c

# Ope - Silent - Swap
CHECKER_OP_SWAP	=	Operations-Silent/Swap/silent_swap.c

# Ope - Silent - Rotate
CHECKER_OP_ROTA	=	Operations-Silent/Rotate/silent_rotate.c

# Ope - Silent - Reverse
CHECKER_OP_REV	=	Operations-Silent/Reverse/silent_reverse_rotate.c \
					Operations-Silent/Reverse/silent_reverse_rotate_both.c

# Checker parsing (partage avec push_swap)
CHECKER_PARSING	=	Parsing/parsing.c

# Checker utils (partage avec push_swap)
CHECKER_UTILS	=	Utils/utils.c Utils/utils2.c

# All sources checker
SRC_CHECKER		=	$(CHECKER_MAIN) $(EXECUTE_OP_VAL) $(CHECKER_OP_PUSH) \
					$(CHECKER_OP_SWAP) $(CHECKER_OP_ROTA) $(CHECKER_OP_REV) \
					$(CHECKER_PARSING) $(CHECKER_UTILS)

# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME			= push_swap
CHECKER_NAME	= checker
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f
MKDIR			= mkdir -p

# Directories
LIBSRIEE_DIR	= Libsriee
SRC_DIR			= Src
CHECKER_DIR		= Src-Checker
OBJ_DIR			= Objs
OBJ_CHECKER_DIR	= Objs-Checker
INCL_DIR		= Include

# Libraries
LIBSRIEE		= $(LIBSRIEE_DIR)/libsriee.a

# Includes
Includes		= -I$(LIBSRIEE_DIR)/Include -I$(INCL_DIR)

# Objects
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJS_CHECKER	= $(addprefix $(OBJ_CHECKER_DIR)/, $(SRC_CHECKER:.c=.o))

# Colors
BOLD_CYAN		= \033[1;36m
CYAN			= \033[0;36m
YELLOW			= \033[0;33m
RED				= \033[0;31m
GREEN			= \033[0;32m
RESET			= \033[0m

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBSRIEE) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBSRIEE) -o $(NAME)
	@echo "  $(BOLD_CYAN)✓$(RESET) $(BOLD_CYAN)Push_swap is ready to use.$(RESET)"

checker: $(LIBSRIEE) $(OBJS_CHECKER)
	@$(CC) $(CFLAGS) $(OBJS_CHECKER) $(LIBSRIEE) -o $(CHECKER_NAME)
	@echo "  $(BOLD_CYAN)✓$(RESET) $(BOLD_CYAN)Checker is ready to use.$(RESET)"

$(LIBSRIEE):
	@echo "$(CYAN)• Building libsriee...$(RESET)"
	@make -C $(LIBSRIEE_DIR)

# Compile sources from Src/ subdirectories (push_swap)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(Includes) -c $< -o $@

# Compile bonus from Src-Checker/ subdirectories
$(OBJ_CHECKER_DIR)/%.o: $(CHECKER_DIR)/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(Includes) -c $< -o $@

# Compile Parsing for bonus
$(OBJ_CHECKER_DIR)/Parsing/%.o: $(SRC_DIR)/Parsing/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(Includes) -c $< -o $@

# Compile Utils for bonus
$(OBJ_CHECKER_DIR)/Utils/%.o: $(SRC_DIR)/Utils/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(Includes) -c $< -o $@

clean:
	@make clean -C $(LIBSRIEE_DIR)
	@$(RM) -r $(OBJ_DIR) $(OBJ_CHECKER_DIR)
	@echo "$(YELLOW)• Cleaned object files.$(RESET)"

fclean: clean
	@make fclean -C $(LIBSRIEE_DIR)
	@$(RM) $(NAME) $(CHECKER_NAME)
	@echo "$(RED)• Full cleanup complete.$(RESET)"

re: fclean all

.PHONY: all checker clean fclean re
