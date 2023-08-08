LIST_COMPILE= gofastplugins.cpp

DEP1 = gofastplugins.$(SO_SUFFIX)
	
all-local: $(DEP1)
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

$(DEP1): gofastplugins.cpp
	$(FFCXX) -auto gofastplugins.cpp
#	$(FFCXX) -auto -mpi gofastplugins.cpp -Wl,-rpath,/home/mb258512/Install/local/ff-petsc/r/lib '-L/home/mb258512/Install/local/ff-petsc/r/lib' '-lflapack' '-lfblas'
	@echo ""
	ldd gofastplugins.so	

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
