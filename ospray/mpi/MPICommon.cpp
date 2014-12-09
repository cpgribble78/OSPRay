/********************************************************************* *\
 * INTEL CORPORATION PROPRIETARY INFORMATION                            
 * This software is supplied under the terms of a license agreement or  
 * nondisclosure agreement with Intel Corporation and may not be copied 
 * or disclosed except in accordance with the terms of that agreement.  
 * Copyright (C) 2014 Intel Corporation. All Rights Reserved.           
 ********************************************************************* */

#include "MPICommon.h"

namespace ospray {
  namespace mpi {
    
    void init(int *ac, const char **av)
    {
      int initialized = false;
      MPI_Initialized(&initialized);
      if (!initialized) {
        // MPI_Init(ac,(char ***)&av);
        int required = MPI_THREAD_MULTIPLE;
        int provided = 0;
        MPI_Init_thread(ac,(char ***)&av,required,&provided);
        if (provided != required)
          throw std::runtime_error("MPI implementation does not offer multi-threading capabilities");
      }
      world.comm = MPI_COMM_WORLD;
      MPI_Comm_rank(MPI_COMM_WORLD,&world.rank);
      MPI_Comm_size(MPI_COMM_WORLD,&world.size);
    }
  }

}