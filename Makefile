FT_NAME = ft_bin

STD_NAME = std_bin

FT_BONUS = ft_bin_bonus

STD_BONUS = std_bin_bonus

CC = clang++

CLFAGS = -Isrc/ -Wall -Wextra -Werror -std=c++98

TEST_FILES = vector_test.cpp stack_test.cpp map_test.cpp

SRC = $(addsuffix .cpp, $(TEST_FILES))

all: $(STD_NAME) $(FT_NAME)

$(STD_NAME):
	$(CC) $(CLFAGS) -o $(STD_NAME) $(TEST_FILES) main.cpp

$(FT_NAME):
	$(CC) -DFT $(CLFAGS) -o $(FT_NAME) $(TEST_FILES) main.cpp

bonus: all
	$(CC) $(CLFAGS) -o $(STD_BONUS) set_test.cpp bonus_main.cpp
	$(CC) -DFT $(CLFAGS) -o $(FT_BONUS) set_test.cpp bonus_main.cpp

clean:
	rm -rf $(FT_NAME) $(STD_NAME) diff $(FT_BONUS) $(STD_BONUS)

fclean: clean

re: fclean all