#-----------------------------------------
# VARIABLES
#-----------------------------------------
LIB      = GameRGR2
INC_DIR  = inc
SRC_DIR  = src
LIB_DIR  = lib
TEST_EXE = cy_valley
CURSES   = ncursesw
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
BUILD_DIR=build
OBJ2=$(addprefix $(BUILD_DIR)/, $(OBJ))

#-----------------------------------------
# REBUILD
#-----------------------------------------
all : $(TEST_EXE) 

#-----------------------------------------
# LIB RGR
#-----------------------------------------

$(LIB_DIR)/error.o : $(SRC_DIR)/error.c $(INC_DIR)/lib$(LIB).h $(INC_DIR)/local.h
	@gcc -c $< -o $@ -I$(INC_DIR) -fPIC

$(LIB_DIR)/utils.o : $(SRC_DIR)/utils.c $(INC_DIR)/lib$(LIB).h $(INC_DIR)/local.h 
	@gcc -c $< -o $@ -I$(INC_DIR) -fPIC

$(LIB_DIR)/lib$(LIB).o : $(SRC_DIR)/lib$(LIB).c $(INC_DIR)/lib$(LIB).h $(INC_DIR)/local.h
	@gcc -c $< -o $@ -I$(INC_DIR) -fPIC

$(LIB_DIR)/lib$(LIB).so : $(LIB_DIR)/lib$(LIB).o $(LIB_DIR)/utils.o $(LIB_DIR)/error.o
	@echo "Regenerating [$@]..."
	@gcc $^ -o $@ -shared -fPIC -I$(INC_DIR) -l$(CURSES)
	
#-----------------------------------------
# MAIN
#-----------------------------------------

$(BUILD_DIR)/%.o: %.c game.h $(BUILD_DIR)
	gcc -c $< -o $@

$(TEST_EXE) : $(OBJ2) $(LIB_DIR)/lib$(LIB).so
	@echo "Regenerating [$@]..."
	@gcc $^ -o $@ -I$(INC_DIR) -L$(LIB_DIR) -l$(CURSES) -l$(LIB) -lm

#-----------------------------------------
# RUN
#-----------------------------------------
run : $(TEST_EXE)
	LD_LIBRARY_PATH=./$(LIB_DIR) ./$(TEST_EXE) 2> err.log


#-----------------------------------------
# CLEAN / REBUILD
#-----------------------------------------
clean :
	@echo "Removing library..."
	@rm -f $(LIB_DIR)/lib$(LIB).so
	@rm -f $(LIB_DIR)/*.o
	@echo "Removing test executable..."
	@rm -f $(TEST_EXE)
	
rebuild : clean $(TEST_EXE)	

