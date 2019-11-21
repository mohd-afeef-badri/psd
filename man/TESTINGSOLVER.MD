# All tests for checking the solver

Manual way to run tests and check if something is broken. Perform in the `PSD` folder. 

*Note* `make check` does the same tests. So one could also run `make check` from the `PSD` source directory.  

#### Test 1: Sequential 2D under gravitation body force 

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 2  -bodyforce  -sequential -glut ffglut \
&& \
FreeFem++ Main.edp -glut ffglut -v 0 -ns -nw 
```

#### Test 2: Sequential 3D under gravitation body force

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 3  -bodyforce  -sequential -glut ffglut \
&& \
FreeFem++ Main.edp -glut ffglut -v 0 -ns -nw
```

#### Test 3: Parallel 2D under gravitation body force

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 2  -bodyforce -glut ffglut \
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 4: Parallel 3D under gravitation body force

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 3  -bodyforce -glut ffglut \
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 5: Sequential non-linear 2D cracking

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 2 -nonlinear -sequential -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 6: Squential non-linear 3D cracking

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 3 -nonlinear -sequential -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 7: Parallel non-linear 2D cracking 

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 2 -nonlinear   -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; \
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 8: Parallel non-linear 3D cracking 

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 3 -nonlinear   -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; \
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 9: Sequential dynamic 2D solver

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 2 -dynamic -sequential -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/j++;/j++;break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 10: Sequential dynamic 3D solver

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 3 -dynamic -sequential -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/j++;/j++;break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 11: Parallel dynamic 2D solver

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 2 -dynamic   -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/j++;/j++;break;/g" {} \; \
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 12: Parallel dynamic 3D solver

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 3 -dynamic   -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/j++;/j++;break;/g" {} \; \
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 13: Sequential soil dynamic 2D solver

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 2 -soildynamics  -fastmethod -sequential -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 14: Parallel soil dynamic 2D solver

```
FreeFem++  SolverGenerator.edp    -v 0  -dimension 2 -soildynamics  -fastmethod  -glut ffglut \
&& \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; \
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw

