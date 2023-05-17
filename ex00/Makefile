NAME = program

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

leakcheck: $(NAME)
	leaks --atExit -q -- ./$(NAME)

format:
	clang-format -style=google $(SRCS) $(INCLUDES) -i
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem . -I .

.PHONY: all clean fclean re run format debug leakcheck
