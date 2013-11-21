CC=g++
CFLAGS=-W -Wall -ansi -pedantic `sdl-config --cflags --libs` 

INCLUDE=`sdl-config --cflags` -I. -I./include 
LIBS=`sdl-config --libs` 

LOCAL_BUILD=$(BUILD_DIR)/screen_vector

TARGET=$(BUILD_DIR)/screen_vector.a

SRC= $(wildcard *.cpp)
OBJ= $(SRC:%.cpp=$(BUILD_DIR)/screen_vector/%.o)

all: $(TARGET)

$(BUILD_DIR)/%.a: $(OBJ)
	ar rcs $@ $^

$(LOCAL_BUILD):
	mkdir $@

$(LOCAL_BUILD)/%.o: %.cpp $(LOCAL_BUILD)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

.PHONY: clean mrproper

clean:
	rm -rf $(BUILD_DIR)/screen_vector/

mrproper: clean
	rm -rf $(TARGET)
