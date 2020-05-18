all: servicemap server client
	
servicemap: servicemap.o 
	gcc -o servicemap servicemap.o
	
server: server.o 
	gcc -o server server.o

client: client.o 
	gcc -o client client.o

clean:
	rm server servicemap client *.o
