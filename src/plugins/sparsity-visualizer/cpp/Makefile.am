LIST_COMPILE= MatrixPlotter.cpp
	
all-local: MatrixPlotter.so
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

MatrixPlotter.so: MatrixPlotter.cpp
	$(FFCXX) -auto MatrixPlotter.cpp
	@echo ""
		
install-exec-local:
	@cp MatrixPlotter.so ${prefix}/include/psd/MatrixPlotter.so
	
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
