CC=gcc
FLAGS=-g -W -Wall -O0
INCPATH=-I/usr/src/kernels/`uname -r`-`uname -i`
LIBPATH=
LIBS=-lapue

OBJ=t_umask ipc_shm iov_demo unix_socket
All: $(OBJ)

t_umask: t_umask.c
	$(CC) $(FLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $^ -o $@

ipc_shm: ipc_shm.c
	$(CC) $(FLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $^ -o $@

iov_demo: iov_demo.c
	$(CC) $(FLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $^ -o $@

unix_socket: unix_socket.c
	$(CC) $(FLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $^ -o $@

clean:
	rm -rf $(OBJ) *~
