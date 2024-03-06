# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 14:23:32 by lluque            #+#    #+#              #
#    Updated: 2024/03/06 11:49:45 by lluque           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories for source code, tester and headers (permanent), and for
# object files and binary output (volatile).
# (relative to repository root directory)
#
SRC_DIR = ./src/
INC_DIR = ./include/
TEST_DIR = ./test/
BIN_DIR = ./bin/
OBJ_DIR = ./obj/
LIBFT_DIR = ./lib/libft/
MLX42_DIR = ./lib/MLX42/

# Library libft binary
LIBFT_BIN = $(LIBFT_DIR)bin/libft.a

# Library libft include dir
LIBFT_INC = $(LIBFT_DIR)include/

# Library MLX42 binary
MLX42_BIN = $(MLX42_DIR)build/libmlx42.a

# Library MLX42 include dir
MLX42_INC = $(MLX42_DIR)include/MLX42/

# Resulting binary (to be placed in BIN_DIR)
NAME = fdf

# Resulting bonus output name (to be placed in BIN_DIR)
BONUS_NAME = fdf_bonus

# Resulting tester name (to be placed in BIN_DIR)
TESTER_NAME = tester

# Default value of DEBUG (if passed from command line DEBUG=yes overrides it)
DEBUG = no

# Optional debugging flags
#DEB_FLAGS = -g -fsanitize=address -D DEBUG=1							################################################# el -fsanitize=address es incompatible con valgrind
DEB_FLAGS = -g -D DEBUG=1

# Compiler flags, conditional to DEBUG value
ifeq ($(DEBUG), no)
	CC_FLAGS = -Wall -Werror -Wextra
else
	CC_FLAGS = -Wall -Werror -Wextra $(DEB_FLAGS)
endif

# Additional external library flags										################################################## Es lo mejor?
# GLFW: API for OpenGL needed by MLX42
# libdl: Dynamic loader (linking) library
# libm: math library
# pthread: POSIX thread library
EXT_LIBS = -ldl -lglfw -pthread -lm

# List of header file names that, if modified, should force recompiling
INCLUDES = $(INC_DIR)main_utils.h

# List of source code file names with path relative to SRC_DIR
SOURCES = fdf_main.c \
		  main_utils/fdf_filename_valid.c \
		  main_utils/fdf_args_valid.c \
		  lin_alg/ft_mx_create.c \
		  lin_alg/ft_mx_destroy.c \
		  lin_alg/ft_mx_print.c \
		  lin_alg/ft_mx_set_element.c \
		  lin_alg/ft_mx_get_element.c \
		  lin_alg/ft_mx_load_file.c \
		  lin_alg/ft_mx_set_row.c \
		  lin_alg/ft_mx_dup.c \
		  lin_alg/ft_mx_smult.c \
		  lin_alg/ft_mx_get_row.c \
		  lin_alg/ft_mx_mult.c \
		  lin_alg/ft_mx_mult3.c \
		  lin_alg/ft_mx_get_col.c \
		  lin_alg/ft_mx_create_id.c \
		  lin_alg/ft_mx_create_bid.c \
		  lin_alg/ft_mx_transpose.c \
		  lin_alg/ft_mx_flipr.c \
		  lin_alg/ft_mx_set_col.c \
		  tesselator/fdf_get_vertex_mx.c \
		  tesselator/fdf_get_edge_mx.c \
		  tesselator/fdf_create_rotmx.c \
		  tesselator/fdf_tesselate_map.c \
		  tesselator/fdf_create_model.c \
		  tesselator/fdf_destroy_model.c \
		  tesselator/fdf_create_ortoproj_mx.c \
		  tesselator/fdf_create_transl_mx.c \
		  tesselator/fdf_create_scale_mx.c \
		  drawing/fdf_drw_vertexes.c \
		  drawing/fdf_get_autofit_transf_matrixes.c \
		  drawing/fdf_render.c \
		  window/fdf_keyhook.c \
		  window/fdf_closehook.c \
		  window/fdf_start_gui.c \
		  window/fdf_resizehook.c \
		  window/fdf_create_wlayout.c \
		  window/fdf_destroy_wlayout.c \
		  window/fdf_recalc_wlayout.c \
		  fdf/fdf_create_fdf.c \
		  fdf/fdf_destroy_fdf.c

# List of BONUS source code file names with path relative to SRC_DIR
BONUS_SOURCES = ch_main.c

# Auto generated list of object file names from SOURCES
# (here the path is relative to repository's root)
#
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)

# Auto generated list of BONUS object file names from BONUS_SOURCES
# (here the path is relative to repository's root)
#
BONUS_OBJECTS = $(BONUS_SOURCES:%.c=$(OBJ_DIR)%.o)

# List of tester source code file names with path relative to TEST_DIR
TEST_SRC = tester.c

################################################################################
############### VARIABLES FOR DOXYGEN DOCUMENTATION GENERATION #################

# Doxyfile name, to be generated and edited in repository root directory
DOXYFILE = Doxyfile
DOC_DIR = ./doc/

# Project name for documentation purposes
DOX_PROJECT_NAME = Fdf

# Project brief description (one line)
DOX_PROJECT_BRIEF = Fdf project for Campus 42

# Version of the documentation (date for now)
DOX_PROJECT_NUMBER = $(shell date +%Y-%m-%d)

# Location with files to extract documentation from (.h)
# Look for more files in subdirectories
#
DOX_INPUT = $(INC_DIR) $(DOX_MAIN_PAGE)
DOX_RECURSIVE = YES

# Content for documentation main page
DOX_MAIN_PAGE = ./README.md

# Optimization for languages
DOX_OPTIMIZE_OUTPUT_FOR_C = YES

# Documentation formats to generate
DOX_GENERATE_HTML = YES
DOX_GENERATE_LATEX = NO
DOX_GENERATE_RTF = NO
DOX_GENERATE_MAN = NO

################ VARIABLES FOR DOXYGEN DOCUMENTATION GENERATION ################
################################################################################

# Default rule
all: $(BIN_DIR)$(NAME)

# Rule for NAME as phony
$(NAME): $(BIN_DIR)$(NAME)

# Rule to link the program
$(BIN_DIR)$(NAME): $(OBJECTS) $(LIBFT_BIN) 
	@echo ----------------------------------------------------------------------
	@echo
	@echo "          --- Linking the program to $(BIN_DIR)$(NAME) ---"
	mkdir -p $(@D)
	cc $(CC_FLAGS) $(OBJECTS) $(LIBFT_BIN) $(MLX42_BIN) $(EXT_LIBS) -o $(BIN_DIR)$(NAME) -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX42_INC)
 
	@echo
	@echo ----------------------------------------------------------------------

# Rule for bonus as phony
bonus: $(BIN_DIR)$(BONUS_NAME)

# Rule to link the bonus
$(BIN_DIR)$(BONUS_NAME): $(BONUS_OBJECTS) $(LIBFT_BIN) 
	@echo ----------------------------------------------------------------------
	@echo
	@echo "          --- Linking the program to $(BIN_DIR)$(BONUS_NAME) ---"
	mkdir -p $(@D)
	cc $(CC_FLAGS) $(BONUS_OBJECTS) $(LIBFT_BIN) $(MLX42_BIN) $(EXT_LIBS) -o $(BIN_DIR)$(BONUS_NAME) -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX42_INC)
	@echo
	@echo ----------------------------------------------------------------------

################################################################################
################## START OF PATTERN RULE TO COMPILE OBJECTS ####################
# Pattern rule to individually compile each object:
#
# 	targets: target-pattern: requisite-pattern extra-req1 extra-req2...
# 	|			|				|				|
# 	|			|				|				|___ more requisites
# 	|			|				|
# 	|			|				|___ ./src/what_matches.c -> ./src/%.c 
#	|			|
# 	|			|________ ./obj/what_matches.o -> ./obj/%.o 
# 	|
# 	|______./obj/file1.o ./obj/file2.o ./obj/file3.o ./obj/file4.o...   
#
# From GNU make manual:
# 	"The target-pattern and prereq-patterns say how to compute the prerequisites
# 	of each target. Each target is matched against the target-pattern to extract
# 	a part of the target name, called the stem. This stem is substituted into
# 	each of the prereq-patterns to make the prerequisite names (one from each
# 	prereq-pattern)."
#
# (1) The wildcard '%' in target-pattern is determined for each target when
# matching the pattern. (2) On the requisite-pattern side, the '%' resolves to
# whatever was determined in the target-pattern side. Thus:
#
#	OBJ_DIR is included in target-pattern because of (1), so it is not included
#	as part of '%' when sustituted in requisite-pattern side.
#
#	SRC_DIR is included in requisite pattern in order to have the complete
#	path and name of each requisite when '%' gets substituted in the requisite-
#	pattern side.
#
# The automatic variables:
#	$^ replaced by the name of ALL prerequisites
#	$< replaced by the name of FIRST prerequisites
#	$@ replaced by the name of the target
#
#	Using $< instead of $^ allows to correctly introduce more prerequisites
#	in a pattern rule.
#
# The expression:
# 	$(dir $@) 	equivalent to	$(@D)
# Resolves to the directory part of the target, excluding the file name.
# For just the name file:
# 	$(notdir $@) 	equivalent to	$(@F)
#
# Notice the headers as extra pre-requisites to force a recompiling if
# modified.
#
$(OBJECTS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "              --- Compiling objects to $(OBJ_DIR)*.o ---"
	mkdir -p $(@D)
	cc $(CC_FLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX42_INC)
	@echo
	@echo ----------------------------------------------------------------------
################### END OF PATTERN RULE TO COMPILE OBJECTS #####################
################################################################################

# Pattern rule to individually compile each BONUS object:
$(BONUS_OBJECTS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "              --- Compiling objects to $(OBJ_DIR)*.o ---"
	mkdir -p $(@D)
	cc $(CC_FLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX42_INC)
	@echo
	@echo ----------------------------------------------------------------------

# Library libft compilation
$(LIBFT_BIN):
ifeq ($(DEBUG), no)
	make --directory=$(LIBFT_DIR)
else
	make --directory=$(LIBFT_DIR) DEBUG=yes
endif

clean:
	@echo ----------------------------------------------------------------------
	@echo
	@echo "                          --- Cleaning ---"
	@echo
	rm -rf $(OBJ_DIR)
	make clean --directory=$(LIBFT_DIR)
	@echo
	@echo ----------------------------------------------------------------------

# Full cleaning rule: deletes objects files, all binary outputs, and directories
# Possible additions to the recipe:
# 	make fclean --directory=$(SOME_ANOTHER_LIBRARY_PATH)
#
fclean:clean
	@echo ----------------------------------------------------------------------
	@echo
	@echo "                          --- Fcleaning ---"
	@echo
	rm -rf $(BIN_DIR)
	make fclean --directory=$(LIBFT_DIR)
	@echo
	@echo ----------------------------------------------------------------------

# Rebuild rule: deletes objects files and all outputs, then compiles again
re: fclean all

$(DOXYFILE):
	@echo ----------------------------------------------------------------------
	@echo
	@echo "      --- Generating default Doxyfile configuration file ---"
	@echo
	doxygen -g $(DOXYFILE)
	@echo
	@echo "        --- Customizing Doxyfile configuration file ---"
	@echo
	sed -i '/^PROJECT_NAME.*=/s/^.*$$/PROJECT_NAME = "$(DOX_PROJECT_NAME)"/' $(DOXYFILE)
	sed -i '/^PROJECT_NUMBER.*=/s/^.*$$/PROJECT_NUMBER = $(DOX_PROJECT_NUMBER)/' $(DOXYFILE)
	sed -i '/^PROJECT_BRIEF.*=/s/^.*$$/PROJECT_BRIEF = "$(DOX_PROJECT_BRIEF)"/' $(DOXYFILE)
	sed -i '\|^OUTPUT_DIR.*=|s|^.*$$|OUTPUT_DIRECTORY = $(DOC_DIR)|' $(DOXYFILE)
	sed -i '\|^INPUT .*=|s|^.*$$|INPUT = $(DOX_INPUT)|' $(DOXYFILE)
	sed -i '/^RECURSIVE.*=/s/^.*$$/RECURSIVE = $(DOX_RECURSIVE)/' $(DOXYFILE)
	sed -i '/^OPTIMIZE_OUTPUT_FOR_C.*=/s/^.*$$/OPTIMIZE_OUTPUT_FOR_C = $(DOX_OPTIMIZE_OUTPUT_FOR_C)/' $(DOXYFILE)
	sed -i '\|^USE_MDFILE_AS_MAINPAGE.*=|s|^.*$$|USE_MDFILE_AS_MAINPAGE = $(DOX_MAIN_PAGE)|' $(DOXYFILE)
	sed -i '/^GENERATE_HTML .*=/s/^.*$$/GENERATE_HTML = $(DOX_GENERATE_HTML)/' $(DOXYFILE)
	sed -i '/^GENERATE_LATEX.*=/s/^.*$$/GENERATE_LATEX = $(DOX_GENERATE_LATEX)/' $(DOXYFILE)
	sed -i '/^GENERATE_RTF.*=/s/^.*$$/GENERATE_RTF = $(DOX_GENERATE_RTF)/' $(DOXYFILE)
	sed -i '/^GENERATE_MAN.*=/s/^.*$$/GENERATE_MAN = $(DOX_GENERATE_MAN)/' $(DOXYFILE)
	@echo
	@echo ----------------------------------------------------------------------

doc: $(DOXYFILE)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "      --- Generating project documentation ($(DOC_DIR)) ---"
	@echo
	doxygen $(DOXYFILE)
	@echo
	@echo ----------------------------------------------------------------------

docclean:
	@echo ----------------------------------------------------------------------
	@echo
	@echo "      --- Cleaning documentation directory and Doxyfile ---"
	@echo
	rm -rf $(DOC_DIR)
	rm $(DOXYFILE)
	@echo
	@echo ----------------------------------------------------------------------

tester: $(BIN_DIR)$(TESTER_NAME)

$(BIN_DIR)$(TESTER_NAME): $(TEST_DIR)$(TEST_SRC) $(BIN_DIR)$(NAME)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "        --- Compiling tester to $(BIN_DIR)$(TESTER_NAME) ---"
	@echo
	cc $(CC_FLAGS) $(TEST_DIR)$(TEST_SRC) $(BIN_DIR)$(NAME) -o $(BIN_DIR)$(TESTER_NAME) -I$(INC_DIR) -I$(TEST_DIR) 
	@echo
	@echo ----------------------------------------------------------------------

# Help rule: because I use to forget everything
help:
	@echo ----------------------------------------------------------------------
	@echo
	@echo "                          --- Ayuda ---"
	@echo
	@echo "    usar 'make', 'make all' o 'make $(BIN_DIR)$(NAME)' para compilar el proyecto base como: $(BIN_DIR)$(NAME)"
	@echo "    usar 'make bonus' para compilar el bonus (en caso de estar disponible) como $(BIN_DIR)$(BONUS_NAME)"
	@echo "    usar 'make tester' para compilar el programa de pruebas (en caso de estar disponible) como $(BIN_DIR)$(TESTER_NAME)"
	@echo "    usar 'make clean' para borrar los archivos .o y su directorio $(OBJ_DIR)"
	@echo "    usar 'make fclean para hacer 'clean' y ademas borrar todos los binarios y su directorio $(BIN_DIR)"
	@echo "    usar 'make re' para hacer 'fclean' y luego 'all'"
	@echo "    usar 'make ... DEBUG=yes' para hacer todas las compilaciones con estos flags adicionales:"
	@echo "          $(DEB_FLAGS)"
	@echo "    usar 'make help' para mostrar esta ayuda"
	@echo
	@echo ----------------------------------------------------------------------

# Phonies: this list of words are never to be interpreted as files but
# only as rule names
#
.PHONY: all clean fclean re tester help bonus $(NAME) doc docclean
