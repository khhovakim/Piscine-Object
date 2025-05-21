# ===== Colors for pretty output =====
_GREY=	\033[1;30m
_RED=	\033[1;31m
_GREEN=	\033[1;32m
_YELLOW=\033[1;33m
_BLUE=	\033[1;34m
_PURPLE=\033[1;35m
_CYAN=	\033[1;36m
_WHITE=	\033[1;37m
_NC=	\033[0m

# ===== Executable name =====
NAME = banking

# ===== Directories =====
SRCDIR = src
INCDIR = include
OBJDIR = obj

# ===== Find all .cpp files in src and subfolders =====
SRC = main.cpp \
      $(shell find $(SRCDIR) -name '*.cpp')

# ===== vpath tells make where to find these files =====
vpath %.cpp $(SRCDIR)
vpath %.h   $(INCDIR)

# ===== Turn source files into object files in obj/ folder =====
OBJ = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

# ===== Compiler and flags =====
CXX      = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -fsanitize=address
INCLUDES = -I$(INCDIR)

# ===== Default target =====
.PHONY: all
all: $(NAME)

# ===== Linking final executable =====
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)
	@printf "$(_GREEN)[✔] Linked $(NAME)\n$(_NC)"

# ===== Compiling .cpp to .o =====
$(OBJDIR)/%.o: %.cpp $(INCDIR)/*.h Makefile
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "$(_BLUE)[●] Compiled $< -> $@\n$(_NC)"

# ===== Clean object files only =====
.PHONY: clean
clean:
	@rm -rf $(OBJDIR)
	@printf "$(_YELLOW)[✗] Removed object files\n$(_NC)"

# ===== Clean everything =====
.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	@printf "$(_YELLOW)[✗] Removed executable $(NAME)\n$(_NC)"

# ===== Rebuild everything =====
.PHONY: re
re: fclean all
