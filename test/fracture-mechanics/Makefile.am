
if HAVESALOME
#
CHECK_LIST= 

MESHDIR2=./../../data/meshes/2D/Geo-Files/Salome/
MESHDIR3=./../../data/meshes/3D/Geo-Files/
#
else !HAVESALOME
#
CHECK_LIST=check-sequential \
check-sequential-reactionforce \
check-parallel \
check-parallel-reactionforce \
check-fracture-mechanics \
check-point-bc

MESHDIR2=./../../data/meshes/2D/Geo-Files/Gmsh/
MESHDIR3=./../../data/meshes/3D/Geo-Files/
#
endif

all-local:
	@echo ""

check-local: check-header $(CHECK_LIST)
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Fracture Mechanics : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Fracture Mechanics : RUNNING                      "
	@echo "*============================================================*"
	@echo ""




SEQUENTIAL_FLAG_FM = -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -crackdirichletcondition -testflags
check-sequential:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_FM) > PreProcess-2D.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_FM) > PreProcess-3D.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-3D.log






SEQUENTIAL_FLAG_FM_RF = $(SEQUENTIAL_FLAG_FM) -getreactionforce
check-sequential-reactionforce:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_FM) > PreProcess-2D_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve_Seq  Main.edp -v 1 -ns -nw > Solve-2D_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_FM) > PreProcess-3D_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-3D_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_FM)  -reactionforce stress_based > PreProcess-2D_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_FM)  -reactionforce stress_based > PreProcess-3D_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-3D_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_FM)  -reactionforce variational_based > PreProcess-2D_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_FM)  -reactionforce variational_based  > PreProcess-3D_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-3D_reaction-force_variational-based.log








NP = 4
PARALLEL_FLAG_FM = -problem damage -model hybrid_phase_field -dirichletconditions 2 -crackdirichletcondition -testflags
check-parallel:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_FM)  > PreProcess-2D_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_FM) > PreProcess-3D_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_Parallel.log





PARALLEL_FLAG_FM_RF = $(PARALLEL_FLAG_FM) -getreactionforce
check-parallel-reactionforce:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_FM_RF) > PreProcess-2D_Parallel_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_Parallel_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_FM_RF) > PreProcess-3D_Parallel_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_Parallel_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_FM_RF)  -reactionforce stress_based > PreProcess-2D_Parallel_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_Parallel_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_FM_RF)  -reactionforce stress_based > PreProcess-3D_Parallel_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_Parallel_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_FM_RF)  -reactionforce variational_based > PreProcess-2D_Parallel_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_Parallel_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_FM_RF)  -reactionforce variational_based  > PreProcess-3D_Parallel_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_Parallel_reaction-force_variational-based.log




check-fracture-mechanics: check-header
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -crackdirichletcondition -testflags > PreProcess-2D_vectorial.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_vectorial.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -crackdirichletcondition -testflags > PreProcess-3D_vectorial.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_vectorial.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture vectorial with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -crackdirichletcondition -getreactionforce -testflags > PreProcess-2D_vectorial_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_vectorial_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture vectorial with reaction-force "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -crackdirichletcondition -testflags > PreProcess-3D_vectorial_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_vectorial_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture vectorial with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -crackdirichletcondition -reactionforce stress_based -testflags > PreProcess-2D_vectorial_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_vectorial_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture vectorial with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -crackdirichletcondition -reactionforce stress_based -testflags > PreProcess-3D_vectorial_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_vectorial_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture vectorial with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PreProcess-2D_vectorial_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_vectorial_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture vectorial with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PreProcess-3D_vectorial_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_vectorial_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture energydecomp "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -energydecomp -crackdirichletcondition -testflags > PreProcess-2D_energydecomp.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture energydecomp "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -energydecomp -crackdirichletcondition -testflags > PreProcess-3D_energydecomp.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-3D_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -crackdirichletcondition -testflags > PreProcess-2D_energydecomp_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_energydecomp_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -crackdirichletcondition -testflags > PreProcess-3D_energydecomp_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw  > Solve-3D_energydecomp_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -crackdirichletcondition -testflags > PreProcess-2D_energydecomp_Parallel_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_energydecomp_Parallel_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -crackdirichletcondition -testflags > PreProcess-3D_energydecomp_Parallel_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_energydecomp_Parallel_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PreProcess-2D_energydecomp_Parallel_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_energydecomp_Parallel_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture mechanics energydecomp with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PreProcess-3D_energydecomp_Parallel_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_energydecomp_Parallel_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PreProcess-2D_energydecomp_Parallel_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_energydecomp_Parallel_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PreProcess-3D_energydecomp_Parallel_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_energydecomp_Parallel_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -crackdirichletcondition -testflags > PreProcess-2D_energydecomp_Parallel_vectorial.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_energydecomp_Parallel_vectorial.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -crackdirichletcondition -testflags > PreProcess-3D_energydecomp_Parallel_vectorial.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_energydecomp_Parallel_vectorial.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp vectorial with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -crackdirichletcondition -testflags > PreProcess-2D_energydecomp_Parallel_vectorial_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_energydecomp_Parallel_vectorial_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp vectorial with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -crackdirichletcondition -testflags > PreProcess-3D_energydecomp_Parallel_vectorial_reaction-force.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_energydecomp_Parallel_vectorial_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp vectorial with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PreProcess-2D_energydecomp_Parallel_vectorial_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_energydecomp_Parallel_vectorial_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with energydecomp vectorial reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PreProcess-3D_energydecomp_Parallel_vectorial_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_energydecomp_Parallel_vectorial_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with energydecomp vectorial reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PreProcess-2D_energydecomp_Parallel_vectorial_reaction-force_variational-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_energydecomp_Parallel_vectorial_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with energydecomp vectorial reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PreProcess-3D_energydecomp_Parallel_vectorial_reaction-force_stress-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-3D_energydecomp_Parallel_vectorial_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture with GFP"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -useGFP -crackdirichletcondition -testflags > PreProcess-2D_GFP.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D_GFP.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture with GFP"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -useGFP -crackdirichletcondition -testflags > PreProcess-3D_GFP.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D_GFP.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with GFP"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -crackdirichletcondition -testflags > PreProcess-2D_GFP_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_GFP_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with GFP"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -crackdirichletcondition -testflags > PreProcess-3D_GFP_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_GFP_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with GFP vectoiral"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -vectorial -crackdirichletcondition -testflags > PreProcess-2D_GFP_Parallel_vectoiral.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_GFP_Parallel_vectoiral.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with GFP vectoiral"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -vectorial -crackdirichletcondition -testflags > PreProcess-3D_GFP_Parallel_vectoiral.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_GFP_Parallel_vectoiral.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture with GFP energydecomp"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -energydecomp -sequential -crackdirichletcondition -testflags > PreProcess-2D_GFP_energydecomp.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D_GFP_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture with GFP energydecomp"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -energydecomp -sequential -crackdirichletcondition -testflags > PreProcess-3D_GFP_energydecomp.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D_GFP_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with GFP energydecomp"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -energydecomp -crackdirichletcondition -testflags > PreProcess-2D_GFP_Parallel_energydecomp.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_GFP_Parallel_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with GFP energydecomp"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -energydecomp -crackdirichletcondition -testflags > PreProcess-3D_GFP_Parallel_energydecomp.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -v 1 -ns -nw > Solve-2D_GFP_Parallel_energydecomp.log





check-point-bc: check-header
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture point-bc"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 1 -dirichletpointconditions 1 -energydecomp -constrainHPF -getreactionforce -testflags > PreProcess-2D_PointBC.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;if(abs(uold[].max-7.618458e+01) > 1e-5)exit(111111);break;/g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#Pbc0Ux  -0. //#Pbc0Ux  -1000. //#g" {} \; && \
	./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)L_shaped_crack.msh -v 1 -ns -nw > PreProcess-2D_PointBC.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture point-bc"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 1 -dirichletpointconditions 1 -energydecomp -constrainHPF -getreactionforce -testflags > PreProcess-2D_PointBC_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e \
		's/dtr;/dtr;real umaxG,umaxL=uold[].max;mpiAllReduce(umaxL,umaxG,mpiCommWorld,mpiMAX);if(abs(umaxG-7.619173e+01) > 1e-2){cout << "umaxG=" << umaxG << endl; exit(111111);}break;/g' {} \;
	find . -name ControlParameters.edp -exec sed -i -e "s#Pbc0Ux  -0. //#Pbc0Ux  -1000. //#g" {} \; && \
	./PSD_Solve -n 4  Main.edp -mesh $(MESHDIR2)L_shaped_crack.msh -v 1 -ns -nw > PreProcess-2D_PointBC_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture point-bc vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 1 -dirichletpointconditions 1 -energydecomp -constrainHPF -getreactionforce -testflags -vectorial > PreProcess-2D_PointBC_Parallel_vectorial.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e \
		's/dtr;/dtr;real umaxG,umaxL=uold[].max;mpiAllReduce(umaxL,umaxG,mpiCommWorld,mpiMAX);if(abs(umaxG-7.619173e+01) > 1e-2){cout << "umaxG=" << umaxG << endl; exit(111111);}break;/g' {} \;	find . -name ControlParameters.edp -exec sed -i -e "s#Pbc0Ux  -0. //#Pbc0Ux  -1000. //#g" {} \; && \
	./PSD_Solve -n 4  Main.edp -mesh $(MESHDIR2)L_shaped_crack.msh -v 1 -ns -nw > PreProcess-2D_PointBC_Parallel_vectorial.log

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq *.data


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
