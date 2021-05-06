
CC = g++
CAR_OBJ = Car.o
MAIN_OBJ = main.o
TEST_OBJ = test.o
TEST_TARGET = test.exe
TARGET = program.exe
DEL = del
FLAGS = -std=c++11 -Wall
DOXY = doxygen
LOG_FILE = testlog.txt
DOC_DIR = docdir
KEEP = echo This is a .keep file for git > git.keep


all : doc $(TARGET) test

rebuild : clean all

$(TARGET) : $(MAIN_OBJ) $(CAR_OBJ)
	$(CC) $(FLAGS) $(MAIN_OBJ) $(CAR_OBJ) -o $(TARGET)

$(MAIN_OBJ) : main.cpp
	$(CC) $(FLAGS) -c main.cpp -o $(MAIN_OBJ)

$(CAR_OBJ) : Car.cpp
	$(CC) $(FLAGS) -c Car.cpp -o $(CAR_OBJ)

clean:
	$(DEL) $(CAR_OBJ)
	$(DEL) $(MAIN_OBJ)
	$(DEL) $(TARGET)
	$(DEL) $(LOG_FILE)
	$(DEL) $(TEST_TARGET)
	$(DEL) $(TEST_OBJ)
	$(DEL) /Q $(DOC_DIR)\html
	$(DEL) /Q $(DOC_DIR)\html\search

doc : Car.h
	$(DOXY)
	cd $(DOC_DIR) && $(KEEP)
	cd $(DOC_DIR)\html && $(KEEP)
	cd $(DOC_DIR)\html\search && $(KEEP)

deploy : test
	git add .
	git commit -m "Commit by makefile"
	git push -u origin main

$(TEST_TARGET) : $(TEST_OBJ) $(CAR_OBJ)
	$(CC) $(FLAGS) $(TEST_OBJ) $(CAR_OBJ) -o $(TEST_TARGET)

build_test : $(TEST_OBJ) $(CAR_OBJ)
	$(CC) $(FLAGS) $(TEST_OBJ) $(CAR_OBJ) -o $(TEST_TARGET)

$(TEST_OBJ) : test.cpp
	$(CC) $(FLAGS) -c test.cpp -o $(TEST_OBJ)

test : $(TEST_TARGET)
	$(TEST_TARGET) >> $(LOG_FILE) && $(TEST_TARGET)

.PHONY : all doc clean test build_test rebuild
