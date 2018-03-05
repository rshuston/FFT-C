include Makefile.inc

EXE = runner.exe

APP_LIB = app.a

APP_SRC = app.c
APP_OBJS = $(APP_SRC:.c=.o)

APP_TEST_SRC = $(APP_SRC:.c=_test.c)
APP_TEST_OBJS =  $(APP_TEST_SRC:.c=.o)
APP_TEST_EXES =  $(APP_TEST_SRC:.c=.exe)

COMPONENT_DIRS = libcheckext libbithacks libcomplex libfft
COMPONENT_LIBS = $(foreach dir, $(COMPONENT_DIRS), $(dir)/$(dir).a)

CFLAGS += $(addprefix -I, $(COMPONENT_DIRS))

.PHONY: default force all tests alltests runtests runalltests runmemtests runallmemtests clean clobber

default: $(EXE)

force:

$(EXE): main.o $(APP_LIB) $(COMPONENT_LIBS)
	$(LD) $^ $(LDFLAGS) -o $(EXE)

$(APP_LIB): $(APP_OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(COMPONENT_LIBS): force
	$(MAKE) -C $(dir $@) $(notdir $@)

app_test.exe: app_test.o $(APP_LIB) $(COMPONENT_LIBS)
	$(LD) $^ $(LDFLAGS) $(TEST_LDFLAGS) -o $@

all: $(EXE) alltests

tests: force
	@$(MAKE) $(APP_TEST_EXES)

alltests: tests
	@for d in $(COMPONENT_DIRS); do (cd $$d; $(MAKE) tests ); done

runtests: tests
	@for t in $(APP_TEST_EXES); do (./$$t); done

runalltests: runtests
	@for d in $(COMPONENT_DIRS); do (cd $$d; $(MAKE) runtests ); done

runmemtests: tests
	@for t in $(APP_TEST_EXES); do ($(VALGRIND) ./$$t); done

runallmemtests: runmemtests
	@for d in $(COMPONENT_DIRS); do (cd $$d; $(MAKE) runmemtests ); done

clean:
	rm -f main.o main.d $(APP_OBJS) $(APP_OBJS:.o=.d) $(APP_TEST_OBJS) $(APP_TEST_OBJS:.o=.d)
	rm -f foo.bar
	@for d in $(COMPONENT_DIRS); do (cd $$d; $(MAKE) clean ); done

clobber:
	rm -f main.o main.d $(APP_OBJS) $(APP_OBJS:.o=.d) $(APP_TEST_OBJS) $(APP_TEST_OBJS:.o=.d)
	rm -f foo.bar
	rm -f $(APP_LIB) $(EXE) $(APP_TEST_EXES)
	@for d in $(COMPONENT_DIRS); do (cd $$d; $(MAKE) clobber ); done

-include $(wildcard *.d)
