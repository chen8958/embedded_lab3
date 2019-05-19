CC:=g++
TARGETS=pipe select server client

all: $(TARGETS)

server:shm_server.c
	$(CC) -o server $^
client:shm_client.c
	$(CC) -o client $^
pipe: pipe.c
	$(CC) -o pipe $^

select: select.c
	$(CC) -o select $^

clean:
	rm *.o
	rm $(TARGETS)
