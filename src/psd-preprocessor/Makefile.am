LIST_COMPILE = PSD_PreProcess.cpp

PSD_PREPROCESSOR_HPP_LIST = ControlParameters.hpp \
FemParameters.hpp \
HeaderMacro.hpp \
Help.hpp \
LinearFormBuilderAndSolver_DamageMechanics.hpp \
LinearFormBuilderAndSolver_ElastoDynamics.hpp \
LinearFormBuilderAndSolver.hpp \
LinearFormBuilderAndSolver_LinearElasticity.hpp \
LinearFormBuilderAndSolver_SoilDynamics.hpp \
Macros.hpp \
Main.hpp \
Mesh.hpp \
OtherParameters.hpp \
PostProcessor.hpp \
PSD_PreProcess.cpp \
VariationalFormulation_DamageMechanics.hpp \
VariationalFormulation_ElastoDynamics.hpp \
VariationalFormulation.hpp \
VariationalFormulation_LinearElasticity.hpp \
VariationalFormulation_SoilDynamics.hpp \
DetectWrongArgument.hpp \
ErrorWrongArgument.hpp


NP = 4


AM_CPPFLAGS=-std=c++11 
bin_PROGRAMS = PSD_PreProcess
PSD_PreProcess_SOURCES = PSD_PreProcess.cpp

all-local: PSD_PreProcess.o
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"


#PSD_PreProcess: PSD_PreProcess.o
#	$(CXX) -o PSD_PreProcess PSD_PreProcess.o
#	@echo ""


PSD_PreProcess.o: PSD_PreProcess.cpp $(PSD_PREPROCESSOR_HPP_LIST)
	$(CXX) -c PSD_PreProcess.cpp -std=c++11

check-linear-elasticity:
	@cp ./../psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -testflags > PSD_PreProcess-2D_linear-elasticity.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -testflags > PSD_PreProcess-3D_linear-elasticity.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -withmaterialtensor -testflags > PSD_PreProcess-2D_linear-elasticity_withmaterialtensor.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_withmaterialtensor.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -withmaterialtensor  -testflags > PSD_PreProcess-3D_linear-elasticity_withmaterialtensor.log && \
	find  -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity_withmaterialtensor.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity"
	@echo "*============================================================*"
	@echo ""	
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags > PSD_PreProcess-2D_linear-elasticity_Parallel.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity"
	@echo "*============================================================*"
	@echo ""	
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags > PSD_PreProcess-3D_linear-elasticity_Parallel.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""	
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -withmaterialtensor -testflags > PSD_PreProcess-2D_linear-elasticity_Parallel_withmaterialtensor.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_Parallel_withmaterialtensor.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""	
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -withmaterialtensor -testflags > PSD_PreProcess-3D_linear-elasticity_Parallel_withmaterialtensor.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity_Parallel_withmaterialtensor.log






check-fracture-mechanics:
	cp ./../psd-solve/PSD_Solve ./PSD_Solve
	cp ./../psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
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
		





check-Elastodynamics:
	@cp ./../psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq	
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem elastodynamics -sequential -dirichletconditions 1 -tractionconditions 1 -testflags > PSD_PreProcess-2D_elastodynamics.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_elastodynamics.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem elastodynamics -sequential -dirichletconditions 1 -tractionconditions 1 -testflags > PSD_PreProcess-3D_elastodynamics.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_elastodynamics.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 -testflags > PSD_PreProcess-2D_elastodynamics_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_elastodynamics_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 -testflags > PSD_PreProcess-3D_elastodynamics_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_elastodynamics_Parallel.log








check-Soildynamics:
	@cp ./../psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Soildynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem soildynamics -sequential -dirichletconditions 1 -testflags > PSD_PreProcess-2D_soildynamics.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics.log		
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Soildynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -sequential -dirichletconditions 1 -testflags > PSD_PreProcess-3D_soildynamics.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Soildynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 -testflags > PSD_PreProcess-2D_soildynamics_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -dirichletconditions 1 -testflags > PSD_PreProcess-3D_soildynamics_Parallel.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Soildynamics with doublecouple (displacement-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem soildynamics -timediscretization newmark_beta -useGFP -doublecouple displacement_based -testflags > PSD_PreProcess-2D_soildynamics_Parallel_doublecouple_displacement-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel_doublecouple_displacement-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Soildynamics with doublecouple (force-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem soildynamics -timediscretization newmark_beta -useGFP -doublecouple force_based -testflags > PSD_PreProcess-2D_soildynamics_Parallel_doublecouple_force-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel_doublecouple_force-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics with top-ii-vol meshing "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_force-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_force-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics with doublecouple (force-based) and top-ii-vol meshing "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -doublecouple force_based -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_doublecouple_force-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_doublecouple_force-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics with doublecouple (displacement-based) and top-ii-vol meshing"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -doublecouple displacement_based -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_doublecouple_displacement-based.log && \
	find -name LinearFormBuilderAndSolver.edp -exec sed -i "s/t += dt;/break;/g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_doublecouple_displacement-based.log	
	
		
check-local: check-linear-elasticity check-fracture-mechanics check-Elastodynamics check-Soildynamics


clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm -f *~ PSD_PreProcess PSD_Solve PSD_Solve_Seq *.o *.edp *.log *.data
	rm -rf VTUs top-ii-vol-meshes
	@echo ""


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm -rf Makefile Makefile.in	
