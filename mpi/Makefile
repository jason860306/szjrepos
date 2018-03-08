MPI_CC=mpicc
MPI_FLAGS=
MPI_LIBS=
MPI_PATH=-I/usr/include/c++/4.4.4/ -I/usr/include/mpich2-x86_64

TARGET=mpi_test
all: $(TARGET)
.PHONY: all clean

mpi_test: mpi_test.c
	$(MPI_CC) $(MPI_FLAGS) $(MPI_LIBS) $(MPI_PATH) $^ -o $@

clean:
	@rm -f $(TARGET)
	@rm -f *.o
	@rm -f *~
