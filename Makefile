COMP = clang++

COMP_FLAGS = -Wall -Wextra -Werror -std=c++98

EXEC_NAME = test

all:

vector:
	@$(COMP) $(COMP_FLAGS) test_vector.cpp -o $(EXEC_NAME)
	@./$(EXEC_NAME)

stack:
	@$(COMP) $(COMP_FLAGS) test_stack.cpp -o $(EXEC_NAME)
	@./$(EXEC_NAME)

map:
	@$(COMP) $(COMP_FLAGS) test_map.cpp -o $(EXEC_NAME)
	@./$(EXEC_NAME)

map_iter:
	@$(COMP) $(COMP_FLAGS) test_map_iter.cpp -o $(EXEC_NAME)
	@./$(EXEC_NAME)

algorithm:
	@$(COMP) $(COMP_FLAGS) test_algorithm.cpp -o $(EXEC_NAME)
	@./$(EXEC_NAME)

type_traits:
	@$(COMP) $(COMP_FLAGS) test_type_traits.cpp -o $(EXEC_NAME)
	@./$(EXEC_NAME)

utilities:
	@$(COMP) $(COMP_FLAGS) test_utilities.cpp -o $(EXEC_NAME)
	@./$(EXEC_NAME)

leaks:
	@valgrind --leak-check=full ./$(EXEC_NAME)

fclean:
	@rm $(EXEC_NAME)

.PHONY: vector stack map map_iter leaks fclean
