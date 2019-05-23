CC:=g++
OBJS = sockop
TARGETS=thread client rmsem makesem

all: $(TARGETS)

$(OBJS).o: $(OBJS).c
	$(CC) -c -o $@ $<
rmsem: rmsem.c
	$(CC) -o rmsem $^

makesem: makesem.c
	$(CC) -o makesem $^

thread: socketd.c $(OBJS).o
	$(CC) -pthread -o thread $^

client: socketc.c $(OBJS).o
	$(CC) -o client $^

clean:
	rm *.o
	rm $(TARGETS)
