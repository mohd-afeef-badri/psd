LIST_COMPILE = PSD_PreProcess.cpp

PSD_PREPROCESSOR_HPP_LIST = Main.hpp \
ControlParameters.hpp \
./ControlParameters/DamageMechanics.hpp \
./ControlParameters/ElastoDynamics.hpp \
./ControlParameters/ElastoPlastic.hpp \
./ControlParameters/LinearElasticity.hpp \
./ControlParameters/SoilDynamics.hpp \
./ControlParameters/poisson.hpp \
FemParameters.hpp \
./FemParameters/DamageMechanics.hpp \
./FemParameters/ElastoDynamics.hpp \
./FemParameters/ElastoPlastic.hpp \
./FemParameters/LinearElasticity.hpp \
./FemParameters/SoilDynamics.hpp \
./FemParameters/poisson.hpp \
OtherParameters.hpp \
./OtherParameters/common.hpp \
./OtherParameters/DamageMechanics.hpp \
./OtherParameters/ElastoDynamics.hpp \
./OtherParameters/ElastoPlastic.hpp \
./OtherParameters/LinearElasticity.hpp \
./OtherParameters/SoilDynamics.hpp \
./OtherParameters/poisson.hpp \
HeaderMacro.hpp \
Help.hpp \
LinearFormBuilderAndSolver.hpp \
./LinearFormBuilderAndSolver/DamageMechanics.hpp \
./LinearFormBuilderAndSolver/ElastoDynamics.hpp \
./LinearFormBuilderAndSolver/LinearElasticity.hpp \
./LinearFormBuilderAndSolver/ElastoPlastic.hpp \
./LinearFormBuilderAndSolver/SoilDynamics.hpp \
./LinearFormBuilderAndSolver/poisson.hpp \
MeshAndFeSpace.hpp \
./MeshAndFeSpace/DamageMechanics.hpp \
./MeshAndFeSpace/ElastoDynamics.hpp \
./MeshAndFeSpace/LinearElasticity.hpp \
./MeshAndFeSpace/ElastoPlastic.hpp \
./MeshAndFeSpace/SoilDynamics.hpp \
./MeshAndFeSpace/poisson.hpp \
Macros.hpp \
./Macros/common.hpp \
./Macros/DamageMechanics.hpp \
./Macros/ElastoDynamics.hpp \
./Macros/LinearElasticity.hpp \
./Macros/ElastoPlastic.hpp \
./Macros/SoilDynamics.hpp \
./Macros/poisson.hpp \
PostProcessor.hpp \
PSD_PreProcess.cpp \
VariationalFormulation.hpp \
./VariationalFormulation/DamageMechanics.hpp \
./VariationalFormulation/ElastoDynamics.hpp \
./VariationalFormulation/ElastoPlastic.hpp \
./VariationalFormulation/LinearElasticity.hpp \
./VariationalFormulation/SoilDynamics.hpp \
./VariationalFormulation/poisson.hpp \
./Validation/Iwan.hpp \
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
if HAVEMED
	$(CXX) -c PSD_PreProcess.cpp -std=c++11 -DMEDCOUPLING
else !HAVEMED
	$(CXX) -c PSD_PreProcess.cpp -std=c++11
endif

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
