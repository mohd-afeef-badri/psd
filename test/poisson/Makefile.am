# Define test scripts
TESTS =
TEST_EXTENSIONS = .sh

PARMMG_TESTS_LIST = test_parallel_adapt_iso_3d.sh \
         test_parallel_adapt_aniso_3d.sh \
         test_parallel_adapt_iso_grouping_3d.sh \
         test_parallel_adapt_aniso_grouping_3d.sh \
         test_parallel_adapt_iso_automatic_grouping_3d.sh \
         test_parallel_adapt_aniso_automatic_grouping_3d.sh

# Define a placeholder that is empty by default
# to use launch make check WITH_PARMMG_TESTS_LIST="$(PARMMG_TESTS_LIST)" 
WITH_PARMMG_TESTS_LIST = 

if !HAVESALOME
TESTS += test_sequential.sh \
         test_sequential_adapt.sh \
         test_sequential_adapt_aniso.sh \
         test_sequential_adapt_iso.sh \
         test_parallel.sh \
         test_sequential_adapt_iso_3d.sh \
         test_sequential_adapt_aniso_3d.sh

TESTS += $(WITH_PARMMG_TESTS_LIST)

MESHDIR2=./../../data/meshes/2D/Geo-Files/Gmsh
MESHDIR3=./../../data/meshes/3D/Geo-Files
else
MESHDIR2=./../../data/meshes/2D/Geo-Files/Salome
MESHDIR3=./../../data/meshes/3D/Geo-Files
endif

# Make test scripts executable
check_SCRIPTS = $(TESTS)

# Export variables for test environment
AM_TESTS_ENVIRONMENT = \
  export NP='$(NP)'; \
  export MESHDIR2='$(MESHDIR2)'; \
  export MESHDIR3='$(MESHDIR3)';

# Ensure test scripts are distributed
EXTRA_DIST = $(TESTS)

NP = 4
SEQUENTIAL_FLAG_LE = -sequential -problem poisson -testflags
ADAPT_FLAG = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend freefem
ANISO_FLAG = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend freefem -adaptmesh_type anisotropic
ISO_FLAG = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend freefem -adaptmesh_type isotropic
ISO_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend mmg -adaptmesh_type isotropic -adaptmesh_metric_backend mshmet
ANISO_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend mmg -adaptmesh_type anisotropic -adaptmesh_metric_backend mshmet
PARALLEL_FLAG_LE = -problem poisson -testflags
PAR_ISO_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type isotropic -adaptmesh_metric_backend mshmet
PAR_ANISO_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type anisotropic -adaptmesh_metric_backend mshmet
PAR_ISO_METHOD2_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type isotropic -adaptmesh_metric_backend mshmet -adaptmesh_parmmg_method partition_regrouping
PAR_ANISO_METHOD2_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type anisotropic -adaptmesh_metric_backend mshmet -adaptmesh_parmmg_method partition_regrouping
PAR_ISO_METHOD3_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type isotropic -adaptmesh_metric_backend mshmet -adaptmesh_parmmg_method partition_automatic_regrouping
PAR_ANISO_METHOD3_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type anisotropic -adaptmesh_metric_backend mshmet -adaptmesh_parmmg_method partition_automatic_regrouping

all-local:
	@echo ""

# This target copies executables and must complete before tests run
copy-executables:
	@echo ""
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess

# Make tests depend on executables being copied
$(TESTS): copy-executables

if !HAVESALOME
test_sequential.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 2D"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE)' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 3D"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE)' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_sequential_adapt.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 2D Adapt"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ADAPT_FLAG)' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_sequential_adapt_aniso.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 2D Anisotropic Adapt"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ANISO_FLAG)' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_sequential_adapt_iso.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 2D Isotropic Adapt"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ISO_FLAG)' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_sequential_adapt_iso_3d.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 3D isotropic Adapt"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) $(ISO_FLAG_3D)' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_sequential_adapt_aniso_3d.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 3D Anisotropic Adapt"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) $(ANISO_FLAG_3D)' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_parallel.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 2D"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_LE)' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE)' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_parallel_adapt_iso_3d.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D isotropic Adapt"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo 'mkdir -p VTUs' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_FLAG_3D)' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \;' >> $@
	@echo './PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_parallel_adapt_aniso_3d.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D anisotropic Adapt"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo 'mkdir -p VTUs' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_FLAG_3D)' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \;' >> $@
	@echo './PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_parallel_adapt_iso_grouping_3d.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D isotropic Adapt Grouping Method"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo 'mkdir -p VTUs' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_METHOD2_FLAG_3D)' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \;' >> $@
	@echo './PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_parallel_adapt_aniso_grouping_3d.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D anisotropic Adapt Grouping Method"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo 'mkdir -p VTUs' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_METHOD2_FLAG_3D)' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \;' >> $@
	@echo './PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_parallel_adapt_iso_automatic_grouping_3d.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D isotropic Adapt Automatic Grouping Method"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo 'mkdir -p VTUs' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_METHOD3_FLAG_3D)' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \;' >> $@
	@echo './PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw' >> $@
	@chmod +x $@

test_parallel_adapt_aniso_automatic_grouping_3d.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D anisotropic Adapt Automatic Grouping Method"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo 'mkdir -p VTUs' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_METHOD3_FLAG_3D)' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \;' >> $@
	@echo './PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw' >> $@
	@chmod +x $@
endif

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output *.csv *.edp-e *.sol
	rm  -f *~ *.log *.edp  *.sh *.trs PSD_Solve PSD_PreProcess PSD_Solve_Seq *.csv


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
