# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabayle <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 18:51:58 by mabayle           #+#    #+#              #
#    Updated: 2019/08/13 18:54:23 by mabayle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	21sh

CC			:=	gcc
LINKER		:=	gcc -o

DEBUG		:=	0

LIBFT		:=	libft/libft.a

INCLUDES	:=	./includes

#libft
INCLUDES	:=	$(INCLUDES) -I$(dir $(LIBFT))includes
LDFLAGS		:=	-L$(dir $(LIBFT)) -lft

CFLAGS		:=	-Wall -Wextra -Werror -I$(INCLUDES)

ifeq ($(DEBUG), 1)
	CFLAGS	:=	$(CFLAGS) -fsanitize=address -ggdb -fno-omit-frame-pointer
endif

SRC_PATH	:=	./src/
OBJ_PATH	:=	./obj/

SRC		:=	
OBJ		:=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))
SRC		:=	$(addprefix $(SRC_PATH), $(SRC))

$(NAME):  $(LIBFT) $(OBJ)
	@$(LINKER) $(NAME) $(LDFLAGS) $(OBJ)
	@echo ""
	@echo "\033[0;32m BUILD DONE \033[0m"
	@echo ""

all: $(NAME)

$(LIBFT):	$(dir $(LIBFT))Makefile
	@make -C $(dir $(LIBFT))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling 21sh :\033[0m" $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Deleted all .o\033[0m"

fclean:
	@make -C libft/ fclean
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Deleted 21sh\033[0m"

re: fclean all

.PHONY:	all clean fclean re
