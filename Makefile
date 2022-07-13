NAME			:= span
CXX				:= clang++
CXXFLAGS		:= -Wall -Wextra -Werror -MMD -MP -std=c++98
SRCS_DIR		:= .
OBJS_DIR		:= objs
SRCS			:= $(shell find $(SRCS_DIR) -type f -name "*.cpp" | xargs basename -a)
INCLUDES		:= $(shell find $(SRCS_DIR) -type d | awk '{print "-I " $$0}')
VPATH			:= $(shell find $(SRCS_DIR) -type d | awk '{print $$0":"}')
OBJS			:= $(SRCS:%.cpp=$(OBJS_DIR)/%.o)
DEPENDS			:= $(OBJS:.o=.d);

all: $(GTEST)

-include $(DEPENDS)

$(OBJS_DIR)/%.o : %.cpp
	@if [ ! -d $(OBJS_DIR) ]; then mkdir $(OBJS_DIR); fi;
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


GTESTER_NAME	:= g_tester

GTEST_DIR		:= googletest
GTEST			:= $(GTEST_DIR)/gtest $(GTEST_DIR)/googletest-release-1.11.0

TEST_DIR		:= testcases
TEST_SRCS		:= $(shell find $(TEST_DIR) -type f -name "*.cpp" | xargs basename -a)

TEST_OBJS_DIR	:= testobjs
TEST_OBJS		:= $(TEST_SRCS:%.cpp=$(TEST_OBJS_DIR)/%.o)

TEST_INCLUDES	:= -I includes -I $(GTEST_DIR)
TEST_FLAGS		:= -MMD -MP -std=c++11

TEST_DEPENDS	:= $(OBJS:.o=.d);

-include $(TEST_DEPENDS)

$(TEST_OBJS_DIR)/%.o : $(TEST_DIR)/%.cpp
	echo $(TEST_SRCS)
	@if [ ! -d $(TEST_OBJS_DIR) ]; then mkdir $(TEST_OBJS_DIR); fi;
	$(CXX) $(TEST_FLAGS) $(TEST_INCLUDES) -c $< -o $@

$(GTEST):
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -zxvf release-1.11.0.tar.gz
	$(RM) release-1.11.0.tar.gz
	python googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(GTEST_DIR)
	mv googletest-release-1.11.0 $(GTEST_DIR)

$(GTESTER_NAME): $(GTEST) $(TEST_OBJS)
	clang++ -std=c++11 \
	$(TEST_OBJS) $(GTEST_DIR)/googletest-release-1.11.0/googletest/src/gtest_main.cc $(GTEST_DIR)/gtest/gtest-all.cc \
	-I$(GTEST_DIR) -lpthread -o $(GTESTER_NAME)

gtest: $(GTESTER_NAME)
	clear
	./g_tester

.PHONY: all clean fclean re gtest