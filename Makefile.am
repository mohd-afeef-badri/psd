SUBDIRS = src data test/load
EXTRA_DIST=README.MD Changelog.MD

AUTOMAKE_LIST=autom4te.cache \
config.h \
config.status \
configure \
install-sh \
missing \
Makefile \
Makefile.in \
aclocal.m4 \
config.h.in \
config.log \
stamp-h1 \
.swp


all-local: logo
	@echo "*============================================================*"
	@echo " 'make' finished now do 'make check'"
	@echo "*============================================================*"

logo:
	@echo ""
	@echo "*============================================================*"
	@echo "                        ___               __                  "
	@echo "                      / __ \\   _____   __/  /                "
	@echo "                     / /_/ /  / ___/ / __  /                  "
	@echo "                    / ___ /  (__  ) / /_/ /                   "
	@echo "                   /_/      /____/  \\___ /                   "
	@echo "                                                              "
	@echo "*============================================================*"
	@echo ""

install-exec-local:
	@mkdir -p ${prefix}/PSD
	@mkdir -p ${prefix}/PSD/Meshes		
	@mkdir -p ${prefix}/PSD/Meshes/2D
	@mkdir -p ${prefix}/PSD/Meshes/3D
	@mkdir -p ${prefix}/PSD/Plugins
	@mkdir -p ${prefix}/PSD/Solver
#	@mkdir -p ${prefix}/PSD/Solver/ScriptModules
	@mkdir -p ${prefix}/PSD/Doc	
	@cp  ./data/meshes/2D/Meshes/* ${prefix}/PSD/Meshes/2D/.	
	@cp  ./data/meshes/3D/Meshes/* ${prefix}/PSD/Meshes/3D/.
	@cp  ./src/plugins/go-fast-plugins/cpp/gofastplugins.so ${prefix}/PSD/Plugins/gofastplugins.so
	@cp  ./src/plugins/top-ii-vol/cpp/top-ii-vol.so ${prefix}/PSD/Plugins/top-ii-vol.so	
	@cp  ./src/plugins/paraview-output/cpp/iovtk.so ${prefix}/PSD/Plugins/iovtk.so
	@cp  ./src/plugins/sparsity-visualizer/cpp/MatrixPlotter.so ${prefix}/PSD/Plugins/MatrixPlotter.so
	@cp  ./src/ff-files/DDmacro.edp ${prefix}/PSD/Plugins/DDmacro.edp
	@cp  ./src/ff-files/DDplotMacro.edp ${prefix}/PSD/Plugins/DDplotMacro.edp	
	@cp  ./src/ff-files/MacroTools.edp ${prefix}/PSD/Plugins/MacroTools.edp	
#	@cp  ./src/ff-files/SolverGenerator.edp ${prefix}/PSD/Solver/SolverGenerator.edp
	@cp  ./src/ff-files/simulation-log.csv ${prefix}/PSD/Solver/.
#	@cp  ./src/scripts/* ${prefix}/PSD/Solver/ScriptModules/.	
	@cp  ./src/psd-preprocessor/PSD_PreProcess ${prefix}/PSD/Solver/PSD_PreProcess
	@cp  ./etc/*.xyz ${prefix}/PSD-devel/PSD_PreProcess-devel/Makefile					
	@cp  ./man/*.html ${prefix}/PSD/Doc/.
	@cp  ./man/*.pdf ${prefix}/PSD/Doc/.
	@cp  ./man/*.png  ${prefix}/PSD/Doc/.	
	@echo ""
	@echo "*============================================================*"
	@echo "  Finished installing PSD version 2.0"
	@echo "*============================================================*"
	@echo ""
	
install-devel:
	@mkdir -p ${prefix}/PSD-devel
	@mkdir -p ${prefix}/PSD-devel/Meshes
	@mkdir -p ${prefix}/PSD-devel/PSD_PreProcess-devel					
	@mkdir -p ${prefix}/PSD-devel/Meshes/2D
	@mkdir -p ${prefix}/PSD-devel/Meshes/3D
	@mkdir -p ${prefix}/PSD-devel/Plugins
	@mkdir -p ${prefix}/PSD-devel/Solver
	@mkdir -p ${prefix}/PSD-devel/Doc	
	@cp  ./data/meshes/2D/Geo-Files/*.msh ${prefix}/PSD-devel/Meshes/2D/.
	@cp  ./data/meshes/2D/Geo-Files/*.geo ${prefix}/PSD-devel/Meshes/2D/.			
	@cp  ./data/meshes/3D/Geo-Files/*.msh ${prefix}/PSD-devel/Meshes/3D/.
	@cp  ./data/meshes/3D/Geo-Files/*.geo ${prefix}/PSD-devel/Meshes/3D/.	
	@cp  ./src/plugins/top-ii-vol/cpp/top-ii-vol.so ${prefix}/PSD/Plugins/top-ii-vol.so	
	@cp  ./src/plugins/go-fast-plugins/cpp/gofastplugins.so ${prefix}/PSD/Plugins/gofastplugins.so
	@cp  ./src/plugins/go-fast-plugins/cpp/gofastplugins.cpp ${prefix}/PSD/Plugins/gofastplugins.cpp	
	@cp  ./src/plugins/paraview-output/cpp/iovtk.so ${prefix}/PSD/Plugins/iovtk.so
	@cp  ./src/plugins/paraview-output/cpp/iovtk.cpp ${prefix}/PSD/Plugins/iovtk.cpp	
	@cp  ./src/ff-files/DDmacro.edp ${prefix}/PSD-devel/Plugins/DDmacro.edp
	@cp  ./src/ff-files/DDplotMacro.edp ${prefix}/PSD-devel/Plugins/DDplotMacro.edp	
	@cp  ./src/ff-files/MacroTools.edp ${prefix}/PSD-devel/Plugins/MacroTools.edp	
	@cp  ./src/ff-files/simulation-log.csv ${prefix}/PSD-devel/Solver/.	
	@cp  ./src/psd-preprocessor/PSD_PreProcess ${prefix}/PSD-devel/Solver/PSD_PreProcess
	@cp  ./src/psd-preprocessor/*.cpp ${prefix}/PSD-devel/PSD_PreProcess-devel/.	
	@cp  ./src/psd-preprocessor/*.hpp ${prefix}/PSD-devel/PSD_PreProcess-devel/.
	@cp  ./etc/Makefile-psd-preprocess-devel ${prefix}/PSD-devel/PSD_PreProcess-devel/Makefile
	@cp  ./etc/*.xyz 	${prefix}/PSD-devel/Meshes/3D/.				
	@cp  ./man/*.html ${prefix}/PSD-devel/Doc/.
	@cp  ./man/*.pdf ${prefix}/PSD-devel/Doc/.
	@cp  ./man/*.png  ${prefix}/PSD-devel/Doc/.	
	@echo "  			  "
	@echo "*============================================================*"
	@echo " Finished installing  PSD version 2.0 developers edition"
	@echo "*============================================================*"
	@echo ""	
	
check-local: 				
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential  2D linear-elasticity                   "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1conditions 1 -sequential -dirichletconditions 1  -testflags > PSD-check.log &&  \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential  3D linear-elasticity                   "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -sequential -dirichletconditions 1  -testflags >> PSD-check.log &&  \
	$(FF) Main.edp -v 0 -ns -nw   -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential  2D linear-elasticity fastmethod       "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -sequential -dirichletconditions 1 -fastmethod  -testflags >> PSD-check.log &&  \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log	
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential  3D linear-elasticity   fastmethod      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -sequential -dirichletconditions 1 -fastmethod  -testflags >> PSD-check.log &&  \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log 	 	
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity                   "
	@echo "*============================================================*"
	@echo ""	
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1  -dirichletconditions 1  -testflags >> PSD-check.log && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity                   "
	@echo "*============================================================*"
	@echo ""	
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1  -dirichletconditions 1  -testflags >> PSD-check.log &&  \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity      fastmethod             "
	@echo "*============================================================*"
	@echo ""	
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1  -dirichletconditions 1 -fastmethod  -testflags >> PSD-check.log &&  \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log	
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity     fastmethod              "
	@echo "*============================================================*"
	@echo ""	
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1  -dirichletconditions 1 -fastmethod  -testflags >> PSD-check.log &&  \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log 	 
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential  2D phase-field fracture mechanics      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -sequential -dirichletconditions 2  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential  3D phase-field fracture mechanics      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field -sequential -dirichletconditions 2  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture mechanics      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -dirichletconditions 2  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture mechanics      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field -dirichletconditions 2  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D  phase-field fracture mechanics energydecomp "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -sequential -dirichletconditions 2 -energydecomp  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture mechanics energydecomp "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field -sequential -dirichletconditions 2 -energydecomp  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture mechanics energydecomp "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -dirichletconditions 2 -energydecomp  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture mechanics energydecomp "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field -dirichletconditions 2 -energydecomp  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture mechanics with GFP     "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -sequential -dirichletconditions 2 -useGFP  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture mechanics with GFP     "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field -sequential -dirichletconditions 2 -useGFP  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture mechanics with GFP     "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -dirichletconditions 2 -useGFP  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture mechanics with GFP     "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field -dirichletconditions 2 -useGFP  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture mechanics with energydecomp & GFP     "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -sequential -dirichletconditions 2 -energydecomp -useGFP  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture mechanics with energydecomp & GFP     "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field -sequential -dirichletconditions 2 -energydecomp -useGFP  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture mechanics with energydecomp & GFP     "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field -dirichletconditions 2 -energydecomp -useGFP  -testflags >> PSD-check.log	 &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture mechanics with energydecomp & GFP     "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field -dirichletconditions 2 -energydecomp -useGFP  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 2  Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Elastodynamics                      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem elastodynamics -sequential -dirichletconditions 1  -tractionconditions 1 -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Elastodynamics                      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem elastodynamics -sequential -dirichletconditions 1 -tractionconditions 1 -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Elastodynamics                      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	$(FFMPI)  -np 2 Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Elastodynamics                      "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	$(FFMPI)  -np 2 Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Soildynamics                        "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem soildynamics -sequential -dirichletconditions 1  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Soildynamics                        "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem soildynamics -sequential -dirichletconditions 1  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	$(FF) Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Soildynamics                        "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	$(FFMPI) -np 2 Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics                        "
	@echo "*============================================================*"
	@echo ""
	cd ${prefix}/PSD/Solver &&  \
	./PSD_PreProcess -dimension 3 -problem soildynamics -dirichletconditions 1  -testflags >> PSD-check.log &&  \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	$(FFMPI) -np 2 Main.edp -v 0 -ns -nw  -testflags >> PSD-check.log &&  \
	rm  -rf *.edp	
	@echo ""
	@echo "*============================================================*"
	@echo " 'make check' finished now do 'make install'"
	@echo "*============================================================*"	
	@echo ""

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~
		
maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning maintainer mode"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf ${AUTOMAKE_LIST}
