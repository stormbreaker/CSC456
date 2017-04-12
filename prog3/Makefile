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

disk_sched.o: disk_sched.c disk_sched.h fcfs.c sstf.c scan.c cscan.c look.c clook.c
	$(CC) $(CFLAGS) disk_sched.c disk_sched.h fcfs.c sstf.c scan.c cscan.c look.c clook.c

clean:
	$(RM) *.o *~ $(TARGET)
