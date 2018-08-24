

.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=dm03_fork dm04_mulfork  dm05_forkfile dm06_vfork hello loop_fork
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)




