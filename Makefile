CC=gcc
CFLAGS=-Wextra -Wall -Wno-long-long -pedantic-errors

JOELIXBLAS_TARGET_LIB=./lib/libjoelixblas.a
JOELIXBLAS_DIR=./joelixblas
JOELIXBLAS_INC=-I$(JOELIXBLAS_DIR)/include -I$(JOELIXBLAS_DIR)/private
JOELIXBLAS_SRC=$(wildcard $(JOELIXBLAS_DIR)/src/*.c)
JOELIXBLAS_OBJ=$(patsubst $(JOELIXBLAS_DIR)/src/%, ./build/obj/%, $(JOELIXBLAS_SRC:.c=.o)) 

JOELIXBLAS_T_TARGET_LIB=./lib/libjoelixblas_t.a
JOELIXBLAS_T_DIR=./joelixblas
JOELIXBLAS_T_INC=-I$(JOELIXBLAS_T_DIR)/include -I$(JOELIXBLAS_T_DIR)/private
JOELIXBLAS_T_SRC=$(wildcard $(JOELIXBLAS_T_DIR)/src/*.c)
JOELIXBLAS_T_OBJ=$(patsubst $(JOELIXBLAS_T_DIR)/src/%, ./build/obj_t/%, $(JOELIXBLAS_T_SRC:.c=.o))
JOELIXBLAS_T_LIBS="-fopenmp"

all: $(JOELIXBLAS_TARGET_LIB) $(JOELIXBLAS_T_TARGET_LIB)
	@true

.PHONY: clean
clean:
	    @-rm -f $(JOELIXBLAS_TARGET_LIB) $(JOELIXBLAS_OBJ) $(JOELIXBLAS_T_TARGET_LIB) $(JOELIXBLAS_T_OBJ)

$(JOELIXBLAS_TARGET_LIB): %: $(JOELIXBLAS_OBJ)
	@echo ""
	@echo "--------------------------"
	@echo "Linking $@ :"
	@echo "--------------------------"
	@mkdir -p $(dir $@)
	ar -cvq $@ $^

$(JOELIXBLAS_T_TARGET_LIB): %: $(JOELIXBLAS_T_OBJ)
	@echo ""
	@echo "--------------------------"
	@echo "Linking $@ :"
	@echo "--------------------------"
	@mkdir -p $(dir $@)
	ar -cvq $@ $^

./build/obj/%.o : $(JOELIXBLAS_DIR)/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(JOELIXBLAS_INC) -c $< -o $@

./build/obj_t/%.o : $(JOELIXBLAS_T_DIR)/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -D__JOELIX_THREADED_VERSION__=1 $(JOELIXBLAS_T_INC) -c $< -o $@ $(JOELIXBLAS_T_LIBS)
