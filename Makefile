.PHONY: default all clean mrproper tar astyle libs

SRC_DIR := ./src

CC	:= g++
CFLAGS	:= -W -Wall --ansi --pedantic -g

INCLUDE	:= -Isrc/ -I/usr/include -I/usr/include/SDL
LIBS	:= -L/usr/lib -lSDL
export BUILD_DIR=$(PWD)/build

STATIC_LIBS = $(BUILD_DIR)/screen_vector.a

TARGET		:= main
HPP_FILES	:= $(wildcard $(SRC_DIR)/*.hpp)
CPP_FILES	:= $(wildcard $(SRC_DIR)/*.cpp)
O_FILES		:= $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

default: all

all: $(TARGET)

$(BUILD_DIR)/%.a:
	cd $(SRC_DIR)/$* && $(MAKE) all

$(TARGET): $(O_FILES) $(STATIC_LIBS) Makefile libs
	$(CC) -o $@ $(O_FILES) $(STATIC_LIBS) $(LDFLAGS) $(LIBS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@

clean:
	-rm -rf $(BUILD_DIR) *.orig *.tgz

mrproper: clean
	-rm -rf $(TARGET)

TMP	:= $(shell mktemp -d tmp)

tar: clean mrproper
	svn export . $(TMP)/screen
	cd $(TMP); tar zcfv screen.tgz screen
	mv $(TMP)/screen.tgz .
	rm -rf $(TMP)

astyle:
	astyle $(CPP_FILES) $(HPP_FILES)
