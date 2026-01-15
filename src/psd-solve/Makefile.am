FF_IS = `which $(FFMPI)`

EXPORT_PSD  =\nexport FF_LOADPATH="${prefix}/include/psd";\nexport FF_INCLUDEPATH="${prefix}/include/psd"
EXPORT_PSD +=\nexport PATH="$$PATH:${prefix}/bin";\nexport LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:${prefix}/lib"

BIN_SALOME_NAME=BINARIES-SALOME

if HAVEMED
EXPORT_MED  =\nexport PATH="${hdf5}/bin:$${PATH}"
EXPORT_MED +=\nexport LD_LIBRARY_PATH="${hdf5}/lib:$${LD_LIBRARY_PATH}"
EXPORT_MED +=\nexport PATH="${medfile}/bin:$${PATH}"
EXPORT_MED +=\nexport LD_LIBRARY_PATH="${medfile}/lib:$${LD_LIBRARY_PATH}"
EXPORT_MED +=\nexport MEDCOUPLING_ROOT_DIR="${medcoupling}"
EXPORT_MED +=\nexport PATH="$${MEDCOUPLING_ROOT_DIR}/bin:$${PATH}"
EXPORT_MED +=\nexport LD_LIBRARY_PATH="$${MEDCOUPLING_ROOT_DIR}/lib:$${LD_LIBRARY_PATH}"
else !HAVEMED
EXPORT_MED  =
endif


all-local: PSD_Solve PSD_Solve_Seq
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in:"; pwd
	@echo "*============================================================*"
	@echo ""

PSD_Solve_Seq:
	cat $(FF_IS) > PSD_Solve_Seq
	find . -name PSD_Solve_Seq -exec sed -i -e 's#mpirun=mpirun#mpirun=mpirun;\n$(EXPORT_PSD)$(EXPORT_MED)\n#g' {} \;
	find . -name PSD_Solve_Seq -exec sed -i -e 's#^ffmpi=FreeFem++-mpi#ffmpi=$(FF)#g' {} \;
	find . -name PSD_Solve_Seq -exec sed -i -e 's#^j=1;#j=1;mpi_run_option=;a[0]=;#g' {} \;
	chmod a+x PSD_Solve_Seq

PSD_Solve:
	cat $(FF_IS) > PSD_Solve
	find . -name PSD_Solve -exec sed -i -e 's#mpirun=mpirun#mpirun=mpirun;\n$(EXPORT_PSD)$(EXPORT_MED);\n#g' {} \;
	find . -name PSD_Solve -exec sed -i -e 's#^ffmpi=FreeFem++-mpi#ffmpi=$(FF)-mpi#g' {} \;
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


distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
