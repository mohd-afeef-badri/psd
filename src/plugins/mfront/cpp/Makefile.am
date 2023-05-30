LIST_COMPILE= mfront.cpp

FF_CPP_IS = `which $(FFCXX)`
FF_DEP_IS = `which $(FFCXXDEP)`

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

$(DEP1): mfront.cpp PsdMfrontHandler.hpp  PsdMfrontHandlerDm.hpp  PsdMfrontPrintBehaviourStats.hpp
if HAVEMGIS
	cat $(FF_CPP_IS) | sed 's/c++14/c++17/g' > ff-c++-temp && chmod a+x ff-c++-temp
	cp $(FF_DEP_IS) .
	find . -name typedefinitions.hxx -exec sed -i -e "s#/usr/lib#${prefix}/lib#g" {} \;
	./ff-c++-temp -auto -mpi mfront.cpp ${mgis}/lib/libMFrontGenericInterface.$(SO_SUFFIX) -I${mgis}/include -Wl,-rpath,${mgis}/lib -fopenmp -march=native -fopt-info-vec-missed
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
	rm  -f *~  *.$(SO_SUFFIX) *.o ./ff-c++-temp ./ff-get-dep


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
