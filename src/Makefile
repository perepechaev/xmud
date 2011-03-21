CXXFLAGS =  -O2 -g -Wall -fmessage-length=0

OBJS =      simple_server_main.o Socket.o ServerSocket.o \
			Message.o MessageStack.o \
			UserStack.o User.o\
			Encoder.o
LIBS = -lpthread
TARGET =   xmudd
INCLUDE = -I/usr/local/include


$(TARGET):  $(OBJS)
	    $(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS) $(INCLUDE) -liconv -L/usr/local/lib

all:    $(TARGET)
simple_server_main.o:
		$(CXX) -O2 $(CXXFLAGS) -c simple_server_main.cpp $(INCLUDE)
Encoder.o: 
		$(CXX) -O2 $(CXXFLAGS) -c Encoder.cpp -liconv -L/usr/local/lib $(INCLUDE)


clean:
	    rm -f $(OBJS) $(TARGET)

