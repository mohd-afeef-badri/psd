LIST_COMPILE= Test_1


LOCAL_VERSION = no
REMOTE_VERSION = ${salome}

MEDCOUPLING_ROOT_DIR=${salome}/INSTALL/MEDCOUPLING
MEDFILE_ROOT_DIR=${salome}/INSTALL/medfile
HDF5_ROOT_DIR=${salome}/INSTALL/hdf5

#MEDCOUPLING_ROOT_DIR=/home/mb258512/Salome/Salome-Test-Bench/SALOME-master-UB18.04/INSTALL/MEDCOUPLING
#MEDFILE_ROOT_DIR=/home/mb258512/Salome/Salome-Test-Bench/SALOME-master-UB18.04/INSTALL/medfile
#HDF5_ROOT_DIR=/home/mb258512/Salome/Salome-Test-Bench/SALOME-master-UB18.04/INSTALL/hdf5

all-local:
	@echo ""

if HAVESALOME
check-local: check-header $(LIST_COMPILE)
	@echo ""
	@echo "*============================================================*"
	@echo " Checking medio plugin : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""
else !HAVESALOME
check-local: check-header
	@echo ""
	@echo "*============================================================*"
	@echo " Skipping medio plugin test                     "
	@echo "*============================================================*"
	@echo ""
endif
check-header:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking medio plugin : RUNNING                      "
	@echo "*============================================================*"
	@echo ""

Test_1: Test_1.edp
	@echo "Test_1 : medio load test"
	@./../../../psd-solve/PSD_Solve -np 1 Test_1.edp -v 1 >  Test_1.log
	@echo "  PASSED "

MedCoupling_Test: MedCoupling_Test.cpp
	@echo "MedCoupling unit tests"
	export LD_LIBRARY_PATH=$(MEDFILE_ROOT_DIR)/lib:$(HDF5_ROOT_DIR)/lib:$(MEDCOUPLING_ROOT_DIR)/lib
	$(CXX) MedCoupling_Test.cpp -I$(MEDCOUPLING_ROOT_DIR)/include -I$(MEDFILE_ROOT_DIR)/include -I$(HDF5_ROOT_DIR)/include -L$(MEDCOUPLING_ROOT_DIR)/lib -lmedloader -lmedcoupling -linterpkernel -lmedcouplingremapper $(PDMT_DEBUG) -DMEDCOUPLING
	@echo ""


clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.med
	rm  -f *~ *.log *.out


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
