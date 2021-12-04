CC = g++
CPPFLAGS = -Wall -ansi
#
# If this is installed as a peer, this will find abi
#
ABIROOT=../../../../
ABISRC = $(ABIROOT)/abi/src

INCLUDE = -I$(ABISRC)/af/xap/xp \
          -I$(ABISRC)/af/util/xp \
	  -I$(ABISRC)/af/util/unix \
	  -I$(ABISRC)/text/fmt/xp \
	  -I$(ABISRC)/af/ev/xp \
	  -I$(ABISRC)/text/ptbl/xp \
	  -I$(ABISRC)/af/gr/xp \
	  -I$(ABISRC)/wp/impexp/xp \
	  -I$(ABISRC)/wp/ap/xp \
	  -I$(ABIROOT)/expat/lib \
	  -I..	  
LIBS = 

libGdictABI.so : GdictAbiPlugin.cpp
	$(CC) $(CPPFLAGS) $(INCLUDE) -shared -o libGdictABI.so GdictAbiPlugin.cpp $(LIBS)

clean: 
	rm *.so
