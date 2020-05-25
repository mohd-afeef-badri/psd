# All tests for checking the solver

Manual way to run tests and check if something is broken. Perform in the `PSD` folder. 

*Note* `make check` does the same tests. So one could also run `make check` from the `PSD` source directory.

#### Test 1: Sequential 2D under gravitation body force 

```
./PSD_PreProcess -dimension 2 -bodyforce -sequential -dirichletconditions 1 \ 
&&  \
FreeFem++ Main.edp -v 10 -ns -nw
```

#### Test 2: Sequential 3D under gravitation body force

```
./PSD_PreProcess -dimension 3 -bodyforce -sequential -dirichletconditions 1 \ 
&&  \
FreeFem++ Main.edp -v 10 -ns -nw
```

#### Test 3: Parallel 2D under gravitation body force

```
./PSD_PreProcess -dimension 2 -bodyforce -dirichletconditions 1 \ 
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg  -ns -nw
```

#### Test 4: Parallel 3D under gravitation body force

```
./PSD_PreProcess -dimension 3 -bodyforce -dirichletconditions 1 \ 
&& \
ff-mpirun -np 4  Main.edp -v 0 -ksp_type cg  -ns -nw
```

#### Test 5: Sequential  2D cracking

```
./PSD_PreProcess -dimension 2 -nonlinear -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 10 -ns -nw
```

#### Test 6: Squential  3D cracking

```
./PSD_PreProcess -dimension 3 -nonlinear -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 10 -ns -nw
```

#### Test 7: Parallel  2D cracking 

```
./PSD_PreProcess -dimension 2 -nonlinear  -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; \
&& \
ff-mpirun -np 4 Main.edp -v 10 -ns -nw
```

#### Test 8: Parallel  3D cracking 

```
./PSD_PreProcess -dimension 3 -nonlinear -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; \
&& \
ff-mpirun -np 4 Main.edp -v 10 -ns -nw
```

#### Test 9: Sequential dynamic 2D solver

```
./PSD_PreProcess -dimension 2 -dynamic -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 10 -ns -nw
```

#### Test 10: Sequential dynamic 3D solver

```
./PSD_PreProcess -dimension 3 -dynamic -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 10 -ns -nw
```

#### Test 11: Parallel dynamic 2D solver

```
./PSD_PreProcess -dimension 3 -dynamic -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; \
&& \
ff-mpirun -np 4 Main.edp -v 10 -ns -nw
```

#### Test 12: Parallel dynamic 3D solver

```
./PSD_PreProcess -dimension 3 -dynamic -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; \
&& \
ff-mpirun -np 4 Main.edp -v 10 -ns -nw
```

#### Test 13: Sequential soil dynamic 2D solver

```
./PSD_PreProcess -dimension 2 -soildynamics -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 14: Parallel soil dynamic 2D solver

```
./PSD_PreProcess -dimension 2 -soildynamics -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; \
&& \
ff-mpirun -np 4 Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 15: Sequential soil dynamic 3D solver

```
./PSD_PreProcess -dimension 3 -soildynamics -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; \
&& \
FreeFem++ Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```

#### Test 16: Parallel soil dynamic 3D solver

```
./PSD_PreProcess -dimension 3 -soildynamics -sequential -dirichletconditions 1 \
&&  \
find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; \
&& \
ff-mpirun -np 4 Main.edp -v 0 -ksp_type cg -glut ffglut  -ns -nw
```





