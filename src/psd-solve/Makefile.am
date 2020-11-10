FF_IS = `which $(FFMPI)`

all-local: PSD_Solve
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""

PSD_Solve:
	cat $(FF_IS) > PSD_Solve
	find  -name PSD_Solve -exec sed -i 's#mpirun=mpirun#mpirun=mpirun; export FF_LOADPATH="${prefix}/include/psd"; export FF_INCLUDEPATH="${prefix}/include/psd";#g' {} \;
	chmod a+x PSD_Solve
	
install-exec-local:
	@cp  PSD_Solve ${prefix}/bin/.			
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  PSD_Solve
	@echo ""


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
