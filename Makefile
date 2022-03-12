NAME			:= span
CXX				:= clang++
CXXFLAGS		:= -Wall -Wextra -Werror -MMD -MP -std=c++98
SRCSDIR			:= .
OBJSDIR			:= objs
SRCS			:= $(shell find $(SRCSDIR) -type f -name "*.cpp" | xargs basename -a)
INCLUDES		:= $(shell find $(SRCSDIR) -type d | awk '{print "-I " $$0}')
VPATH			:= $(shell find $(SRCSDIR) -type d | awk '{print $$0":"}')
OBJS			:= $(SRCS:%.cpp=$(OBJSDIR)/%.o)
DEPENDS			:= $(OBJS:.o=.d);

GTEST_DIR	=	./test
GTEST		=	$(GTEST_DIR)/gtest $(GTEST_DIR)/googletest-release-1.11.0

all: $(NAME)

-include $(DEPENDS)

$(OBJSDIR)/%.o : %.cpp
	@if [ ! -d $(OBJSDIR) ]; then mkdir $(OBJSDIR); fi;
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

$(GTEST):
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -zxvf release-1.11.0.tar.gz
	$(RM) release-1.11.0.tar.gz
	python googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(GTEST_DIR)
	mv googletest-release-1.11.0 $(GTEST_DIR)

test: $(GTEST)