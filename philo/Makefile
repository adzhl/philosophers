NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

MAIN = main.c
SRCS = \
$(addprefix src/, \
	check_args.c \
	init.c \
	monitor.c \
	routine.c \
	threads.c \
	utils1.c \
	utils2.c) 

OBJ_DIR = obj
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MAIN) -o $(NAME) 

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

clean :
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re