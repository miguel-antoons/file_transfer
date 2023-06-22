CC = gcc
CFLAGS = -g -Wall -Werror
INCLUDES = -Iinclude
SRC = src/main.c
OBJ = main.o receiver.o sender.o
TARGET = transfer

compile: $(OBJ)
	@echo "Linking..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(TARGET)
	@echo "Done."

clean:
	@echo "Cleaning..."
	@rm -f $(OBJ) $(TARGET)
	@echo "Done."

main.o: src/main.c
	@echo "Compiling main.c..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c src/main.c

receiver.o: src/file_transfer/receiver.c src/file_transfer/receiver.h
	@echo "Compiling receiver.c..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c src/file_transfer/receiver.c

sender.o: src/file_transfer/sender.c src/file_transfer/sender.h
	@echo "Compiling sender.c..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c src/file_transfer/sender.c