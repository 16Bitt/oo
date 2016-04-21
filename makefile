SOURCES	= $(patsubst %.c,%.o,$(wildcard *.c))
LCC_PATH= $(HOME)/src/libcc
CFLAGS	= -g -I$(LCC_PATH) -Wall -Werror
CC	= gcc
TARGET	= oo
TARGET_ARGS	= 
TEST_FILE	= test.oo

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LCC_PATH)/libcc.a -o $(TARGET)

run: all
	cat $(TEST_FILE) | ./$(TARGET) $(TARGET_ARGS)

clean:
	-rm $(SOURCES) $(TARGET)
