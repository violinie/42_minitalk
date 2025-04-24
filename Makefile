# Project Name (not used to build a target here)
NAME = minitalk

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRC_S = server.c
SRC_C = client.c

# Object files
OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

# Targets
all: server client

server: $(OBJ_S)
	$(CC) $(CFLAGS) $(OBJ_S) -o server
	@echo "✅ server built"

client: $(OBJ_C)
	$(CC) $(CFLAGS) $(OBJ_C) -o client
	@echo "✅ client built"

clean:
	rm -f $(OBJ_S) $(OBJ_C)
	@echo "🧹 objects cleaned"

fclean: clean
	rm -f server client
	@
