# Use the GNU C/C++ compiler:
CC = gcc
CPP = g++

# COMPILER OPTIONS:
CFLAGS = -c #-g -Wall

#OBJECT FILES
OBJS = disk_sched.o

#TARGET FILES
TARGET = disk_sched

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

disk_sched.o: disk_sched.c disk_sched.h fcfs.c fcfs.h sstf.c scan.c cscan.c look.c clook.c
	$(CC) $(CFLAGS) fcfs.c fcfs.h disk_sched.c disk_sched.h sstf.c scan.c cscan.c look.c clook.c

clean:
	$(RM) *.o *.h.gch *~ $(TARGET)
