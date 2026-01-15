LIST_COMPILE = MatrixPlotter.cpp

DEP1 = MatrixPlotter.$(SO_SUFFIX)
	
all-local: $(DEP1)
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

$(DEP1): MatrixPlotter.cpp
	$(FFCXX) -auto MatrixPlotter.cpp
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


distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
