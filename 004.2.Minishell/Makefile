NAME = minishell

CFLAGS = $(INCLUDE) -Wall -Werror -Wextra
INCLUDE = -IInclude/
ifeq ($(shell uname), Darwin)
INCLUDE = -IInclude/ -I/Users/segungor/goinfre/homebrew/Cellar/readline/8.2.1/include
endif
CC = gcc -g
SRC	:=  src/builtin/runBuiltin.c \
		src/builtin/runCd.c \
		src/builtin/runEcho.c \
		src/builtin/runEnv.c \
		src/builtin/runExit.c \
		src/builtin/runExport.c \
		src/builtin/runPwd.c \
		src/builtin/runUnset.c \
		src/executer/dup.c \
		src/executer/execCmd.c \
		src/executer/executer.c \
		src/executer/pipeFunction.c \
		src/executer/runProcess.c \
		src/expander/clearEmptyContent.c \
		src/expander/expandDollar.c \
		src/expander/expander.c \
		src/expander/expanderCmd.c \
		src/lexer/addLexNode.c \
		src/lexer/classify.c \
		src/lexer/freeLexer.c \
		src/lexer/getMissinArg.c \
		src/lexer/lexer.c \
		src/lexer/printLexer.c \
		src/lexer/syntaxCheck.c \
		src/main/free.c \
		src/main/init.c \
		src/main/initDestroy.c \
		src/main/minishell.c \
		src/main/signal.c \
		src/main/updateLoop.c \
		src/PARSER/create_cmdtable.c \
		src/PARSER/create_files.c \
		src/PARSER/CreateFileList.c \
		src/PARSER/fill_cmd_table.c \
		src/PARSER/heradoc.c \
		src/PARSER/parser.c \
		src/PARSER/printParser.c \
		src/utils/env/createNewEnv.c \
		src/utils/env/exportEnvControl.c \
		src/utils/env/getEnvName.c \
		src/utils/env/updateEnv.c \
		src/utils/error/printError.c \
		src/utils/free/freeUtils.c \
		src/utils/metacharacter/CompareMeta.c \
		src/utils/str/ft_atoi.c \
		src/utils/str/ft_itoa.c \
		src/utils/str/ft_strdup.c \
		src/utils/str/ft_strlcpy.c \
		src/utils/str/ft_strlen.c \
		src/utils/str/getArrayLen.c \
		src/utils/str/OwnStrJoin.c \
		src/utils/str/StrAddChar.c \
		src/utils/str/StrCompare.c \
		src/utils/str/trimSpace.c \
		src/utils/str/utils.c \
		src/utils/title/title.c
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