NAME = philo

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3

FILES = main \
		parsing \
		init \
		philo_routine \
		utils \
		mini_liblp \
		mini_liblp1 \
		check_death_while \

SRCS_DIR = src

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))

OBJS_DIR = .build

OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))

INCLUDES_DIR = includes

INCLUDES_FILES = philo

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(addsuffix .h, $(INCLUDES_FILES)))

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(OBJS) $(LIBLP) -o $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all

bonus: all

.PHONY: all clean fclean re