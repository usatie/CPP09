NAME = PMergeMe

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

SRCDIR	= src
SRCS	= $(wildcard $(SRCDIR)/*.cpp)
INCLUDES	= $(wildcard $(SRCDIR)/*.hpp)
OBJDIR	= obj
OBJS	= $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $^ $(CXXFLAGS) -c -o $@

clean:
	$(RM) *.o
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

debug: CXXFLAGS += -D DEBUG
debug: re

run: $(NAME)
	./$(NAME)
	./$(NAME) `jot -r 1 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 2 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 3 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 4 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 5 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 21 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 100 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 1000 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 10000 1 100000 | tr '\n' ' '` | tail -n +3
	./$(NAME) `jot -r 50000 1 100000 | tr '\n' ' '` | tail -n +3

leakcheck: $(NAME)
	leaks --atExit -q -- ./$(NAME)

format:
	clang-format -style=google $(SRCS) $(INCLUDES) -i
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem . -I .

.PHONY: all clean fclean re run format debug leakcheck
