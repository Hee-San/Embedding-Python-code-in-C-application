hello: main.c
	$(eval cflags := $(shell python3.9-config --cflags))
	$(eval ldflags := $(shell python3.9-config --embed --ldflags))

	gcc -c $(cflags) main.c
	gcc -o main main.o $(ldflags)

	./main