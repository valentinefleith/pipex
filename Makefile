# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 15:31:12 by vafleith          #+#    #+#              #
#    Updated: 2024/06/14 00:11:44 by vafleith         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra
CFLAGS += -Werror

LIBFT_PATH = libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)/$(LIBFT_NAME)

INC = -Iinclude -Ilibft

SRC_DIR = src

SRCS = pipe_error_messages.c free.c main.c open_files.c paths_handling.c \
	   exit_status.c bash_error_messages.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR = build
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

.PHONY: all
all: $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	@echo "Making Libft"
	@make -C $(LIBFT_PATH) > /dev/null

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC)
	@echo "pipex ready."

.PHONY: clean
clean:
	@echo Cleaning up object files	
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH) > /dev/null

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_PATH) > /dev/null
	@rm -rf $(NAME)

.PHONY: re
re: fclean all
