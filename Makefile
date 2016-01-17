CC=g++
CCFLAGS=-std=c++11 -Wall -Werror
RM=rm -fr
MAIN_SRCS=main.cpp
MAIN_OBJS=$(subst .cpp,.o,$(MAIN_SRCS))
MAIN=$(subst .cpp,,$(MAIN_SRCS))
TESTS_SRCS=unit_tests.cpp
TESTS_OBJS=$(subst .cpp,.o,$(TESTS_SRCS))
TESTS=$(subst .cpp,,$(TESTS_SRCS))
LIB_SRCS=buzzfizz.cpp
LIB_OBJS=$(subst .cpp,.o,$(LIB_SRCS))
EXEC=$(MAIN) $(TESTS)

.PHONY: clean

all: $(TESTS) $(MAIN)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

$(TESTS): $(TESTS).o $(LIB_OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

$(MAIN): $(MAIN).o $(LIB_OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	$(RM) *.o $(EXEC)

