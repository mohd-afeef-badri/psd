LIST_COMPILE= mfront.cpp

LOCAL_VERSION = no
REMOTE_VERSION = ${mgis}
	
all-local: mfront.so
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

mfront.so: mfront.cpp mfrontElasticityHandler.hpp
if HAVEMGIS
	find -name mfrontElasticityHandler.hpp -exec sed -i "s#/usr/lib#${prefix}/lib#g" {} \; && \
	$(FFCXX) -auto -mpi mfront.cpp ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	find -name mfrontElasticityHandler.hpp -exec sed -i "s#${prefix}/lib#/usr/lib#g" {} \;
else !HAVEMGIS	
	@echo ""
endif
	
install-exec-local:
	@mkdir -p ${prefix}/include
	@mkdir -p ${prefix}/include/psd
if HAVEMGIS	
	@cp mfront.so ${prefix}/include/psd/mfront.so	
endif
		
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
