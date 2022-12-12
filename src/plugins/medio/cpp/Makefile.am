LIST_COMPILE= medio.cpp

DEP1 = medio.$(SO_SUFFIX)
	
all-local: $(DEP1)
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

$(DEP1): medio.cpp medio.hpp medioSaveMedMesh.hpp medioLoadMedMesh.hpp medioGetGroupLabel.hpp
if HAVEMED
	$(FFCXX) -auto medio.cpp $(CXXFLAGS_MED)  $(LDFLAGS_MED) $(LIBS_MED) $(PDMT_DEBUG) -DMEDCOUPLING
else !HAVEMED	
	@echo ""
endif
	
install-exec-local:
	@mkdir -p ${prefix}/include
	@mkdir -p ${prefix}/include/psd
if HAVEMED	
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
