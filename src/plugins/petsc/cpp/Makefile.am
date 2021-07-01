LIST_COMPILE= PSD-PETSc.cpp
	
all-local: PSD-PETSc.so
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

PSD-PETSc.so: PSD-PETSc.cpp common_hpddm.hpp ./../../paraview-output/cpp/PSD-iovtk.cpp
	$(FFCXX) -auto -mpi PSD-PETSc.cpp
	@echo ""	

install-exec-local:
	@mkdir -p ${prefix}/include
	@mkdir -p ${prefix}/include/psd
	@cp PSD-PETSc.so ${prefix}/include/psd/PSD-PETSc.so
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.so *.o


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
