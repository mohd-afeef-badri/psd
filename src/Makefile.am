SUBDIRS=plugins psd-preprocessor
EXTRA_DIST=   	      \
./ff-files/DDmacro.edp  \
./ff-files/DDplotMacro.edp  \
./ff-files/MacroTools.edp  \
./ff-files/SolverGenerator.edp  \
./ff-files/simulation-log.csv  \
./plugins/gofastplugins.cpp  \
./plugins/iovtk.cpp  \
./plugins/MatrixPlotter.cpp

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm -f *~ 
	@echo ""
	
maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
