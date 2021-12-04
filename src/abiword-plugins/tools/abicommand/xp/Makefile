SRCS=AbiControl.cpp
ABI_RT=/home/msevior/abidir/abi-cvs/abi
READLINE=/usr/lib
INCLUDES=-I${ABI_RT}/src/af/xap/xp -I${ABI_RT}/src/text/fmt/xp -I${ABI_RT}/src/text/ptbl/xp -I${ABI_RT}/src/af/ev/xp -I${ABI_RT}/src/af/util/xp -I${ABI_RT}/src/wp/ap/xp  -I${ABI_RT}/src/wp/ap/unix -I${ABI_RT}/src/wp/impexp/xp -I${ABI_RT}/src/af/util/unix -I${ABI_RT}/src/af/gr/xp  -I${ABI_RT}/src/af/xap/unix -I/usr/include/gtk-1.2 -I/usr/include/glib-1.2 -I/usr/lib/glib/include `gnome-config --cflags bonobox`
LIBS= -L${READLINE}  -lreadline -lhistory -ltermcap `gnome-config --libs bonobox`
all: 
	g++ -g -shared -o libAbiControl.so ${SRCS} ${INCLUDES} -DDEBUG -DABI_BUILD_VERSION=\"0.99.5\"  ${LIBS}
	gcc -g -o test-container test-container.c ${INCLUDES} ${LIBS}



