

.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=dm04_mulfork my_system wait_status waitpid
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)




