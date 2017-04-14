CC=gcc
CFLAGS=-Wall -g
BIN=minftpd
OBJS=main.o sysutil.o session.o ftpproto.o privparent.o str.o

$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -f *.o $(BIN)

