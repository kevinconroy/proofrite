SRCS=AbiGimp.cpp
ABI_RT=/home/msevior/abidir/abi-cvs/abi

INCLUDES=-I${ABI_RT}/src/af/xap/xp -I${ABI_RT}/src/text/fmt/xp -I${ABI_RT}/src/text/ptbl/xp -I${ABI_RT}/src/af/ev/xp -I${ABI_RT}/src/af/util/xp -I${ABI_RT}/src/wp/ap/xp -I${ABI_RT}/src/wp/impexp/xp -I${ABI_RT}/src/af/util/unix -I${ABI_RT}/src/af/gr/xp 

all: 
	g++ -g -shared -o libAbiGimp.so ${SRCS} ${INCLUDES} -DDEBUG