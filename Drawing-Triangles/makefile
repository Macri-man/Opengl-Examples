  CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CFLAGS  = -g -Wall -lglut -lGLEW -lGLU -lGL 

  # the build target executable:
  TARGET = shapes

  all: $(TARGET)

  $(TARGET): $(TARGET).cpp initShader.h
  	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

  clean:
  	$(RM) $(TARGET)
