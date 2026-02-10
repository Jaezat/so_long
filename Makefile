# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/27 16:31:27 by mariacos          #+#    #+#              #
#    Updated: 2025/11/10 11:40:54 by mariacos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = so_long
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g

# Directories
SRC_DIR         = src
OBJ_DIR         = obj
INC_DIR         = include
LIBFT_PATH      = libft/
LIBFT_SRC       = $(LIBFT_PATH)src/
LIBFT_INC       = $(LIBFT_PATH)include/
LIBFT_LIB       = $(LIBFT_SRC)libft.a
MLX_PATH        = mlx_linux/
MLX_LIB         = $(MLX_PATH)libmlx.a
MLX_FLAGS       = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
MLX_REPO        = https://github.com/42Paris/minilibx-linux.git

# Source files organized by subdirectory
GRAPHICS_SRC    = graphics/draw_map.c \
                  graphics/image_loader.c \
                  graphics/mlx_init.c \
                  graphics/movement.c

MAP_SRC         = map/map_init.c \
                  map/map_parsing.c \
                  map/map_pathfinding.c \
                  map/map_validation.c

UTILS_SRC       = utils/cleanup.c \
                  utils/error.c

MAIN_SRC        = main.c

# All source files with src/ prefix
CFILES          = $(MAIN_SRC) $(GRAPHICS_SRC) $(MAP_SRC) $(UTILS_SRC)
SRC             = $(addprefix $(SRC_DIR)/, $(CFILES))
OBJECTS         = $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

# Valgrind
VALGRIND        = valgrind
VALGRIND_FLAGS  = --leak-check=full \
                  --show-leak-kinds=all \
                  --track-origins=yes \
                  --verbose \
                  --log-file=valgrind-out.txt
VALGRIND_MAP    = maps/test.ber
RM              = rm -rf

# Rules
all: $(NAME)
	@echo "✓ Compilation complete!"

# Create obj directory and subdirectories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/graphics
	@mkdir -p $(OBJ_DIR)/map
	@mkdir -p $(OBJ_DIR)/utils

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_PATH) -I$(LIBFT_INC) -c $< -o $@

# Link executable
$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJECTS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX_FLAGS) $(MLX_LIB) $(LIBFT_LIB) -o $(NAME)
	@echo "✓ $(NAME) created successfully!"

# Download and compile MLX
$(MLX_PATH):
	@echo "Downloading MLX library from GitHub..."
	@git clone $(MLX_REPO) $(MLX_PATH)
	@echo "✓ MLX library downloaded!"

$(MLX_LIB): | $(MLX_PATH)
	@echo "Compiling MLX library..."
	@make -C $(MLX_PATH) --no-print-directory > /dev/null 2>&1
	@echo "✓ MLX library ready!"

# Compile libft
$(LIBFT_LIB):
	@echo "Compiling libft library..."
	@make extra -C $(LIBFT_SRC) --no-print-directory
	@echo "✓ Libft library ready!"

clean:
	@echo "Cleaning object files..."
	@if [ -d "$(MLX_PATH)" ]; then \
		make clean -C $(MLX_PATH) --no-print-directory > /dev/null 2>&1 || true; \
	fi
	@make clean -C $(LIBFT_PATH)src --no-print-directory > /dev/null 2>&1 || true
	@$(RM) $(OBJ_DIR)
	@echo "✓ Object files cleaned!"

fclean: clean
	@echo "Removing executable and libraries..."
	@if [ -d "$(MLX_PATH)" ]; then \
		make fclean -C $(MLX_PATH) --no-print-directory > /dev/null 2>&1 || true; \
	fi
	@make fclean -C $(LIBFT_PATH)src --no-print-directory > /dev/null 2>&1 || true
	@$(RM) $(NAME)
	@$(RM) valgrind-out.txt
	@echo "✓ Full clean complete!"

fclean_all: fclean
	@echo "Removing MLX library..."
	@$(RM) $(MLX_PATH)
	@echo "✓ MLX library removed!"

re: fclean all

# Valgrind Tests
valgrind: $(NAME)
	@echo "Running valgrind tests..."
	@$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME) $(VALGRIND_MAP)
	@echo "✓ Check valgrind-out.txt for results"

valgrind-error: $(NAME)
	@echo "Running valgrind with error check..."
	@$(VALGRIND) --leak-check=full --error-exitcode=1 ./$(NAME) $(VALGRIND_MAP)

vg: $(NAME)
	@echo "Running quick valgrind test..."
	@$(VALGRIND) --leak-check=full --show-leak-kinds=all ./$(NAME) $(VALGRIND_MAP)

valgrind-supp: $(NAME)
	@echo "Running valgrind with suppressions..."
	@$(VALGRIND) $(VALGRIND_FLAGS) --suppressions=.valgrind_suppress ./$(NAME) $(VALGRIND_MAP)

# Help message
help:
	@echo "Available targets:"
	@echo "  make                   - Compile the project"
	@echo "  make clean             - Remove object files"
	@echo "  make fclean            - Remove object files and executable"
	@echo "  make fclean_all        - Remove everything including MLX"
	@echo "  make re                - Recompile everything"
	@echo "  make valgrind          - Run valgrind with full report"
	@echo "  make vg                - Run quick valgrind test"
	@echo "  make valgrind-error    - Run valgrind that exits on error"
	@echo "  make help              - Show this help message"

.PHONY: all clean fclean fclean_all re valgrind valgrind-error vg valgrind-supp help