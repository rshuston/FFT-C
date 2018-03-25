include ../Makefile.inc

LIB = libcheckext.a

SRC = checkext.c
OBJS = $(SRC:.c=.o)
TSTBL_OBJS = $(SRC:.c=.tstbl.o)

TEST_SRC = $(SRC:.c=_test.c)
TEST_OBJS = $(TEST_SRC:.c=.o)

TEST_EXES =  $(TEST_SRC:.c=.exe)

.PHONY: default force tests runtests runmemtests clean clobber help

default: $(LIB)

force:

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

tests: force
	@$(MAKE) $(TEST_EXES)

runtests: tests
	@for t in $(TEST_EXES); do (./$$t); done

runmemtests: tests
	@for t in $(TEST_EXES); do ($(VALGRIND) ./$$t); done

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TSTBL_OBJS) $(TEST_OBJS) $(TEST_OBJS:.o=.d)

clobber:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TSTBL_OBJS) $(TEST_OBJS) $(TEST_OBJS:.o=.d) $(TEST_EXES) $(LIB)

help:
	@echo "default: $(LIB)"
	@echo "$(LIB): make the library archive"
	@for e in $(TEST_EXES); do (echo "$$e: make the $$e test runner" ); done
	@echo "tests: make the library test runner(s): $(TEST_EXES)"
	@echo "runtests: run the library test runner(s), making them if needed"
	@echo "runmemtests: run the library test runner(s), checking for leaks"
	@echo "clean: delete object files and debug files"
	@echo "clobber: delete object files, debug files, exe files, and lib files"

-include $(wildcard *d)
