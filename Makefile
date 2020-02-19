server : server.o process.o
	gcc -o $@ $^ -lm

client : client.o
	gcc -o $@ $^

client.o : client.c
	gcc -c -std=c99 client.c

process.o : process.c
	gcc -c process.c

server.o : server.c
	gcc -c server.c

clean :
	rm server client server.o client.o process.o
