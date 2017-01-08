TARGETS=solution0 solution1 solution2
all:$(TARGETS)

solution2:solution2.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread
