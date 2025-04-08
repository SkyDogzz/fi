NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= philo.c utils.c init.c ato.c philos_monitor.c threads_monitor.c \
		  parse.c status.c
OBJS	= $(SRCS:.c=.o)

ifdef DEBUG
CFLAGS += -g3
endif
ifdef FSAN
CFLAGS += -fsanitize=thread
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)
	@echo "Executable $(NAME) created"

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Object $@ created"

clean:
	rm -f $(OBJS)
	@echo "Object cleared"

fclean: clean
	rm -f $(NAME)
	@echo "Executable cleared"

re: fclean all

nm: re
	nm $(NAME) | grep GLIBC

.PHONY: all clean fclean re
