LIST_COMPILE= PSD-iovtk.cpp

DEP1 = PSD-iovtk.$(SO_SUFFIX)
	
all-local: $(DEP1)
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

PSD-iovtk.so: PSD-iovtk.cpp ./../../petsc/cpp/common_hpddm.hpp
	$(FFCXX) -auto PSD-iovtk.cpp
	@echo ""	

install-exec-local:
	@mkdir -p ${prefix}/include
	@mkdir -p ${prefix}/include/psd
	@cp $(DEP1) ${prefix}/include/psd/$(DEP1)
	
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
