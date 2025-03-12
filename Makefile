SERVER = server
CLIENT = client

PRINTF_DIR = ft_printf
SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -D_XOPEN_SOURCE=700

INCLUDES = -I$(PRINTF_DIR)

all: $(SERVER) $(CLIENT)

$(PRINTF_DIR)/ft_printf.a:
	make -C $(PRINTF_DIR)

$(SERVER): $(OBJS_SERVER) $(PRINTF_DIR)/ft_printf.a
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER) $(PRINTF_DIR)/ft_printf.a $(INCLUDES)

$(CLIENT): $(OBJS_CLIENT) $(PRINTF_DIR)/ft_printf.a
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT) $(PRINTF_DIR)/ft_printf.a $(INCLUDES)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	make -C $(PRINTF_DIR) clean

re: fclean all

.PHONY: all clean fclean re


