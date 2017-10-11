CFLAGS = -Wall     # flags de compilacao
LDLIBS = -lm       # bibliotecas a ligar

EXECS  = wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix clean
 
# arquivos-objeto
objects = wavvol.o wavautovol.o wavinfo.o  wavrev.o wavecho.o wavwide.o wavcat.o wavmix.o audio-open.o 

all:  $(EXECS)

wavinfo: wavinfo.o audio-open.o
	gcc wavinfo.o audio-open.o -o wavinfo

wavrev: wavrev.o audio-open.o
	gcc wavrev.o audio-open.o -o wavrev

wavvol: wavvol.o audio-open.o
	gcc wavvol.o audio-open.o -o wavvol

wavautovol: wavautovol.o audio-open.o 
	gcc wavautovol.o audio-open.o -o wavautovol $(LDLIBS) 

wavecho: wavecho.o audio-open.o
	gcc wavecho.o audio-open.o -o wavecho $(LDLIBS) 

wavwide: wavwide.o audio-open.o
	gcc wavwide.o audio-open.o -o wavwide $(LDLIBS) 

wavcat: wavcat.o audio-open.o
	gcc wavcat.o audio-open.o -o wavcat

wavmix: wavmix.o audio-open.o
	gcc wavmix.o audio-open.o -o wavmix $(LDLIBS) 



wavvol.o : wavvol.c audio-open.h
	gcc -c wavvol.c $(CFLAGS)

wavinfo.o : wavinfo.c audio-open.h
	gcc -c wavinfo.c $(CFLAGS)
        
wavrev.o : wavrev.c audio-open.h
	gcc -c wavrev.c $(CFLAGS) 

wavautovol.o : wavautovol.c audio-open.h
	gcc -c wavautovol.c $(CFLAGS) $(LDLIBS) 

wavecho.o : wavecho.c audio-open.h
	gcc -c wavecho.c $(CFLAGS) $(LDLIBS) 	

wavwide.o: wavwide.c audio-open.h
	gcc -c wavwide.c $(CFLAGS) $(LDLIBS)  

wavcat.o: wavcat.c audio-open.h
	gcc -c wavcat.c $(CFLAGS) 

wavmix.o: wavmix.c audio-open.h
	gcc -c wavmix.c $(CFLAGS) $(LDLIBS) 

audio-open.o: audio-open.c audio-open.h
	gcc -c audio-open.c $(CFLAGS)


clean :
	-rm $(objects)

purge:
	-rm $(EXECS)