##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

BEGINL		= 	\033[A
CLEARL		= 	\033[2K
COL_END		= 	\033[0m
GRAY		=	\033[1;30m
RED			=	\033[1;31m
GREEN 		= 	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

RESET		=	\033[0m

NAME = libmystr.a
LIBDIR = ../

SRC 	=	src/matrix_len.c \
			src/my_getnbr.c \
			src/my_str_copy_cat.c \
			src/my_str_isalphanum.c \
			src/my_str_isnum.c \
			src/my_str_to_word_array.c \
			src/my_strcat.c \
			src/my_strcmp.c \
			src/my_strcpy.c \
			src/my_strncmp.c \
			src/fprintf/my_fprintf.c \
			src/fprintf/my_fputchar.c \
			src/fprintf/my_fputstr.c \
			src/fprintf/my_fputnbr.c \

CRIT_LIST	=	\

SRC_CRIT = $(SRC)
TEST_CRIT = $(CRIT_LIST)

OBJ = 	$(SRC:%.c=%.o)

CFLAGS = -W -Wall -Wextra -Iinclude
CRITFLAGS = -lcriterion --coverage

FILE_AMOUNT = $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find . -type f -name "*.o" | wc -l | sed -e 's/ //g')
CURRENT_FILE = $(shell echo "$$(( $(CURRENT_FILES) + 1 ))")
PERCENT = $(shell echo "$$(( $(CURRENT_FILE) * 10 / $(FILE_AMOUNT) ))")
PERCENT_LEFT = $(shell echo "$$(( 10 - $(PERCENT) ))")

%.o: %.c
	@$(CC) $(CFLAGS) $^ -c -o $@
	@echo -en "$(CLEARL)$(BLUE)building$(RESET): [$(GREEN)"
	@for i in `seq 1 $(PERCENT)`; do \
		echo -n "█"; \
	done
	@for i in `seq 1 $(PERCENT_LEFT)`; do \
		echo -n " "; \
	done
	@echo -en  "$(RESET)] ($(CURRENT_FILE)/$(FILE_AMOUNT))"
	@echo -e " [$(CYAN)$(notdir $^)$(RESET)]$(BEGINL)"

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@mv $(NAME) $(LIBDIR)
	@echo -e "$(CLEARL)$(GREEN)✓ Compiled $(NAME)$(RESET)$(COL_END)"

all:	$(NAME)

clean:
	@rm -f $(OBJ)
	@rm -f *~
	@rm -f #*#
	@rm -f *.gcda
	@rm -f *.gcno
	@echo -e "$(CLEARL)[$(YELLOW)Cleaned $(NAME)$(RESET)]$(BEGINL)"

fclean: clean
	@rm -f $(LIBDIR)$(NAME)
	@rm -f unit-tests
	@echo -e "$(CLEARL)[$(YELLOW)Fcleaned $(NAME)$(RESET)]$(BEGINL)"

re: fclean all

tests_run:
	@gcc -o unit-tests $(SRC_CRIT) $(TEST_CRIT) $(CFLAGS) $(CRITFLAGS)
	@echo -e "[$(GREEN)Launch tests $(NAME)$(RESET)]"
	@./unit-tests

.PHONY: all clean fclean re
