NAME                =   philo

CC                  =   gcc
CFLAGS              =   -Wall -Wextra -Werror -g3 -I $(INCLUDES)

INCLUDES            =   ./includes/

SRC_DIR             =   ./srcs
OBJ_DIR             =   $(SRC_DIR)/objs

SRCS                =   $(SRC_DIR)/main_program.c 		\
						$(SRC_DIR)/utils.c       		\
						$(SRC_DIR)/routines.c       	\
						$(SRC_DIR)/routine_utils.c		\
						$(SRC_DIR)/end_of_prog_utils.c	\
						$(SRC_DIR)/safe_checks.c		\

OBJS                =   $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

################################## COMMANDES ##################################


all: $(NAME)

$(NAME): $(OBJS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -pthread -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
