// You have access to the following global variables :
int world_rank, world_size;
MPI_Comm custom_comm1, custom_comm2, custom_comm3, tmp;

// The tmp communicator is provided if you need to point somewhere, where you don't
// care about the outputted communicator. For instance, when using MPI_UNDEFINED as color.

// world_rank : rank of the process on MPI_COMM_WORLD
// world_size : size of MPI_COMM_WORLD
// These two variables are already initialised when splitting() is called

void splitting() {
  int color;
  MPI_Comm *new_comm;

  // 1- First splitting here.
  // With only one call to MPI_Comm_split you should be able to split processes 0-3 in custom_comm1
  // and processes 4-6 in custom_comm2

  if (world_rank < 4) {
    color = 1;
    new_comm = &custom_comm1;
  }
  else if (world_rank < 7) {
    color = 2;
    new_comm = &custom_comm2;
  }
  else {
    color = MPI_UNDEFINED;
    new_comm = &tmp;
  }

  MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, new_comm);
  
  // 2- Second splitting here
  // Now put processes 0 and 4 in custom_comm3

  if (world_rank == 0 || world_rank == 4) {
    color = 0;
    new_comm = &custom_comm3;
  }
  else {
    color = MPI_UNDEFINED;
    new_comm = &tmp;
  }

  MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, new_comm);

}
