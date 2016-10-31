all:
	cc -DAA -g -DDebug mimetex.c gifsave.c -lm -o mimetex
	#if [ ! -d cgi-bin ]; then mkdir cgi-bin; fi
	#mv mimetex.cgi cgi-bin    
