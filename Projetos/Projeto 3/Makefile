CFLAGS = -Wall     # flags de compilacao
LDLIBS = -lm       # bibliotecas a ligar

EXECS  = wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix clean
 
# arquivos-objeto
objects = wavvol.o wavautovol.o wavinfo.o  wavrev.o wavecho.o wavwide.o wavcat.o wavmix.o audio-open.o arg-treat.o utilidades.o

all:  $(EXECS)

wavinfo: wavinfo.o audio-open.o arg-treat.o utilidades.o
	gcc wavinfo.o audio-open.o  arg-treat.o utilidades.o -o wavinfo

wavrev: wavrev.o audio-open.o arg-treat.o utilidades.o
	gcc wavrev.o audio-open.o arg-treat.o utilidades.o -o wavrev

wavvol: wavvol.o audio-open.o arg-treat.o utilidades.o
	gcc wavvol.o audio-open.o arg-treat.o utilidades.o -o wavvol

wavautovol: wavautovol.o audio-open.o utilidades.o
	gcc wavautovol.o audio-open.o arg-treat.o utilidades.o -o wavautovol $(LDLIBS) 

wavecho: wavecho.o audio-open.o arg-treat.o utilidades.o
	gcc wavecho.o audio-open.o arg-treat.o utilidades.o -o wavecho $(LDLIBS) 

wavwide: wavwide.o audio-open.o arg-treat.o utilidades.o
	gcc wavwide.o audio-open.o arg-treat.o utilidades.o -o wavwide $(LDLIBS) 

wavcat: wavcat.o audio-open.o arg-treat.o utilidades.o
	gcc wavcat.o audio-open.o arg-treat.o utilidades.o -o wavcat

wavmix: wavmix.o audio-open.o arg-treat.o utilidades.o
	gcc wavmix.o audio-open.o arg-treat.o utilidades.o -o wavmix $(LDLIBS) 



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

audio-open.o: audio-open.c audio-open.h utilidades.h
	gcc -c audio-open.c $(CFLAGS)

arg-treat.o: arg-treat.c arg-treat.h
	gcc -c arg-treat.c $(CFLAGS)

utilidades.o: utilidades.c utilidades.h
	gcc -c utilidades.c $(CFLAGS)


clean :
	-rm $(objects)

purge:
	-rm $(EXECS)