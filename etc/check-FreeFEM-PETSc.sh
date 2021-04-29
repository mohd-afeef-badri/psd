#!/bin/sh



echo 'load "PETSc"; cout << "Load PETSc Success "<< mpirank << endl; system("rm test.edp"); '>test.edp  | ff-mpirun -np 2 test.edp -ns -nw -v 0
RESULT=$?
echo ""
echo ""
echo "=================================================================="
echo "Testing if your system has a compiled version of FreeFEM and PETSc"
echo "=================================================================="
echo ""
if [ $RESULT -eq 0 ]; then
  echo " Test PASSED"
  echo " Your system has FreeFEM and PETSc compiled"
else
  echo " Test FAILED"
  echo " Your system does not have FreeFEM and PETSc compiled"
  echo " or the compilation is done wrongly"
fi
echo "=================================================================="

