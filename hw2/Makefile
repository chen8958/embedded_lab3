CC:=g++
OBJS = sockop
TARGETS=thread client

all: $(TARGETS)

$(OBJS).o: $(OBJS).c
	$(CC) -c -o $@ $<

thread: socketd.c $(OBJS).o
	$(CC) -pthread -o thread $^

client: socketc.c $(OBJS).o
	$(CC) -o client $^

clean:
	rm *.o
	rm $(TARGETS)
