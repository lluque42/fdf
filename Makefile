# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 11:23:07 by lluque            #+#    #+#              #
#    Updated: 2024/07/21 11:45:33 by lluque           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#
# Directories for source code, tester and headers (permanent), and for
# object files and binary output (volatile).
# (all directories are relative to repository's root directory)
#
# Common directories
BASE_BIN_DIR = ./bin/
OBJ_DIR = ./obj/

# Project's mandatory version directories
SRC_DIR = ./src/mandatory/
INC_DIR = ./include/mandatory/
BIN_DIR = $(BASE_BIN_DIR)mandatory/

# Project's bonus version directories
BONUS_SRC_DIR = ./src/bonus/
BONUS_INC_DIR = ./include/bonus/
BONUS_BIN_DIR = $(BASE_BIN_DIR)bonus/

# Project's optional tester directories
TEST_DIR = ./test/
TEST_INC_DIR = ./test/
TEST_BIN_DIR = $(BASE_BIN_DIR)tester/

# Directories for external libraries to be built using their own building tools
LIBFT_DIR = ./lib/libft/
LIBFT_BIN_DIR = $(LIBFT_DIR)bin/
LIBFT_INC = $(LIBFT_DIR)include/

MLX42_DIR = ./lib/MLX42/
MLX42_BIN_DIR = $(MLX42_DIR)build/
MLX42_INC = $(MLX42_DIR)include/MLX42/

################################################################################
#
# Binary names, including other pre-compiled external libraries passed as
# flags when linking
#
# Resulting binary name for mandatory program version (to be placed in BIN_DIR)
NAME = fdf

# Resulting binary name for bonus program version(to be placed in BONUS_BIN_DIR)
BONUS_NAME = $(NAME)

# Resulting tester name (to be placed in BIN_DIR)
TESTER_NAME = tester

# Library libft binary
LIBFT_BIN = $(LIBFT_BIN_DIR)libft.a

# Library MLX42 binary
MLX42_BIN = $(MLX42_BIN_DIR)libmlx42.a

# Additional external (already-compiled) libraries for linking to the
# project's binaries (mandatory, bonus and tester).
# 
# GLFW: API for OpenGL needed by MLX42
# libdl: Dynamic loader (linking) library needed by MLX42
# pthread: POSIX thread library needed by MLX42
# libm: math library
EXT_LIBS = -ldl -lglfw -pthread -lm

################################################################################
#
# Variables for adding debug capabilities, only used when compiling object for:
# 		Project's mandatory version
# 		Project's bonus version
# 		Project's tester
#		Library libft (only applies if using a version that supports this)
#
# Definition, for clarity, of DEBUG variable. Its value is supposed to be
# asigned when a DEBUG=xxx is passed to make from the command line
# (e.g. "$ make DEBUG=g bonus")
DEBUG =

# Definition, for clarity, of the argument that will be passed to libft's make
# when building it. Its purpose is to propagate the same DEBUG=xxx value passed
# to make from the command line when building this project.
# Its definite value will be set in later conditional statements and will
# depends exclusively on $(DEBUG). It will remain empty if no DEBUG=xxx is
# passed to make when compiling this project.
LIBFT_MAKE_DEBUG_ARGS =

# Definition, for clarity, of the variable that holds the actual debug flags
# to be used when compiling this project's object files.
# Its definite value will be set in later conditional statements and will
# depends exclusively on $(DEBUG). It will remain empty if no DEBUG=xxx is
# passed to make when compiling this project.
DEB_FLAGS =

# Setting of both DEB_FLAGS and LIBFT_MAKE_DEBUG_ARGS values as correspond to
# the value of $(DEBUG) (no value by default; or the external value if passed
# to make as "$ make DEBUG=xxx...". If received an unforeseen value for DEBUG,
# the variables remain empty, thus having no effect.
#
# Options to consider in the future:
# 	-fsanitize=undefined -fsanitize=address -fsanitize=leak
ifeq ($(DEBUG), g)
	DEB_FLAGS += -g
	LIBFT_MAKE_DEBUG_ARGS += DEBUG=$(DEBUG)
else ifeq ($(DEBUG), addsan)
	DEB_FLAGS += -g -fsanitize=address
	LIBFT_MAKE_DEBUG_ARGS += DEBUG=$(DEBUG)
endif

# Definition, for clarity, of MAKE_DEBUG_LVL intended to provide a building-time
# mechanism to pass data which will affect the built program's behavior. It is
# intended to be used to pass an integer value which can be used by the source
# code to report more, less or no debug messages during the program's runtime.
#
# From the source code's perspective, a building using "make MAKE_DEBUG_LVL=5"
# is the same as having a "#define MAKE_DEBUG_LVL 5" in a global scope. It is
# up to the programmer to use it or not.
#
# If a value is passed to make, the DEB_FLAGS and LIBFT_MAKE_DEBUG_ARGS will
# be modified accordingly both to have an effect on this project and the
# libft building.
MAKE_DEBUG_LVL =

# Condition to modify DEB_FLAGS and LIBFT_MAKE_DEBUG_ARGS if a value for
# MAKE_DEBUG_LVL is passed to make from the command line when building
# this project.
ifdef MAKE_DEBUG_LVL
	DEB_FLAGS += -D MAKE_DEBUG_LVL=$(MAKE_DEBUG_LVL)
	LIBFT_MAKE_DEBUG_ARGS += MAKE_DEBUG_LVL=$(MAKE_DEBUG_LVL)
endif

################################################################################
#
# Choice for compiler and standard flags to be used for mandatory, bonus and
# tester binaries.
# NOTE: DEB_FLAGS is empty if no debugging arguments are passed to make
#
# Compiler to use
CC = cc

# Compiler flags
CC_FLAGS = -Wall -Werror -Wextra

################################################################################
#
# The source and header files for mandatory, bonus and tester
#
# List of mandatory version header file names
# NOTE: Only to be used to force recompiling if modified
INCLUDES = $(INC_DIR)drawing.h \
		   $(INC_DIR)fdf_features.h \
		   $(INC_DIR)fdf.h \
		   $(INC_DIR)lin_alg.h\
		   $(INC_DIR)main_utils.h \
		   $(INC_DIR)tesselator.h \
		   $(INC_DIR)window.h

# List of source code file names with path relative to SRC_DIR
SOURCES = fdf_main.c \
		  main_utils/fdf_filename_valid.c \
		  main_utils/fdf_args_valid.c \
		  main_utils/fdf_print_instructions.c \
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
		  lin_alg/ft_mx_flipc.c \
		  lin_alg/ft_mx_set_col.c \
		  lin_alg/ft_vx_xproduct.c \
		  lin_alg/ft_vx_create.c \
		  lin_alg/ft_vx_substract.c \
		  lin_alg/ft_vx_dproduct.c \
		  tesselator/fdf_get_vertex_mx.c \
		  tesselator/fdf_get_edge.c \
		  tesselator/fdf_set_diag_edge_validity.c \
		  tesselator/fdf_create_rotmx.c \
		  tesselator/fdf_tesselate_map.c \
		  tesselator/fdf_create_object.c \
		  tesselator/fdf_destroy_object.c \
		  tesselator/fdf_create_ortoproj_mx.c \
		  tesselator/fdf_create_transl_mx.c \
		  tesselator/fdf_create_scale_mx.c \
		  tesselator/fdf_print_edges.c \
		  tesselator/fdf_create_plane.c \
		  tesselator/fdf_point_is_in_plane.c \
		  tesselator/fdf_create_3drect.c \
		  tesselator/fdf_getz_3drect.c \
		  tesselator/fdf_get_vertex_mx_sph.c \
		  tesselator/fdf_get_vertex_mx_cyl.c \
		  tesselator/fdf_create_nv.c \
		  tesselator/fdf_destroy_nv.c \
		  drawing/fdf_drw_edges.c \
		  drawing/fdf_get_autofit_transf_par.c \
		  drawing/fdf_get_vertex_min_max.c \
		  drawing/fdf_render.c \
		  window/fdf_keyhook.c \
		  window/fdf_closehook.c \
		  window/fdf_generichook.c \
		  window/fdf_start_gui.c \
		  window/fdf_resizehook.c \
		  window/fdf_create_wlayout.c \
		  window/fdf_destroy_wlayout.c \
		  window/fdf_rotation_keys_down.c \
		  window/fdf_translation_keys_down.c \
		  window/fdf_zoom_keys_down.c \
		  fdf/fdf_create_fdf.c \
		  fdf/fdf_destroy_fdf.c \
		  features/fdf_exit_program.c \
		  features/fdf_window_resize.c \
		  features/fdf_rotate_step.c \
		  features/fdf_translate_step.c \
		  features/fdf_scale_step.c \
		  features/fdf_toggle_autofit.c \
		  features/fdf_toggle_tesselation.c \
		  features/fdf_toggle_drw_hidden.c \
		  features/fdf_toggle_drw_diags.c


# List of bonus version header file names
# NOTE: Only to be used to force recompiling if modified
BONUS_INCLUDES = $(BONUS_INC_DIR)placeholder_bonus.h

# List of BONUS source code file names with path relative to BONUS_SRC_DIR
BONUS_SOURCES = placeholder_bonus.c

# List of tester header file names
# NOTE: Only to be used to force recompiling if modified
TESTER_INCLUDES = $(TESTER_INC_DIR)placeholder_tester.h

# List of tester source code file names with path relative to TEST_DIR
TESTER_SOURCES = tester.c

################################################################################
#
# Object files names for mandatory, bonus and tester
#
# Auto generated list of object file names from respective source directory by:
# replacing the file extension .c for .o; and adding the $(OBJ_DIR) to the
# resulting list of file names (thus maintaining the directory structure of the
# code files.
# (here the path is relative to repository's root)
#
# For mandatory version objects
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)

# For bonus version objects
BONUS_OBJECTS = $(BONUS_SOURCES:%.c=$(OBJ_DIR)%.o)

# For tester version objects
TESTER_OBJECTS = $(TESTER_SOURCES:%.c=$(OBJ_DIR)%.o)

################################################################################
############### VARIABLES FOR DOXYGEN DOCUMENTATION GENERATION #################

# Doxyfile name, to be generated and edited in repository root directory
DOXYFILE = Doxyfile
DOC_DIR = ./doc/

# Project name for documentation purposes
DOX_PROJECT_NAME = Fdf

# Project brief description (one line)
DOX_PROJECT_BRIEF = Fdf project for Campus 42

# Content for documentation main page (detailed description there)
DOX_MAIN_PAGE = ./README.md

# Version of the documentation (date for now)
DOX_PROJECT_NUMBER = $(shell date +%Y-%m-%d)

# Location with files to extract documentation from (.h)
# Look for more files in subdirectories
#
DOX_INPUT = $(INC_DIR) $(DOX_MAIN_PAGE)
DOX_RECURSIVE = YES

# Optimization for languages
DOX_OPTIMIZE_OUTPUT_FOR_C = YES

# Documentation formats to generate
DOX_GENERATE_HTML = YES
DOX_GENERATE_LATEX = NO
DOX_GENERATE_RTF = NO
DOX_GENERATE_MAN = NO

################ VARIABLES FOR DOXYGEN DOCUMENTATION GENERATION ################
################################################################################

################## VARIABLES FOR ANSI ESCAPE CODES FOR COLORS ##################
################################################################################

# BASIC COLOR CODES
RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
PURPLE = \033[0;35m

# BOLD COLOR CODES
BRED = \033[1;31m
BGREEN = \033[1;32m
BCYAN = \033[1;36m
BPURPLE = \033[1;35m

# No Color (resets previously set color)
NC=\033[0m

################## VARIABLES FOR ANSI ESCAPE CODES FOR COLORS ##################
################################################################################

################################################################################
############################# FINALLY THE ######################################
################################ RULES #########################################
################################################################################

# Default rule
all: $(BIN_DIR)$(NAME)

############################# For mandatory version ############################

# Rule for NAME as phony
# (i.e. to allow 'make my_project' instead of 'make [some_path]my_project')
$(NAME): $(BIN_DIR)$(NAME)

# Rule (pattern rule) to individually (no relink) compile objects.
# See comments at the end of Makefile for details on the syntax.
$(OBJECTS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "              --- ${PURPLE}Compiling objects to ${BPURPLE}$(OBJ_DIR)*.o${NC} ---"
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(DEB_FLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX42_INC)
	@echo
	@echo ----------------------------------------------------------------------

# Rule to link the program
$(BIN_DIR)$(NAME): $(OBJECTS) $(LIBFT_BIN) $(MLX42_BIN)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "          --- ${PURPLE}Linking the program to ${BPURPLE}$(BIN_DIR)$(NAME)${NC} ---"
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(DEB_FLAGS) $(OBJECTS) $(LIBFT_BIN) $(MLX42_BIN) $(EXT_LIBS) -o $(BIN_DIR)$(NAME) -I$(INC_DIR) -I$(LIBFT_INC)
	@echo
	@echo ----------------------------------------------------------------------

############################### For bonus version ##############################
# Rule for bonus as phony
bonus: $(BONUS_BIN_DIR)$(BONUS_NAME)

# Rule (pattern rule) to individually (no relink) compile BONUS objects
$(BONUS_OBJECTS): $(OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_INCLUDES)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "              --- ${PURPLE}Compiling bonus objects to ${BPURPLE}$(OBJ_DIR)*.o${NC} ---"
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(DEB_FLAGS) -c $< -o $@ -I$(BONUS_INC_DIR) -I$(LIBFT_INC) -I$(MLX42_INC)
	@echo
	@echo ----------------------------------------------------------------------

# Rule to link the bonus
$(BONUS_BIN_DIR)$(BONUS_NAME): $(BONUS_OBJECTS) $(LIBFT_BIN) $(MLX42_BIN)
	@echo "          --- ${PURPLE}Linking the bonus program to ${BPURPLE}$(BIN_DIR)$(BONUS_NAME)${NC} ---"
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(DEB_FLAGS) $(BONUS_OBJECTS) $(LIBFT_BIN) $(MLX42_BIN) $(EXT_LIBS) -o $(BONUS_BIN_DIR)$(BONUS_NAME) -I$(BONUS_INC_DIR) -I$(LIBFT_INC)
	@echo
	@echo ----------------------------------------------------------------------

############################### For test program ###############################
# Rule for tester as phony
tester: $(BASE_BIN_DIR)$(TESTER_NAME)

# Rule (pattern rule) to individually (no relink) compile TESTER objects
$(TESTER_OBJECTS): $(OBJ_DIR)%.o: $(TEST_DIR)%.c $(INCLUDES)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "              --- ${PURPLE}Compiling tester objects to ${BPURPLE}$(OBJ_DIR)*.o${NC} ---"
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(DEB_FLAGS) -c $< -o $@ -I$(TESTER_INCLUDES_DIR) -I$(LIBFT_INC) -I$(MLX42_INC)
	@echo
	@echo ----------------------------------------------------------------------

# Rule to link the test program binary.
$(BASE_BIN_DIR)$(TESTER_NAME): $(TESTER_OBJECTS) $(LIBFT_BIN) $(MLX42_BIN)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "          --- ${PURPLE}Linking the tester program to ${BPURPLE}$(BIN_DIR)$(TESTER_NAME)${NC} ---"
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(DEB_FLAGS) $(TESTER_OBJECTS) $(LIBFT_BIN) $(MLX42_BIN) $(EXT_LIBS) -o $(BASE_BIN_DIR)$(TESTER_NAME) -I$(INC_DIR) -I$(LIBFT_INC)
	@echo
	@echo ----------------------------------------------------------------------

########################### For external libraries  ############################
# Library libft compilation
$(LIBFT_BIN):
	@echo ----------------------------------------------------------------------
	@echo
	@echo "              --- ${PURPLE}Compiling libft library to ${BPURPLE}$(LIBFT_BIN)${NC} ---"
	make --directory=$(LIBFT_DIR) $(LIBFT_MAKE_DEBUG_ARGS)
	@echo
	@echo ----------------------------------------------------------------------

# Library MLX42 compilation
$(MLX42_BIN):
	@echo ----------------------------------------------------------------------
	@echo
	@echo "              --- ${PURPLE}Compiling MLX42 library to ${BPURPLE}$(MLX42_BIN)${NC} ---"
	cmake -S $(MLX42_DIR) -B $(MLX42_BIN_DIR)
	cmake --build $(MLX42_BIN_DIR) -j4
	@echo
	@echo ----------------------------------------------------------------------

################### For standard remaining mandatory rules #####################
# Cleaning rule: deletes object files and directory.
# Possible additions to the recipe:
# 	rm -rf $(BONUS_OBJ_DIR)
# 	make clean --directory=$(SOME_LIBRARY_PATH)
#
clean:
	@echo ----------------------------------------------------------------------
	@echo
	@echo "                          --- ${PURPLE}Cleaning (at $(NAME))${NC} ---"
	@echo
	rm -rf $(OBJ_DIR)
	make clean --directory=$(LIBFT_DIR)
	@echo
	@echo ----------------------------------------------------------------------

# Full cleaning rule: deletes objects files, all binary outputs, and directories
# Possible additions to the recipe:
# 	make fclean --directory=$(SOME_ANOTHER_LIBRARY_PATH)
#
# TODO TODO TODO ver si cmake de MLX42 tiene un clean o fclean
fclean:clean
	@echo ----------------------------------------------------------------------
	@echo
	@echo "                          --- ${PURPLE}Fcleaning (at $(NAME))${NC} ---"
	@echo
	rm -rf $(BASE_BIN_DIR)
	rm -rf $(MLX42_BIN_DIR)
	make fclean --directory=$(LIBFT_DIR)
	@echo
	@echo
	@echo ----------------------------------------------------------------------

# Rebuild rule: deletes objects files and all outputs, then compiles again
re: fclean all

######################### For my own make help rule ############################
# Help rule: because I use to forget everything
help:
	@echo ----------------------------------------------------------------------
	@echo
	@echo "                          --- ${PURPLE}Ayuda${NC} ---"
	@echo
	@echo "    usar '${BGREEN}make${NC}', '${GREEN}make ${BGREEN}all${NC}' o '${GREEN}make ${BGREEN}$(BIN_DIR)$(NAME)${NC}' para compilar el proyecto base como: ${CYAN}$(BIN_DIR)$(NAME)${NC}"
	@echo "    usar '${GREEN}make ${BGREEN}bonus${NC}' para compilar el proyecto en version bonus (en caso de estar disponible) como ${CYAN}$(BIN_DIR)$(BONUS_NAME)${NC}"
	@echo "    usar '${GREEN}make ${BGREEN}tester${NC}' para compilar el programa de pruebas (en caso de estar disponible) como ${CYAN}$(BIN_DIR)$(TESTER_NAME)${NC}"
	@echo "    usar '${GREEN}make ${BGREEN}clean${NC}' para borrar los archivos .o y su directorio ${CYAN}$(OBJ_DIR)${NC}"
	@echo "    usar '${GREEN}make ${BGREEN}fclean${NC}' para hacer '${CYAN}clean${NC}' y ademas borrar todos los binarios y su directorio ${CYAN}$(BIN_DIR)${NC}"
	@echo "    usar '${GREEN}make ${BGREEN}re${NC}' para hacer '${CYAN}fclean${NC}' y luego '${CYAN}all${NC}'"
	@echo "    usar '${GREEN}make ... ${BGREEN}DEBUG=...${NC}' para hacer todas las compilaciones con estos flags adicionales:"
	@echo "        ${CYAN}DEBUG=${BCYAN}g${NC}      (e.g. para debugging con lldb)    ---> ${CYAN}-g${NC}"
	@echo "        ${CYAN}DEBUG=${BCYAN}addsan${NC} (i.e. para reportar memory leaks) ---> ${CYAN}-g -fsanitize=address${NC}"
	@echo "        (cualquier otro valor es ignorado)"
	@echo "    usar '${GREEN}make ... ${BGREEN}MAKE_DEBUG_LVL=...${NC}' para compilar el código con un ${CYAN}#define MAKE_DEBUG_LVL ...${NC}"
	@echo "        Se recomienda pasar un valor entero que sería usado en el código como MAKE_DEBUG_LVL"
	@echo "        para imprimir diferentes niveles de mensajes de debugging."
	@echo "    usar '${GREEN}make ${BGREEN}help${NC}' para mostrar esta ayuda"
	@echo
	@echo ----------------------------------------------------------------------

################## For my own documentation generation rules  ##################
# Rule to create and customize Doxygen configuration file which will define
# how to generate the project's documentation from comments in the code when
# using 'make doc'.
$(DOXYFILE):
	@echo ----------------------------------------------------------------------
	@echo
	@echo "      --- ${PURPLE}Generating default Doxygen configuration file: ${BPURPLE}./$(DOXYFILE)${NC} ---"
	@echo
	doxygen -g $(DOXYFILE)
	@echo
	@echo "        --- ${PURPLE}Customizing Doxygen configuration file: ${BPURPLE}./$(DOXYFILE)${NC} ---"
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

# Rule to generate the project's documentation from commented code.
doc: $(DOXYFILE)
	@echo ----------------------------------------------------------------------
	@echo
	@echo "      --- ${PURPLE}Generating project documentation in ${BPURPLE}$(DOC_DIR)${NC} ---"
	@echo
	doxygen $(DOXYFILE)
	@echo
	@echo ----------------------------------------------------------------------

# Rule to delete the project's documentation and Doxygen's configuration file.            NEWWWWWW -f para rm doxyfile
docclean:
	@echo ----------------------------------------------------------------------
	@echo
	@echo "      --- ${PURPLE}Cleaning documentation directory and Doxyfile${NC} ---"
	@echo
	rm -rf $(DOC_DIR)
	rm -f $(DOXYFILE)
	@echo
	@echo ----------------------------------------------------------------------

# Phonies: this list of words are never to be interpreted as files but
# only as rule names. 
# NOTE: Keywords test, bonus and the program's name are set as phony to ease
# make's use while keeping the resulting binaries in bin/. Simply put: this
# allows the user to execute "make my_project" instead of "make bin/my_project.
.PHONY: all clean fclean re tester help bonus $(NAME) doc docclean

############################### REMEMBER #######################################
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
