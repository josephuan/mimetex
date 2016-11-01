#compile_as = bin
compile_as = solib
CC=g++


ifeq ($(compile_as),solib)
all:
	cc -O2 -shared -fPIC -D FOR_PYTHON_IMPLEMENT mimetex.c gifsave.c -lm -o lib_mimetex.so 
else
all:
	cc -g -DDebug -D DEBUG mimetex.c gifsave.c -lm -o mimetex  
endif

clean:
	rm -f *.o *~ \#*\# mimetex.h.gch  

	#cc -DAA -g -DDebug mimetex.c gifsave.c -lm -o mimetex
	#if [ ! -d cgi-bin ]; then mkdir cgi-bin; fi
	#mv mimetex.cgi cgi-bin    
