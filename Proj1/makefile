all: et_crt ep_crt para_mm
	
	
et_crt:	et.o timing.o
		gcc -pthread -o et_crt et.o timing.o

ep_crt:	ep.o timing.o
		gcc -o ep_crt ep.o timing.o

para_mm:	para_mm.o timing.o
		gcc -pthread -o para_mm para_mm.o timing.o

clean:
	rm timing.o et.o ep.o para_mm.o et_crt ep_crt para_mm
