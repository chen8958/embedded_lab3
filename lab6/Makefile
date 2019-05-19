CC:=g++
OBJS = sockop
TARGETS=doodle makesem rmsem

all: $(TARGETS)

doodle: doodle.c
	$(CC) -o doodle $^

makesem: makesem.c
	$(CC) -o makesem $^

rmsem: rmsem.c
	$(CC) -o rmsem $^

clean:
	rm *.o
	rm $(TARGETS)
