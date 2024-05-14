NAME		=	scop

IMGUI_DIR	=	./includes/imgui
INCLUDES	=	./includes
GLAD		=	./includes/include/glad

SRC_DIR		=	./srcs
SRC			=	main.cpp							\
				

OBJ			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC))))

SRC_LIB			+=	$(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SRC_LIB			+=	$(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

OBJ_DIR 	=	./obj
OBJ			+=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(SRC_LIB)))))

CC			=	clang++

CFLAGS		=	-g -std=c++17 -I$(IMGUI_DIR) -I$(INCLUDES) -I$(GLAD) -I$(IMGUI_DIR)/backends -Wall -Wextra -Werror

LIBS 		=	-lglut

ifeq ($(shell uname),Darwin)
	CFLAGS += -Wno-deprecated-declarations
    LIBS += -lglfw -framework OpenGL -framework GLUT -framework IOKit -framework Cocoa 
else
    # Other operating systems
    LIBS += -lglfw -lGL -ldl
endif

all: $(OBJ_DIR) glad.o $(NAME)
	clear
	@make header --no-print-directory

submodules:
	git submodule init
	git submodule update

$(OBJ_DIR):
	@if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi
	@if [ ! -d "$(OBJ_DIR)/ArcticFeather" ]; then mkdir $(OBJ_DIR)/ArcticFeather; fi

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) glad.o $(LIBS)

glad.o: $(INCLUDES)/src/glad.c
	clang -I$(INCLUDES)/include $(INCLUDES)/src/glad.c -c -o glad.o 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.o:$(IMGUI_DIR)/%.cpp
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o:$(IMGUI_DIR)/backends/%.cpp
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

run: all
	@printf "Arguments: "
	@read ARGS; \
	./$(NAME) $$ARGS

commit:
	@make fclean --no-print-directory
	@git add *
	@printf "Commit message: "
	@read MESSAGE; \
	git commit -m "$$MESSAGE"

push:
	git push

fpush: commit push

work:
	@git pull
	@code .
	@make

test:
	clang++ -D TESTING $(CFLAGS) ./tests/CI_Matrix.cpp -o CI_Matrix
	./CI_Matrix
	rm ./CI_Matrix

.PHONY: all clean fclean re
-include header.mk
