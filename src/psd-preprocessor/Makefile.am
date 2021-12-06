LIST_COMPILE = PSD_PreProcess.cpp

PSD_PREPROCESSOR_HPP_LIST = ControlParameters.hpp \
FemParameters.hpp \
HeaderMacro.hpp \
Help.hpp \
LinearFormBuilderAndSolver.hpp \
./LinearFormBuilderAndSolver/DamageMechanics.hpp \
./LinearFormBuilderAndSolver/ElastoDynamics.hpp \
./LinearFormBuilderAndSolver/LinearElasticity.hpp \
./LinearFormBuilderAndSolver/ElastoPlastic.hpp \
./LinearFormBuilderAndSolver/SoilDynamics.hpp \
Macros.hpp \
Main.hpp \
Mesh.hpp \
OtherParameters.hpp \
PostProcessor.hpp \
PSD_PreProcess.cpp \
VariationalFormulation.hpp \
./VariationalFormulation/DamageMechanics.hpp \
./VariationalFormulation/ElastoDynamics.hpp \
./VariationalFormulation/ElastoPlastic.hpp \
./VariationalFormulation/LinearElasticity.hpp \
./VariationalFormulation/SoilDynamics.hpp \
DetectWrongArgument.hpp \
ErrorWrongArgument.hpp

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

check-local:


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
