# define environmental variables

CC=gcc
CFLAGS=-O2 -Wall -g
   GCTPLIB=-L/opt/Toolkit-x86_64/hdfeos2-19.1.00/lib -lGctp 

LIBS = -lm $(GCTPLIB)

GCTPINC=/opt/Toolkit-x86_64/hdfeos5-1.15/include
    HDFINC=/opt/Toolkit-x86_64/hdf-4.2.11/include

	
# compile
TARGET = solar.zenith.exe
  OBJS = solar.zenith.main.o \
		 mean_solarzen.o \
		 hls_projection.o\
		 local_solar.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)  -I$(GCTPINC) -I$(HDFINC)
solar.zenith.main.o:solar.zenith.main.c
	$(CC) $(CFLAGS) -c solar.zenith.main.c -I$(GCTPINC) -I$(HDFINC)
hls_projection.o: hls_projection.c
	$(CC) $(CFLAGS) -c hls_projection.c -I$(GCTPINC) -I$(HDFINC)
mean_solarzen.o: mean_solarzen.c
	$(CC) $(CFLAGS) -c mean_solarzen.c -I$(GCTPINC) -I$(HDFINC)
local_solar.o: local_solar.c
	$(CC) $(CFLAGS) -c local_solar.c $(LIBS)

clean:
	rm -f *.o

delete:
	rm -f $(TARGET)
