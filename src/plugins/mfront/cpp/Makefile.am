LIST_COMPILE= mfront.cpp

LOCAL_VERSION = no
REMOTE_VERSION = ${mgis}
DEP1 = mfront.$(SO_SUFFIX)
	
all-local: $(DEP1)
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

$(DEP1): mfront.cpp PsdMfrontHandler.hpp  PsdMfrontHandlerDm.hpp  PsdMfrontPrintBehaviourStats.hpp typedefinitions.hxx
if HAVEMGIS
	find . -name typedefinitions.hxx -exec sed -i -e "s#/usr/lib#${prefix}/lib#g" {} \;
	$(FFCXX) -auto -mpi mfront.cpp ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib -fopenmp -march=native -fopt-info-vec-missed
	find . -name typedefinitions.hxx -exec sed -i -e "s#${prefix}/lib#/usr/lib#g" {} \;
else !HAVEMGIS	
	@echo ""
endif
	
install-exec-local:
	@mkdir -p ${prefix}/include
	@mkdir -p ${prefix}/include/psd
if HAVEMGIS	
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
