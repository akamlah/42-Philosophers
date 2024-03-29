# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/12 21:52:44 by akamlah           #+#    #+#              #
#    Updated: 2022/01/14 13:35:30 by alicekamlah      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PHILOSOPHERS - Makefile

# **************************************************************************** #
# FLAGS
# **************************************************************************** #

CC=gcc
C_FLAGS=-Wall -Wextra -Werror -pthread

# for testing and debugging purposes:
# (run `make fsa' or `make fst' to apply)
FST_FLAG=-g -fsanitize=thread
FSA_FLAG=-g -fsanitize=address

# **************************************************************************** #
# PROGRAM
# **************************************************************************** #

NAME=philo_bonus

SRC_DIR=./src/
OBJ_DIR=./obj/

SRC_LIST= \
phb_main.c \
ph_parse.c \
phb_init.c \
phb_simulation.c \
phb_cycle.c \
ft_atoi.c \
ft_strlen.c \

SRC=$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ=$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_LIST)))

HEADER=./header/philosophers_bonus.h

# **************************************************************************** #
# COLORS
# **************************************************************************** #

WHITEBAR=\033[0;50m
RED=\033[0;31m
NC=\033[0m
GREEN=\033[0;32m
TURQOISE=\033[0;36m
PINK=\033[0;35m
YELLOW=\033[0;33m
YELLOW_BLK=\033[5;33m

# **************************************************************************** #
# RULES
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(HEADER)

	@$(CC) $(OBJ) $(C_FLAGS) $(LFLAGS) $(CPFLAGS) -o $@
	@echo "\n$(GREEN)Created executable: \`$(NAME)' $(NC)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "$(NC)Creating object-files$(NC)\c"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(C_FLAGS) $(CPFLAGS) $^ -c -o $@
	@echo "$(NC).$(NC)\c"

clean:
	@rm -f $(OBJ) *~
	@rm -f -d $(OBJ_DIR) *~
	@echo "$(RED)Deleting:\tobject-files ...$(NC)"

fclean:
	@rm -f $(OBJ) *~
	@rm -f -d $(OBJ_DIR) *~
	@echo "$(RED)Deleting object-files ...$(NC)"
	@rm -f $(NAME)
	@echo "$(RED)Deleting executable: \`$(NAME)'$(NC)"

re:
	@make fclean
	@make $(NAME)


# **************************************************************************** #
# debug & test
# **************************************************************************** #

# Recompie with fsanitize flags:
# =address
fsa: fclean $(OBJ_DIR) $(OBJ) $(HEADER)

	@$(CC) $(OBJ) $(C_FLAGS) $(FSA_FLAG) $(LFLAGS) $(CPFLAGS) -o $(NAME)
	@echo "\nRecompiled with: $(PINK)$(FSA_FLAG)\n\
	$(GREEN)Created executable: \`$(NAME)' $(NC)"
# =thread
fst: fclean $(OBJ_DIR) $(OBJ) $(HEADER)

	@$(CC) $(OBJ) $(C_FLAGS) $(FST_FLAG) $(LFLAGS) $(CPFLAGS) -o $(NAME)
	@echo "\nRecompiled with: $(TURQOISE)$(FST_FLAG)\n\
	$(GREEN)Created executable: \`$(NAME)' $(NC)"

#option:
#\
TESTS="2 420 200 200" \
	"5 800 200 200" \
	@for d in $(LIBS);\
	do\
		$(MAKE) -C $$d;\
	done;\


# TESTS
# "make test_d1" -> one philo must die in every testcase
test_d1: all
	@echo "$(YELLOW)TEST 1: one must die\n$(NC)"
	
	@echo "$(YELLOW)philo 4 310 200 100$(NC)"
	@./philo_bonus 4 310 200 100
	
	@echo "$(YELLOW)\nphilo 3 550 200 200$(NC)"
	@./philo_bonus 3 550 200 200
	
	@echo "$(YELLOW)\nphilo 2 100 100 100$(NC)"	
	@./philo_bonus 2 100 100 100

	@echo "$(YELLOW)\nphilo 2 150 100 100 - one philo should die in his sleep (150)$(NC)"
	@./philo_bonus 2 150 100 100

	@echo "$(YELLOW)\nend of test$(NC)"

#TESTS that should run infinitely
test_fe1: all
	@echo "$(YELLOW_BLK)should run for ever 2 420 200 200$(NC)"
	#@sleep 3s
	./philo_bonus 2 420 200 200

test_fe2: all
	@echo "$(YELLOW_BLK)should run for ever 5 800 200 200$(NC)"
	#@sleep 3s
	./philo_bonus 5 800 200 200

test_fe3: all
	@echo "$(YELLOW_BLK)should run for ever 4 410 200 200$(NC)"
	#@sleep 3s
	./philo_bonus 4 410 200 200

test_fe4: all
	@echo "$(YELLOW_BLK)should run for ever 30 550 200 200$(NC)"
	#@sleep 3s
	./philo_bonus 30 550 200 200

test_fe5: all
	@echo "$(YELLOW_BLK)should run for ever 99 620 200 200$(NC)"
	#@sleep 3s
	./philo_bonus 99 620 200 200

test_fe6: all
	@echo "$(YELLOW_BLK)should run for ever 98 440 200 200$(NC)"
	#@sleep 3s
	./philo_bonus 98 440 200 200

test_fe7: all
	@echo "$(YELLOW_BLK)should run for ever 198 440 200 200$(NC)"
	#@sleep 3s
	./philo_bonus 198 440 200 200

test_fe8: all
	@echo "$(YELLOW_BLK)should run for ever 199 620 200 200$(NC)"
	#@sleep 3s
	./philo_bonus 199 620 200 200

test_fe9: all
	@echo "$(YELLOW_BLK)should run for ever 2 121 60 60$(NC)"
	#@sleep 3s
	./philo_bonus 2 121 60 60

test_d800:
	./philo_bonus 1 800 200 200
	@echo "die after 800 milliseconds"

test_opt1: all
	./philo_bonus 5 800 200 200 7
	@echo "end after 7 meals_per_philo"

test_opt2:
	./philo_bonus 30 800 200 200 7
	@echo "end after 7 meals_per_philo"