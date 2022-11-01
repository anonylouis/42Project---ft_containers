CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98 -g

OTHERS_FILES = RBT_set.hpp RBT.hpp pair.hpp enable_if.hpp equal.hpp is_integral.hpp iterators_traits.hpp lexicographical_compare.hpp reverse_iterator.hpp
OTHERS = $(addprefix ./other/, $(HEADER_FILES))

VECTOR1 = ft_vector
VECTOR2 = std_vector

STACK1 = ft_stack
STACK2 = std_stack

MAP1 = ft_map
MAP2 = std_map

SET1 = ft_set
SET2 = std_set

all : vector stack map

bonus : set

## VECTOR 
vector : $(VECTOR1) $(VECTOR2)

$(VECTOR1) :	./objs/ft_vector.o
				$(CC) $(FLAGS) -o $@ $< -D REAL=0

$(VECTOR2) :	./objs/std_vector.o
				$(CC) $(FLAGS) -o $@ $< -D REAL=1

## STACK
stack : $(STACK1) $(STACK2)

$(STACK1) :	./objs/ft_stack.o
			$(CC) $(FLAGS) -o $@ $< -D REAL=0

$(STACK2) : ./objs/std_stack.o
			$(CC) $(FLAGS) -o $@ $< -D REAL=1

## MAP
map : $(MAP1) $(MAP2)

$(MAP1) :	./objs/ft_map.o
			$(CC) $(FLAGS) -o $@ $< -D REAL=0

$(MAP2) : ./objs/std_map.o
			$(CC) $(FLAGS) -o $@ $< -D REAL=1

## SET
set : $(SET1) $(SET2)

$(SET1) :	./objs/ft_set.o
			$(CC) $(FLAGS) -o $@ $< -D REAL=0

$(SET2) : ./objs/std_set.o
			$(CC) $(FLAGS) -o $@ $< -D REAL=1

## OTHER RULES

clean : 
		rm -rf ./objs

fclean :	clean 
			rm -f $(VECTOR1)
			rm -f $(VECTOR2)
			rm -f $(STACK1)
			rm -f $(STACK2)
			rm -f $(MAP1)
			rm -f $(MAP2)
			rm -f $(SET1)
			rm -f $(SET2)

re : fclean all

## OBJS FILES

./objs/ft_vector.o :	./main/vector.cpp ./includes/vector.hpp $(OTHERS)
						mkdir -p objs
						$(CC) $(FLAGS) -MMD -o $@ -c $< -D REAL=0

./objs/std_vector.o :	./main/vector.cpp ./includes/vector.hpp $(OTHERS)
						mkdir -p objs
						$(CC) $(FLAGS) -MMD -o $@ -c $< -D REAL=1

./objs/ft_stack.o :		./main/stack.cpp ./includes/stack.hpp ./includes/vector.hpp $(OTHERS)
						mkdir -p objs
						$(CC) $(FLAGS) -MMD -o $@ -c $< -D REAL=0

./objs/std_stack.o :	./main/stack.cpp ./includes/stack.hpp ./includes/vector.hpp $(OTHERS)
						mkdir -p objs
						$(CC) $(FLAGS) -MMD -o $@ -c $< -D REAL=1

./objs/ft_map.o :		./main/map.cpp ./includes/map.hpp $(OTHERS)
						mkdir -p objs
						$(CC) $(FLAGS) -MMD -o $@ -c $< -D REAL=0

./objs/std_map.o :		./main/map.cpp ./includes/map.hpp $(OTHERS)
						mkdir -p objs
						$(CC) $(FLAGS) -MMD -o $@ -c $< -D REAL=1

./objs/ft_set.o :		./main/set.cpp ./includes/set.hpp $(OTHERS)
						mkdir -p objs
						$(CC) $(FLAGS) -MMD -o $@ -c $< -D REAL=0

./objs/std_set.o :		./main/set.cpp ./includes/set.hpp $(OTHERS)
						mkdir -p objs
						$(CC) $(FLAGS) -MMD -o $@ -c $< -D REAL=1

.PHONY : all re clean fclean vector stack map set bonus

