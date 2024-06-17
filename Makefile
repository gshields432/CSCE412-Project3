CC = g++
CFLAGS = -Wall -Werror

all: myprogram

myprogram: loadbalancer.o webserver.o request.o
	$(CC) $(CFLAGS) -o myprogram loadbalancer.o webserver.o request.o

loadbalancer.o: loadbalancer.cpp
	$(CC) $(CFLAGS) -c loadbalancer.cpp

webserver.o: webserver.cpp
	$(CC) $(CFLAGS) -c webserver.cpp

request.o: request.cpp
	$(CC) $(CFLAGS) -c request.cpp

clean:
	rm -f myprogram *.o

