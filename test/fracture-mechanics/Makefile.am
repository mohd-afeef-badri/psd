	
all-local: 
	@echo ""

check-local: check-header check-fracture-mechanics
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

NP = 4

check-fracture-mechanics:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -crackdirichletcondition -getreactionforce -testflags > PSD_PreProcess-2D_fracture-mechanics_Parallel_reaction-force.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_Parallel_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -getreactionforce -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_Parallel_reaction-force.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_Parallel_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_Parallel_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_Parallel_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_Parallel_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_Parallel_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_Parallel_reaction-force_variational-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_Parallel_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_Parallel_reaction-force_variational-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_Parallel_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_vectorial.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_vectorial.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_vectorial.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_vectorial.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture vectorial with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -crackdirichletcondition -getreactionforce -testflags > PSD_PreProcess-2D_fracture-mechanics_vectorial_reaction-force.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_vectorial_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture vectorial with reaction-force "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_vectorial_reaction-force.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_vectorial_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture vectorial with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -crackdirichletcondition -reactionforce stress_based -testflags > PSD_PreProcess-2D_fracture-mechanics_vectorial_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_vectorial_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture vectorial with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -crackdirichletcondition -reactionforce stress_based -testflags > PSD_PreProcess-3D_fracture-mechanics_vectorial_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_vectorial_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture vectorial with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_vectorial_reaction-force_variational-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_vectorial_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture vectorial with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -vectorial -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_vectorial_reaction-force_variational-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_vectorial_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture energydecomp "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -energydecomp -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture energydecomp "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -energydecomp -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw  > PSD_Solve-3D_fracture-mechanics_energydecomp_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp_Parallel_reaction-force.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp_Parallel_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp_Parallel_reaction-force.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_energydecomp_Parallel_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp_Parallel_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp_Parallel_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture mechanics energydecomp with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp_Parallel_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_energydecomp_Parallel_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp_Parallel_reaction-force_variational-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp_Parallel_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp with reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp_Parallel_reaction-force_variational-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_energydecomp_Parallel_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp_Parallel_vectorial.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp_Parallel_vectorial.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp vectorial"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp_Parallel_vectorial.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_energydecomp_Parallel_vectorial.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp vectorial with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture energydecomp vectorial with reaction-force"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture energydecomp vectorial with reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with energydecomp vectorial reaction-force (stress-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -reactionforce stress_based -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force_stress-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with energydecomp vectorial reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force_variational-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with energydecomp vectorial reaction-force (variational-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -energydecomp -vectorial -getreactionforce -reactionforce variational_based -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force_stress-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_fracture-mechanics_energydecomp_Parallel_vectorial_reaction-force_variational-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture with GFP"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -useGFP -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_GFP.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture with GFP"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -useGFP -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_GFP.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with GFP"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_GFP_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with GFP"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_GFP_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with GFP vectoiral"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -vectorial -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_GFP_Parallel_vectoiral.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP_Parallel_vectoiral.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with GFP vectoiral"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -vectorial -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_GFP_Parallel_vectoiral.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP_Parallel_vectoiral.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D phase-field fracture with GFP energydecomp"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -energydecomp -sequential -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_GFP_energydecomp.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D phase-field fracture with GFP energydecomp"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -energydecomp -sequential -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_GFP_energydecomp.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D phase-field fracture with GFP energydecomp"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -energydecomp -crackdirichletcondition -testflags > PSD_PreProcess-2D_fracture-mechanics_GFP_Parallel_energydecomp.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP_Parallel_energydecomp.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D phase-field fracture with GFP energydecomp"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field -dirichletconditions 2 -useGFP -energydecomp -crackdirichletcondition -testflags > PSD_PreProcess-3D_fracture-mechanics_GFP_Parallel_energydecomp.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_fracture-mechanics_GFP_Parallel_energydecomp.log	

					
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
