TARGET = sharedMem noSharedMem condVar mutex
CC=gcc

all: $(TARGET)

%: %.c
	$(CC) $< -o $@ -lpthread

clean:
	rm -f $(TARGET)
