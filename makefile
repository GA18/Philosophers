NAME = philo

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror

INCLUDES = -Iincludes

SRCS = main.c \
	   parser.c \
	   routine.c \
	   time.c \
	   cleanup.c \

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all