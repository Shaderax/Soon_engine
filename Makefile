# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrouzeva <nrouzeva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 09:31:46 by nrouzeva          #+#    #+#              #
#    Updated: 2019/03/15 17:36:38 by nrouzeva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Soon

SRC_PATH = ./src
OBJ_PATH = ./obj
LIB_PATH = ./lib/
INC_PATH = ./inc $(LIB_PATH)glfw/include/ ./$(LIB_PATH)/libmathpp ./$(LIB_PATH)/ECS

SRC_NAME = main.cpp \
		   Init.cpp \
		   Error.cpp \
		   Window.cpp \
		   Mouse.cpp

OBJ_NAME = $(SRC_NAME:.cpp=.o)
LIB_NAME = glfw/src libmathpp ECS/build

CC = g++
CFLAGS = -std=c++11 #-Wextra -Wall -g -Werror -g3 -O2 #-fsanitize=address -fsanitize=undefined
LIB_FLAGS = -lECS -lglfw3 -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo


RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	cmake -B $(LIB_PATH)glfw $(LIB_PATH)glfw
	cmake $(LIB_PATH)ECS -B $(LIB_PATH)ECS/build
	make -C $(LIB_PATH)glfw
	make -C $(LIB_PATH)ECS/build
	@echo "$(GREEN)[✓]$(NC) Library built"
	$(CC) $(CFLAGS) $(LIB) $(INC) $(OBJ) $(LIB_FLAGS) -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp Makefile inc/scop.h
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "$(GREEN)[✓]$(NC) Source compiled : $<"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(RED)[-]$(NC) Objects cleaned"
	@make -C $(LIB_PATH)glfw clean
	@echo "$(RED)[-]$(NC) Library cleaned"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[-]$(NC) Program clear"

re:fclean
	@make
