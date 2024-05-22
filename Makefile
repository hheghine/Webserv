################################################################################
#                                  VISUALS                                     #
################################################################################

WHITE	= \033[1;37m
GREY 	= \033[1;90m
GREEN	= \033[0;32m
BLINK	= \033[5m
END		= \033[0m

COLOR_1 = \033[38;2;153;255;255m
COLOR_2 = \033[38;2;153;255;224m
COLOR_3 = \033[38;2;153;255;193m
COLOR_4 = \033[38;2;153;255;163m
COLOR_5 = \033[38;2;153;255;132m
COLOR_6 = \033[38;2;153;255;102m


NAME_LINE_1 = ██╗    ██╗███████╗██████╗ ███████╗███████╗██████╗ ██╗   ██╗							\n
NAME_LINE_2 = ██║    ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║							\n
NAME_LINE_3 = ██║ █╗ ██║█████╗  ██████╔╝███████╗█████╗  ██████╔╝██║   ██║							\n
NAME_LINE_4 = ██║███╗██║██╔══╝  ██╔══██╗╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝							\n
NAME_LINE_5 = ╚███╔███╔╝███████╗██████╔╝███████║███████╗██║  ██║ ╚████╔╝ 							\n
NAME_LINE_6 =  ╚══╝╚══╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝								\n

PRINT_NAME = printf "\n$(COLOR_1) %4s $(NAME_LINE_1) %4s $(COLOR_2)$(NAME_LINE_2) %4s $(COLOR_3)$(NAME_LINE_3) %4s $(COLOR_4)$(NAME_LINE_4) %4s $(COLOR_5)$(NAME_LINE_5) %5s $(COLOR_6)$(NAME_LINE_6)\n"

################################################################################
#                                  COMPILATION                                 #
################################################################################

SRCS_DIR	= src/
PARSER_DIR	= $(SRCS_DIR)parser/
UTILS_DIR	= $(SRCS_DIR)utils/
CORE_DIR	= $(SRCS_DIR)core/

SRC_FILES	= $(SRCS_DIR)main.cpp \
				$(addprefix $(CORE_DIR), a_server.cpp server.cpp) \
				$(addprefix $(UTILS_DIR), utils.cpp) \
				$(addprefix $(PARSER_DIR), parser.cpp)

INCLUDES	=	-Iinc \
					-Iinc/parser \
					-Iinc/utils \
					-Iinc/core \

CXX			= @c++
CXXFLAGS 	= -g3 -Wall -Wextra -Werror -std=c++98 $(INCLUDES) -fsanitize=address


OBJS_DIR	= .objects
OBJS 		= $(SRC_FILES:%.cpp=$(OBJS_DIR)/%.o)

NAME 		= webserv

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@printf "$(COLOR_6)%15s Compilation of $(END)$(WHITE)$(NAME)$(COLOR_6) terminated $(END)$(WHITE)$(BLINK)[$(COLOR_6)$(BLINK)success$(BLINK)$(WHITE)]$(END)\n\n"
	
$(OBJS_DIR) :
	@$(PRINT_NAME)
	@sleep 0.1
	@printf "$(WHITE)$(COLOR_6)%25s Compiling $(END)$(WHITE)$(NAME)...\n"
	@printf "$(COLOR_6)%24s Creating $(END)$(WHITE)$(OBJS_DIR)...\n"
	@mkdir -p $(OBJS_DIR)
	@sleep 0.1
	@printf "$(COLOR_6)%24s Creating $(END)$(WHITE)$(OBJS_DIR)/$(SRCS_DIR)...\n"
	@mkdir -p $(OBJS_DIR)/$(SRCS_DIR)
	@sleep 0.1
	@printf "$(COLOR_6)%21s Creating $(END)$(WHITE)$(OBJS_DIR)/$(PARSER_DIR)...\n"
	@mkdir -p $(OBJS_DIR)/$(PARSER_DIR)
	@sleep 0.1
	@printf "$(COLOR_6)%21s Creating $(END)$(WHITE)$(OBJS_DIR)/$(UTILS_DIR)...\n"
	@mkdir -p $(OBJS_DIR)/$(UTILS_DIR)
	@sleep 0.1
	@printf "$(COLOR_6)%21s Creating $(END)$(WHITE)$(OBJS_DIR)/$(CORE_DIR)...\n"
	@mkdir -p $(OBJS_DIR)/$(CORE_DIR)

$(OBJS) : $(OBJS_DIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS_DIR)
	@printf "\n$(WHITE)$(COLOR_6)%15s Removing the $(END)$(WHITE)$(OBJS_DIR)$(COLOR_6) directory...\n"

fclean : clean
	@rm -rf $(NAME)
	@printf "$(COLOR_6)%20s Removing $(END)$(WHITE)$(NAME) $(WHITE)$(BLINK)[$(COLOR_6)$(BLINK)success$(BLINK)$(WHITE)]$(END)\n\n"

re : fclean all

.PHONY: all clean fclean re