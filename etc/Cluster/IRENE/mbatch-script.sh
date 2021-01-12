#!/bin/bash
#MSUB -r PSD_SKL2B           # Request name
#MSUB -n 2                   # Number of tasks to use
#MSUB -N 1                   # Number of nodes to use
#MSUB -T 1000                # Elapsed time limit in seconds
#MSUB -q skylake             # Batch queue request
#MSUB -A dendm2s
#MSUB -m work

####MSUB -o ./testPSD_%I.o        # Standard output. %I is the job id
####MSUB -e ./testPSD_%I.e         # Error output. %I is the job id         

#./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -nonlinearmethod Picard -pipegnu -supercomp # -sequential
#ccc_mprun FreeFem++-mpi -nw Main.edp -v 0 -split 4 > testksp-48-split1-test.log


export FF_LOADPATH="/ccc/work/cont002/den/foerstee/local/include/psd"; 
export FF_INCLUDEPATH="/ccc/work/cont002/den/foerstee/local/include/psd";

ccc_mprun /ccc/work/cont002/den/foerstee/local/bin/FreeFem++-mpi -nw Main.edp -v 0 -split 4
