CC=gcc
CFLAGS=-Wextra -Wall -Wno-long-long -pedantic-errors

JOELIXBLAS_TARGET_LIB=./lib/libjoelixblas.a
JOELIXBLAS_DIR=./joelixblas
JOELIXBLAS_INC=-I$(JOELIXBLAS_DIR)/include -I$(JOELIXBLAS_DIR)/private
JOELIXBLAS_SRC=$(wildcard $(JOELIXBLAS_DIR)/src/*.c)
JOELIXBLAS_OBJ=$(patsubst $(JOELIXBLAS_DIR)/src/%, ./build/obj/%, $(JOELIXBLAS_SRC:.c=.o)) 

all: $(JOELIXBLAS_TARGET_LIB)
	@true

.PHONY: clean
clean:
	    @-rm -f $(JOELIXBLAS_TARGET_LIB) $(JOELIXBLAS_OBJ)

$(JOELIXBLAS_TARGET_LIB): %: $(JOELIXBLAS_OBJ)
	@echo ""
	@echo "--------------------------"
	@echo "Linking $@ :"
	@echo "--------------------------"
	@mkdir -p $(dir $@)
	ar -cvq $@ $^

./build/obj/%.o : $(JOELIXBLAS_DIR)/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(JOELIXBLAS_INC) -c $< -o $@

