CC = g++

CFLAGS = -g -Wall -lSDL2 -lGLEW -lGLU -lGL 

TARGET = shapes

all: $(TARGET)

$(TARGET): $(TARGET).cpp initShaders.h
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
  
