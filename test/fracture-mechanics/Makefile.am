
# Define the full list of granular tests
FM_TESTS = \
    test_fm_seq_2d.sh \
    test_fm_seq_3d.sh \
    test_fm_par_2d.sh \
    test_fm_par_3d.sh \
    test_fm_par_vec_2d.sh \
    test_fm_par_vec_3d.sh \
    test_fm_ed_par_2d.sh \
    test_fm_ed_par_3d.sh

# Reaction Force variants (Split by dimension and method)
RF_TESTS = \
    test_fm_seq_rf_2d.sh

TEST_EXTENSIONS = .sh
TESTS =

# Mesh directories logic
if HAVESALOME
MESHDIR2 = ./../../data/meshes/2D/Geo-Files/Salome/
MESHDIR3 = ./../../data/meshes/3D/Geo-Files/
else !HAVESALOME
MESHDIR2 = ./../../data/meshes/2D/Geo-Files/Gmsh/
MESHDIR3 = ./../../data/meshes/3D/Geo-Files/
TESTS += $(FM_TESTS) $(RF_TESTS)
endif

check_SCRIPTS = $(TESTS)

# Environment variables for the shell scripts
AM_TESTS_ENVIRONMENT = \
    export NP='$(NP)'; \
    export MESHDIR2='$(MESHDIR2)'; \
    export MESHDIR3='$(MESHDIR3)'; \
    export SEQ_FM='-problem damage -model hybrid_phase_field -sequential -dirichletconditions 2 -crackdirichletcondition -testflags'; \
    export PAR_FM='-problem damage -model hybrid_phase_field -dirichletconditions 2 -crackdirichletcondition -testflags';

EXTRA_DIST = $(FM_TESTS) $(RF_TESTS)
NP = 4

copy-executables:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess

$(FM_TESTS) $(RF_TESTS): copy-executables

# --- 1. Sequential Phase-Field ---
test_fm_seq_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$SEQ_FM > PreProcess-2D.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-2D.log' >> $@
	@chmod +x $@

test_fm_seq_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$SEQ_FM > PreProcess-3D.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -v 1 -ns -nw > Solve-3D.log' >> $@
	@chmod +x $@

# --- 2. Parallel Phase-Field ---
test_fm_par_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$PAR_FM > PreProcess-2D_Par.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > Solve-2D_Par.log' >> $@
	@chmod +x $@

test_fm_par_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$PAR_FM > PreProcess-3D_Par.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > Solve-3D_Par.log' >> $@
	@chmod +x $@

# --- 3. Parallel Vectorial ---
test_fm_par_vec_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$PAR_FM -vectorial > PreProcess-2D_Vec.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > Solve-2D_Vec.log' >> $@
	@chmod +x $@

test_fm_par_vec_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$PAR_FM -vectorial > PreProcess-3D_Vec.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > Solve-3D_Vec.log' >> $@
	@chmod +x $@

# --- 4. Energy Decomposition (Parallel) ---
test_fm_ed_par_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 $$PAR_FM -energydecomp > PreProcess-2D_ED.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > Solve-2D_ED.log' >> $@
	@chmod +x $@

test_fm_ed_par_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 $$PAR_FM -energydecomp > PreProcess-3D_ED.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > Solve-3D_ED.log' >> $@
	@chmod +x $@

# --- 5. Example Reaction Force Script (Sequential) ---
test_fm_seq_rf_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'for MODE in "" "-reactionforce stress_based" "-reactionforce variational_based"; do' >> $@
	@echo '  ./PSD_PreProcess -dimension 2 $$SEQ_FM -getreactionforce $$MODE > PreProcess-2D_RF.log' >> $@
	@echo '  find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dtr;/dtr;break;/g" {} \;' >> $@
	@echo '  find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo '  find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)#g" {} \;' >> $@
	@echo '  ./PSD_Solve_Seq Main.edp -v 1 -ns -nw >> Solve-2D_RF.log' >> $@
	@echo 'done' >> $@
	@chmod +x $@

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output *.csv *.edp-e
	rm  -f *~ *.log *.sh *.trs *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq *.data

distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
