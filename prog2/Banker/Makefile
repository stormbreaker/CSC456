# Use the GNU C/C++ compiler:
CC = gcc
CPP = g++

#OBJECT FILES
OBJS = bank.o customer.o

#TARGET FILES
TARGET = bankers

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -pthread -o $(TARGET) $(OBJS)

bank.o: bank.c bank.h
	$(CC) -pthread -c bank.c

customer.o: customer.c customer.h
	$(CC) -pthread -c customer.c

clean:
	$(RM) *.gch *.o *~ $(TARGET)
