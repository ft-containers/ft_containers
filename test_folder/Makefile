NAME = TEST

CXX = c++ -g3 -fsanitize=address
# CXXFLAGS = -Wall -Wextra -Werror -g3
# -std=c++98 -pedantic

SRCS = test_vector.cpp 
#		enable_if.cpp 
		

OBJS = $(SRCS:.cpp=.o)
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
