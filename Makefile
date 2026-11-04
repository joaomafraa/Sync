CC = gcc
CFLAGS = -Wall -Wextra -pthread

sync_car: sync_car.c sync_car-runner.c sync_car.h
	$(CC) $(CFLAGS) sync_car.c sync_car-runner.c -o sync_car

clean:
	rm -f sync_car

.PHONY: clean
