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

NAME = libclist.a
LIBDIR = ../

SRC 	=	src/chained_list_concat.c		\
			src/chained_list_create.c 	\
			src/chained_list_data_destructor.c	\
			src/chained_list_destroy.c	\
			src/chained_list_exec.c	\
			src/chained_list_find.c	\
			src/chained_list_print.c	\
			src/chained_list_remove.c	\
			src/chained_list_build.c	\
			src/chained_list_dup.c	\

CRIT_LIST	=	../../tests/lib/clist/test_list_init.c \
				../../tests/lib/clist/test_list_concat.c \
				../../tests/lib/clist/test_list_data_destructor.c \
				../../tests/lib/clist/test_list_destroy.c \
				../../tests/lib/clist/test_list_exec.c \
				../../tests/lib/clist/test_list_find.c \
				../../tests/lib/clist/test_list_print.c \
				../../tests/lib/clist/test_list_remove.c \
				../../tests/lib/clist/test_list_build.c \
				../../tests/lib/clist/test_list_dup.c \
				../../tests/lib/clist/test_string.c \

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
