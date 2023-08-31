NAME = minishell

CFLAGS = $(INCLUDE) -Wall -Werror -Wextra
INCLUDE = -IInclude/
ifeq ($(shell uname), Darwin)
INCLUDE = -IInclude/ -I/Users/segungor/goinfre/homebrew/Cellar/readline/8.2.1/include
endif
CC = gcc -g

SRC = $(shell find src -name "*.c")
SRCDIR = $(sort $(dir $(SRC)))
SRCFLS = $(notdir $(SRC))

OUTPREFIX = builds/
OBJ = $(addprefix $(OUTPREFIX), $(SRCFLS:.c=.o))

vpath %.c $(SRCDIR)
$(OUTPREFIX)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: outfolder $(NAME)
	@echo "Done"

$(NAME): $(OBJ)
ifeq ($(shell uname), Darwin)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -L /Users/segungor/goinfre/homebrew/Cellar/readline/8.2.1/lib -o $(NAME)
endif
ifeq ($(shell uname), Linux)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
endif

outfolder:
	@echo "Building Minishell"
	@if [ ! -d $(OUTPREFIX) ]; then echo "$(OUTPREFIX) folder created."; fi
	@mkdir -p $(OUTPREFIX);
	@echo "Compiling Files..."

clean:
	@echo "Cleaning Objects..."
	@if [ -d $(OUTPREFIX) ]; then rm -rf $(OUTPREFIX); fi

fclean: clean
	@echo "Cleaning Program..."
	@if [ ! -d $(NAME) ]; then rm -rf $(NAME); fi
	@echo "Done"

re: fclean seperate all

seperate:
	@echo "-----------------"

.PHONY:
	all clean fclean re seperate

check:
	@echo "SRC : "
	@echo $(SRC)
	@echo "\nSRCDIR : "
	@echo $(SRCDIR)
	@echo "\nSRCFLS : "
	@echo $(SRCFLS)
	@echo "\nOBJ : "
	@echo $(OBJ)