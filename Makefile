BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
RESET = \033[0m

NAME = philo
MAKE = make --noprint-directory

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = $(addprefix src/, main.c init.c threads.c philo_routine.c checker.c utils.c)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "🔨 $(BLUE)$(notdir $<) $(BLACK)=> $(CYAN)$(notdir $@)$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(@)
	@echo "🔗 $(CYAN)$(notdir $(LIBFT)) $(notdir $(OBJS)) $(BLACK)=> $(YELLOW)$(@)$(RESET)"

clean :
	@find . -type f -name "*.o" -printf "🧹 $(BLACK)%f$(RESET)\n" -delete

fclean : clean
	@find . -type f -name "$(NAME)" -printf "🧹 $(BLACK)%f$(RESET)\n" -delete

re : fclean all

run: $(NAME)
	@./$<

.PHONY: all clean fclean re run
