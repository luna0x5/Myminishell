# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 16:15:28 by hmoukit           #+#    #+#              #
#    Updated: 2024/11/13 11:52:04 by hmoukit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- MakeFile -*-

NAME = minishell
CC = cc
FLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
CFLAGS += -I/Users/hmoukit/.brew/opt/readline/include
LDFLAGS += -L/Users/hmoukit/.brew/opt/readline/lib -lreadline -lncurses
T_SOURCES = ./tokenizer/tokenizer.c \
            ./tokenizer/tokenizer_handler.c \
            ./tokenizer/tokenizer_utils.c \
			./tokenizer/t_token_utils.c \
			./tokenizer/process_tokens.c \
			./tokenizer/syntax_errors.c

P_SOURCES = ./parser/parser.c \
            ./parser/parser_utils.c \
			./parser/parser_handler.c

EXP_SOURCES = ./expander/expander_handler.c \
			  ./expander/expander_utils.c \
			  ./expander/expander.c \
			  ./expander/heredoc_ex.c \
			  ./expander/handle_quoted_str.c \
			  ./expander/ft_getenv.c

EXEC_SOURCES = ./execution/find_path.c \
			   ./execution/execution_utils.c \
			   ./execution/make_env.c \
			   ./execution/pipelines.c \
			   ./execution/redirections_handler.c \
			   ./execution/heredoc_handler.c \
			   ./execution/redirections_utils.c \
			   ./execution/redirections.c \
			   ./execution/simple_cmd.c \
			   ./execution/minishell.c \
			   ./execution/executer.c \
			   ./execution/open_out_files.c \
			   ./execution/signals.c \
			   ./execution/pipelines_utils.c \
			   ./execution/simple_cmd_utils.c \
			   ./execution/cleanup.c

T_OBJECTS = $(T_SOURCES:.c=.o)
P_OBJECTS = $(P_SOURCES:.c=.o)
EXP_OBJECTS = $(EXP_SOURCES:.c=.o)
EXEC_OBJECTS = $(EXEC_SOURCES:.c=.o)

INCLUDES = ./includes/tokenizer.h \
		   ./includes/parser.h \
	       ./includes/expander.h \
		   ./includes/minishell.h 

%.o: %.c
	$(CC) $(FLAGS) $(CFLAGS) -I./includes -c -o $@ $<

all: libft $(NAME)

$(NAME): $(T_OBJECTS) $(P_OBJECTS) $(EXP_OBJECTS) $(EXEC_OBJECTS) $(INCLUDES)
	$(CC) $(FLAGS) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(T_OBJECTS) $(P_OBJECTS) $(EXP_OBJECTS) $(EXEC_OBJECTS) ./libft/libft.a
libft:
	make -C ./libft

clean:
	$(RM) $(T_OBJECTS) $(P_OBJECTS) $(EXP_OBJECTS) $(EXEC_OBJECTS)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: libft clean fclean re
