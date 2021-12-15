FF_IS = `which $(FFMPI)`

all-local: PSD_Solve PSD_Solve_Seq
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""

PSD_Solve_Seq:
	cat $(FF_IS) > PSD_Solve_Seq
	find . -name PSD_Solve_Seq -exec sed -i -e 's#mpirun=mpirun#mpirun=mpirun; export FF_LOADPATH="${prefix}/include/psd"; export FF_INCLUDEPATH="${prefix}/include/psd";#g' {} \;
	find . -name PSD_Solve_Seq -exec sed -i -e 's#^ffmpi=FreeFem++-mpi#ffmpi=FreeFem++#g' {} \;
	find . -name PSD_Solve_Seq -exec sed -i -e 's#^j=1;#j=1;mpi_run_option=;a[0]=;#g' {} \;
	chmod a+x PSD_Solve_Seq

PSD_Solve:
	cat $(FF_IS) > PSD_Solve
	find . -name PSD_Solve -exec sed -i -e 's#mpirun=mpirun#mpirun=mpirun; export FF_LOADPATH="${prefix}/include/psd"; export FF_INCLUDEPATH="${prefix}/include/psd";#g' {} \;
	chmod a+x PSD_Solve
	
install-exec-local:
	@cp  PSD_Solve     ${prefix}/bin/.	
	@cp  PSD_Solve_Seq ${prefix}/bin/.						
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  PSD_Solve PSD_Solve_Seq
	@echo ""


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
