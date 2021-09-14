LIST_COMPILE= gofastplugins.cpp
	
all-local: gofastplugins.so
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

gofastplugins.so: gofastplugins.cpp
	$(FFCXX) -auto -mpi gofastplugins.cpp '-lflapack' '-lfblas'
#	$(FFCXX) -auto -mpi gofastplugins.cpp -Wl,-rpath,/home/mb258512/Install/local/ff-petsc/r/lib '-L/home/mb258512/Install/local/ff-petsc/r/lib' '-lflapack' '-lfblas'
	@echo ""	

install-exec-local:
	@mkdir -p ${prefix}/include
	@mkdir -p ${prefix}/include/psd
	@cp gofastplugins.so ${prefix}/include/psd/gofastplugins.so	
		
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
