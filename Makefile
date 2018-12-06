
NAME = vm

SRC_FILES = main.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

SRC_DIR = src/

OBJ_DIR = obj/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

HEADER = -I includes

WWW = -Wall -Wextra -Werror

COLOR = \x1b[38;5;218m

RESET_COLOR = \033[0m

all: $(NAME)


$(NAME): $(OBJ)
		clang++ lexer.cpp parser.cpp $(OBJ) -o $(NAME)
		@echo "$(COLOR)***		$(NAME) compiled			***$(RESET_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
		@mkdir -p $(OBJ_DIR)
		flex -o lexer.cpp lexer.l
		bison -o parser.cpp parser.y
		clang++ $(WWW) -o $@ -c $<
		@echo "$(COLOR)***		obj files compiled		***$(RESET_COLOR)"

clean:
		@rm -rf $(OBJ_DIR)
		@echo "$(COLOR)***		obj files deleted		***$(RESET_COLOR)"

fclean: clean
		@rm -f $(NAME)
		@echo "$(COLOR)***		$(NAME) deleteed		***$(RESET_COLOR)"

re: fclean all

