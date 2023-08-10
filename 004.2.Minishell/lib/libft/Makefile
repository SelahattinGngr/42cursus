# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: segungor<seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 17:37:59 by segungor          #+#    #+#              #
#    Updated: 2023/07/12 17:38:01 by segungor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I./inc
SRC_DIR	=	src
SRC_MDT	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_itoa.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strjoin.c \
			ft_strmapi.c \
			ft_strtrim.c \
			ft_substr.c
SRC_BNS	=	ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c
SRC_ADD	=	ft_free_split.c

OBJ_DIR	=	obj
OBJ_MDT	=	$(addprefix $(OBJ_DIR)/, $(SRC_MDT:.c=.o))
OBJ_BNS	=	$(addprefix $(OBJ_DIR)/, $(SRC_BNS:.c=.o))
OBJ_ADD	=	$(addprefix $(OBJ_DIR)/, $(SRC_ADD:.c=.o))
OBJ		=	$(OBJ_MDT) $(OBJ_BNS) $(OBJ_ADD)

# ********************* #
#      C O L O R S      #
# ********************* #

N		=	\033[m
R		=	\033[0;31m
G		=	\033[0;32m
Y		=	\033[0;33m
B		=	\033[0;34m
P		=	\033[0;35m
T		=	\033[0;36m

# N = no color, R = red, G = green, Y = yellow, B = blue, P = purple, T = turquoise

# ********************* #
#      S Y S T E M      #
# ********************* #

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

# ********************* #
#       R U L E S       #
# ********************* #

.PHONY: all $(NAME) bonus $(OBJ_DIR)/%.o header obj_dir clean fclean re debug release

all: header obj_dir $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@printf "$(B)%b $(Y)%b $(B)%b$(N)\n" "###############################" "$(NAME) ready" "###"

$(NAME): header obj_dir $(OBJ_MDT)
	@ar -rcs $(NAME) $(OBJ_MDT)
	@printf "$(B)%b $(Y)%b $(B)%b$(N)\n" "###############################" "$(NAME) ready" "###"

bonus: header obj_dir $(OBJ_MDT) $(OBJ_BNS)
	@ar -rcs $(NAME) $(OBJ_MDT) $(OBJ_BNS)
	@printf "$(B)%b $(Y)%b $(B)%b$(N)\n" "###############################" "$(NAME) ready" "###"

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(B)%b $(Y)%10b $(T)%-34b $(B)%b$(N)\n" "#" "compiling" "$@" "#"

header:
	@printf "$(B)%b $(Y)%b $(B)%b$(N)\n" "###################" "L I B F T" "###################"

obj_dir:
	@mkdir -p $(OBJ_DIR)

clean: header
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r *.dSYM
	@printf "$(B)%b $(Y)%10b $(T)%-34b $(B)%b$(N)\n" "#" "removing" "objects" "#"
	@printf "$(B)%b $(Y)%b $(B)%b$(N)\n" "##################################" "clean done" "###"

fclean: header clean
	@$(RM) $(NAME)
	@printf "$(B)%b $(Y)%10b $(T)%-34b $(B)%b$(N)\n" "#" "removing" "$(NAME)" "#"
	@printf "$(B)%b $(Y)%b $(B)%b$(N)\n" "#################################" "fclean done" "###"

re: fclean all

debug: CFLAGS += -O0 -DDEBUG -g
debug: all

release: fclean
release: CFLAGS	+= -O2 -DNDEBUG
release: all