
# Define the test scripts
LE_TESTS = \
    test_seq_2d.sh \
    test_seq_3d.sh \
    test_seq_mt_2d.sh \
    test_seq_mt_3d.sh \
    test_par_2d.sh \
    test_par_3d.sh \
    test_par_pnl_2d.sh \
    test_par_pnl_3d.sh \
    test_par_mt_2d.sh \
    test_par_mt_3d.sh

# Add Mfront tests if MGIS is available
if !HAVESALOME
if HAVEMGIS
LE_TESTS += test_mfront_2d.sh test_mfront_pnl_2d.sh
endif
endif

TEST_EXTENSIONS = .sh
TESTS =

# Conditionals for Mesh Directories
if HAVESALOME
MESHDIR2 = ./../../data/meshes/2D/Geo-Files/Salome
MESHDIR3 = ./../../data/meshes/3D/Geo-Files
else !HAVESALOME
MESHDIR2 = ./../../data/meshes/2D/Geo-Files/Gmsh
MESHDIR3 = ./../../data/meshes/3D/Geo-Files
TESTS += $(LE_TESTS)
endif

check_SCRIPTS = $(TESTS)

# Environment variables for the shell scripts
AM_TESTS_ENVIRONMENT = \
    export NP='$(NP)'; \
    export MESHDIR2='$(MESHDIR2)'; \
    export MESHDIR3='$(MESHDIR3)'; \
    export SEQUENTIAL_FLAG_LE='-bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -testflags'; \
    export SEQUENTIAL_MT_FLAG_LE='-bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -testflags -withmaterialtensor'; \
    export PARALLEL_FLAG_LE='-bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags'; \
    export PARALLEL_MT_FLAG_LE='-bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags -withmaterialtensor'; \
    export PARALLEL_MF_FLAG_LE='-bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags -useMfront';

EXTRA_DIST = $(LE_TESTS)
NP = 4

all-local:
	@echo ""

copy-executables:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess

$(LE_TESTS): copy-executables

# --- Sequential Test Generation ---
test_seq_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$SEQUENTIAL_FLAG_LE > PreProcess-2D.log' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D.log' >> $@
	@chmod +x $@

test_seq_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$SEQUENTIAL_FLAG_LE > PreProcess-3D.log' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D.log' >> $@
	@chmod +x $@

test_seq_mt_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$SEQUENTIAL_MT_FLAG_LE > PreProcess-2D_withmaterialtensor.log' >> $@
	@echo './PSD_Solve_Seq Main.edp -v 1 -mesh $(MESHDIR2)/bar.msh -ns -nw > Solve-2D_withmaterialtensor.log' >> $@
	@chmod +x $@

test_seq_mt_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$SEQUENTIAL_MT_FLAG_LE > PreProcess-3D_withmaterialtensor.log' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_withmaterialtensor.log' >> $@
	@chmod +x $@

# --- Parallel Test Generation ---
test_par_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$PARALLEL_FLAG_LE > PreProcess-2D_Parallel.log' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel.log' >> $@
	@chmod +x $@

test_par_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$PARALLEL_FLAG_LE > PSD_PreProcess-3D_linear-elasticity_Parallel.log' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_Parallel.log' >> $@
	@chmod +x $@

test_par_pnl_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$PARALLEL_FLAG_LE -model pseudo_nonlinear > PreProcess-2D_Parallel_pseudo_nonlinear.log' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel_pseudo_nonlinear.log' >> $@
	@chmod +x $@

test_par_pnl_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$PARALLEL_FLAG_LE -model pseudo_nonlinear > PreProcess-3D_Parallel_pseudo_nonlinear.log' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_Parallel_pseudo_nonlinear.log' >> $@
	@chmod +x $@

test_par_mt_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$PARALLEL_MT_FLAG_LE > PreProcess-2D_Parallel_withmaterialtensor.log' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel_withmaterialtensor.log' >> $@
	@chmod +x $@

test_par_mt_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$PARALLEL_MT_FLAG_LE > PreProcess-3D_Parallel_withmaterialtensor.log' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_Parallel_withmaterialtensor.log' >> $@
	@chmod +x $@

# --- Mfront Test Generation ---
if HAVEMGIS
test_mfront_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$PARALLEL_MF_FLAG_LE > PreProcess-2D_Parallel_Mfornt.log' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#mfront#./../../src/plugins/mfront/cpp/mfront#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel_Mfornt.log' >> $@
	@chmod +x $@

test_mfront_pnl_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$PARALLEL_MF_FLAG_LE -model pseudo_nonlinear > PreProcess-2D_Parallel_Mfornt_pseudo_nonlinear.log' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#mfront#./../../src/plugins/mfront/cpp/mfront#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel_Mfornt_pseudo_nonlinear.log' >> $@
	@chmod +x $@
endif

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output *.csv *.edp-e
	rm  -f *~ *.log *.sh *.trs   *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq *.csv


distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
