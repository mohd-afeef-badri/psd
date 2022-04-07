LIST_COMPILE= medio.cpp

LOCAL_VERSION = no
REMOTE_VERSION = ${salome}

MEDCOUPLING_ROOT_DIR=${salome}/INSTALL/MEDCOUPLING
MEDFILE_ROOT_DIR=${salome}/INSTALL/medfile
HDF5_ROOT_DIR=${salome}/INSTALL/hdf5

DEP1 = medio.$(SO_SUFFIX)
	
all-local: $(DEP1)
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

$(DEP1): medio.cpp medio.hpp
if HAVESALOME
	export LD_LIBRARY_PATH=$(MEDFILE_ROOT_DIR)/lib:$(HDF5_ROOT_DIR)/lib:$(MEDCOUPLING_ROOT_DIR)/lib
	$(FFCXX) -auto medio.cpp -I$(MEDCOUPLING_ROOT_DIR)/include -I$(MEDFILE_ROOT_DIR)/include -I$(HDF5_ROOT_DIR)/include -L$(MEDCOUPLING_ROOT_DIR)/lib -lmedloader -lmedcoupling -linterpkernel -lmedcouplingremapper $(PDMT_DEBUG) -DMEDCOUPLING
else !HAVESALOME	
	@echo ""
endif
	
install-exec-local:
	@mkdir -p ${prefix}/include
	@mkdir -p ${prefix}/include/psd
if HAVESALOME	
	@cp $(DEP1) ${prefix}/include/psd/$(DEP1)
endif
		
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.$(SO_SUFFIX) *.o


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
