# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 20:16:32 by azinchen          #+#    #+#              #
#    Updated: 2024/11/07 20:53:26 by azinchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME 			=	pipex

# Directories
LIBFT_DIR		= 	./libft
SRC_DIR 		=	./src
OBJ_DIR 		=	./obj

#Includes
LIBFT_INC		=	$(LIBFT_DIR)/include
INCLUDE 		=	./include/
HEADERS			=	-I$(LIBFT_INC)/libft.h -I$(LIBFT_INC)/get_next_line.h -I$(MLX_INC)

#Libraries
LIBFT			=	$(LIBFT_DIR)/libft.a
LIB				=	-L$(LIBFT_DIR)

# Compiler and compilation flags
CC 				=	cc
CFLAGS 			=	-g -Wall -Wextra -Werror
RM				=	rm -f

# Source files
READING_DIR			=	$(SRC_DIR)/reading/read_map.c
TRANSFORMING_DIR	= 	$(SRC_DIR)/transforming/rotate.c
DRAWING_DIR			=	$(SRC_DIR)/drawing/px_matrix.c
SRC					=	$(READING_DIR) \
						$(TRANSFORMING_DIR) \
						$(DRAWING_DIR) \
						$(SRC_DIR)/main.c

# Object files
OBJ 			=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

#Build rules
all: 			$(NAME)

$(LIBFT):
				@make -C ./libft

$(NAME): 		$(OBJ) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(HEADERS) $(LIB) -o $(NAME) 

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INCLUDE_DIR) -Imlx -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)
				@$(RM) .cache_exists
				@make clean -C ./libft
		
fclean: 		clean 
				@$(RM) $(NAME)
				@$(RM) $(LIBFT)
			
re: 			fclean all

.PHONY: 		all clean fclean re

BLUE = \033[1;34m
GREEN = \033[1;32m
NC = \033[0m
