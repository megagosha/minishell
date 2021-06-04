NAME = minishell

LIBFT = libft.a

FLAGS = gcc -O2 $(HEADERS)

LIBFHT_H = -I srcs/libft/
MINISHELL_H = -I includes/

GNL_BUFFER = -D BUFFER_SIZE=1000
HEADERS = $(MINISHELL_H)#$(LIBFHT_H) $(MINISHELL_H)

SRC_DIR = srcs/
OBJ_DIR = obj/
LIB_DIR = srcs/libft/
#Указать точные названия файлов.
CFILES = main.c\
		 pwd.c\
		 error.c \
		 init.c \
		 cd.c \
		 echo.c \
		 history.c \
		 term_helper.c \
		 terminal.c \
		 signal.c \
		 export.c \
		 env.c \
		 parser.c \
		 parser2.c \
		 parser3.c \
		 parser4.c \
		 parser5.c \
		 execute.c \
		 helper.c \
		 termcap.c \
		 termcap2.c \
		 exec_prep.c \
		 redirections.c \
		 pipe.c \
		 exec_tools.c

CFIND = $(CFILES:%=$(SRC_DIR)%)

OFILES = $(CFILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OFILES))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
				@echo Building libft
				@make -C $(LIB_DIR)
				@echo Copy $(LIB_DIR)$(LIBFT) to root
				@cp $(LIB_DIR)$(LIBFT) .

				$(FLAGS) $(HEADERS) -o $(NAME) $(addprefix $(OBJ_DIR), $(OFILES)) -L. -lft -ltermcap

$(OBJ): $(CFIND)
				@$(MAKE) $(OFILES)
$(OFILES):
			@echo Compiled: $(@:obj/%=%)
			@gcc $(HEADERS) $(GNL_BUFFER) -c -o $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)
clean:
				/bin/rm -rf $(OBJ_DIR)
				@make -C $(LIB_DIR) clean

fclean:			clean
				@make -C $(LIB_DIR) fclean
				/bin/rm -f $(LIBFT)
				/bin/rm -f $(NAME)

re: 			fclean all

.PHONY:			all clean flcean re
