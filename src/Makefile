# FLAGS
CC =g++ -std=c++17 
MAX_ERRORS =10
CFLAGS =-Werror -Wextra -Wall -pedantic -fmax-errors=$(MAX_ERRORS) -O3
TEST_FLAGS =-lgtest -pthread
GCOV_FLAGS =--coverage -lgcov -fprofile-arcs -ftest-coverage

# DIRS
TEST_DIR =tests
REPORT_DIR =report

# FILES
SRC =*.cpp
OBJ =*.o
TEST_SRC =$(TEST_DIR)/*.cpp
TEST_OBJ =$(TEST_DIR)/*.o
TEST_OUT =test.out
STATIC_LIB =s21_matrix_oop.a
STATIC_LIB_GCOV =libS21_matrix_oop_gcov.a

#-----------------------------------------------------------------------------

ifeq ($(shell uname -s), Linux)
	CMD_LEAKS =@valgrind --tool=memcheck --track-fds=yes --trace-children=yes \
	--track-origins=yes --leak-check=full --show-leak-kinds=all -s \
	./$(TEST_DIR)/$(TEST_OUT)
	OPEN =xdg-open
else 
	CMD_LEAKS =@leaks --atExit -- $<
	OPEN =open
endif

#-----------------------------------------------------------------------------

.PHONY: all
all: clean $(STATIC_LIB) gcov_report

#-----------------------------------------------------------------------------

$(STATIC_LIB): $(SRC)
	@$(CC) $(CFLAGS) -c $<
	@ar rcs $@ $(OBJ)
	@ranlib $@
	@rm $(OBJ)

#-----------------------------------------------------------------------------

.PHONY: test
test: $(TEST_OUT) 
	@./$(TEST_DIR)/$<
	@rm $(TEST_OBJ)

$(TEST_OUT): $(TEST_OBJ) $(STATIC_LIB_GCOV)
	@$(CC) $(CFLAGS) $< -L. -lS21_matrix_oop_gcov -o $(TEST_DIR)/$@ $(TEST_FLAGS)

$(TEST_OBJ): $(TEST_SRC)
	@$(CC) -g $(CFLAGS) -c $^ 
	@mv $(OBJ) $(TEST_DIR)

#-----------------------------------------------------------------------------

$(STATIC_LIB_GCOV): $(OBJ)
	@ar rcs $@ $<
	@ranlib $@
	@rm $<

$(OBJ): $(SRC)
	@$(CC) $(CFLAGS) -g -c $<

.PHONY: gcov_report
gcov_report: $(SRC) $(TEST_SRC)
	@mkdir -p ./$(REPORT_DIR)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $^ -o $(REPORT_DIR)/$(TEST_OUT) $(TEST_FLAGS) 
	@./$(REPORT_DIR)/$(TEST_OUT)
	@lcov -t "GcovReport" -c -d ./ -o ./$(REPORT_DIR)/coverage.info
	@genhtml ./$(REPORT_DIR)/coverage.info --output-directory ./$(REPORT_DIR)/
	@$(OPEN) ./$(REPORT_DIR)/$(shell pwd)/index.html

#-----------------------------------------------------------------------------

.PHONY: gstyle_test
gstyle_test:
	@cp ../materials/linters/.clang-format .
	clang-format --style=Google -n *.cpp *.h $(TEST_DIR)/*.cpp
	@rm .clang-format

.PHONY: gstyle_format
gstyle_format:
	@cp ../materials/linters/.clang-format .
	clang-format --style=Google -i *.cpp *.h $(TEST_DIR)/*.cpp
	@rm .clang-format

.PHONY: check_leaks
check_leaks: test
	$(CMD_LEAKS)

.PHONY: cppcheck
cppcheck: $(SRC)
	cppcheck --enable=all --force --suppress=missingIncludeSystem --language=c++ $< $(TEST_DIR)/$<

.PHONY: clean
clean:
	@rm -f *.a .*swp *.o
	@rm -f ./$(TEST_DIR)/*.o $(TEST_DIR)/*.out 
	@rm -rf ./$(REPORT_DIR)
