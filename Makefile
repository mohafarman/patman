##
# Patman
#
# @file
# @version 0.1

EXECUTABLE = patman

CC = gcc
CFLAGS= -g3 -O0 -Wall -Werror -Wextra -pedantic -std=c11
LDLIBS = -lm -lpthread -ldl `pkg-config --libs raylib`
COMPILE = $(CC) $(CFLAGS) $(LDLIBS)

BUILD_DIR := ./bin
SRC_DIR := ./src
HDR_DIR := ./include

SRCS := $(shell find $(SRC_DIR) -name '*.c')
HDRS := $(shell find $(HDR_DIR) -name '*.h')
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

dir_guard=@mkdir -p $(@D)

default: $(BUILD_DIR)/$(EXECUTABLE)

print:
	@echo $(SRCS)
	@echo $(OBJS)

run:
	$(BUILD_DIR)/patman

dir:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJS)
	$(COMPILE) $^ -o $@

# Define a pattern rule that compiles every .c file into a .o file
$(BUILD_DIR)/%.o : ./src/%.c $(HDRS)
	$(dir_guard)
	$(COMPILE) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)/$(EXECUTABLE) $(OBJS) $(BUILD_DIR)/*~


# end
