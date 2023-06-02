CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -L. -linput -llog -lconvert

TARGET = datetime_app
SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

ifeq ($(OS),Windows_NT)
    # Windows (MinGW)
    TARGET := $(TARGET).exe
    LDFLAGS += -static
    RM = del /Q
    MKDIR = mkdir
else
    # Linux
    RM = rm -f
    MKDIR = mkdir -p
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) libinput.a liblog.a libconvert.a
	$(CC) $(LDFLAGS) -o $@ $^

libinput.a: $(OBJ_DIR)/input.o
	ar rcs $@ $^

liblog.a: $(OBJ_DIR)/log.o
	ar rcs $@ $^

libconvert.a: $(OBJ_DIR)/convert.o
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(OBJ_DIR) $(MKDIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) libinput.a liblog.a libconvert.a $(TARGET)
	$(RM) -r $(OBJ_DIR)
