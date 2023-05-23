CC = gcc
CFLAGS = -Wall -Werror -Wextra
CLIENT = @$(CC) $(CFLAGS) client.c ft_printf.c -o $(NAME_CL)
SERVER = @$(CC) $(CFLAGS) server.c ft_printf.c -o $(NAME_SV)
CLIENTBONUS = @$(CC) $(CFLAGS) client_bonus.c ft_printf.c -o $(NAME_CL_BONUS)
SERVERBONUS = @$(CC) $(CFLAGS) server_bonus.c ft_printf.c -o $(NAME_SV_BONUS)
NAME_CL = client
NAME_SV = server
NAME_CL_BONUS = client_bonus
NAME_SV_BONUS = server_bonus


all: $(NAME_CL) $(NAME_SV)
$(NAME_CL):
	$(CLIENT)
	@echo "\n\033[92m $@ built 💼\033[0m\n"
$(NAME_SV):
	$(SERVER)
	@echo "\n\033[92m $@ built 🖥️\033[0m\n"
bonus: $(NAME_CL_BONUS) $(NAME_SV_BONUS)
$(NAME_CL_BONUS):
	$(CLIENTBONUS)
	@echo "\n\033[92m $@ built 💼\033[0m\n"
$(NAME_SV_BONUS):
	$(SERVERBONUS)
	@echo "\n\033[92m $@ built 🖥️\033[0m\n"
clean:
	@rm -rf client server client_bonus server_bonus
	@echo "\n\033[36m object files removed 👋\033[0m\n"
norm:
	norminette *.c *.h
run:
	@make
	./server
fclean: clean
	@echo "\n\033[36m executables removed 👋\033[0m\n"
re: clean all
.PHONY: all bonus clean fclean re
