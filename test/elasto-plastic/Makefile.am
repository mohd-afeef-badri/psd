# Define test scripts
TESTS =
TEST_EXTENSIONS = .sh

if HAVESALOME
MESHDIR2=./../../data/meshes/2D/Geo-Files/Salome/
MESHDIR3=./../../data/meshes/3D/Geo-Files/
else !HAVESALOME
MESHDIR2=./../../data/meshes/2D/Geo-Files/Gmsh/
MESHDIR3=./../../data/meshes/3D/Geo-Files/

if HAVEMGIS
TESTS += test_elasto_plastic_mfront.sh
endif
endif

# Make test scripts executable
check_SCRIPTS = $(TESTS)

# Export variables for test environment
AM_TESTS_ENVIRONMENT = \
  export NP='$(NP)'; \
  export MESHDIR2='$(MESHDIR2)'; \
  export MESHDIR3='$(MESHDIR3)';

# Ensure required files are distributed
EXTRA_DIST = $(TESTS)

NP = 4

all-local:
	@echo ""

# This target copies executables and must complete before tests run
copy-executables:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess

# Make tests depend on executables being copied
$(TESTS): copy-executables

if !HAVESALOME
if HAVEMGIS
test_elasto_plastic_mfront.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 2D elasto-plasticity with mfront "' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 -tractionconditions 1 -problem elasto_plastic -dirichletconditions 2 -model von_mises -useMfront -testflags > PreProcess-2D_elasto-plasticity_Parallel_Mfornt.log' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#mfront#./../../src/plugins/mfront/cpp/mfront#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 0 -ns -nw > Solve-2D_elasto-plasticity_Parallel_Mfornt.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Checking Elasto Plasticity : SUCCESS                      "' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@chmod +x $@
endif
endif

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output *.csv *.edp-e
	rm  -f *~ *.log *.edp  *.sh *.trs PSD_Solve PSD_PreProcess PSD_Solve_Seq


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
