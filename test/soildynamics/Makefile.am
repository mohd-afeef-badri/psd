# Define the list of all soildynamics tests
SOILDYNAMICS_TESTS = \
  test_seq_2d.sh \
  test_seq_3d.sh \
  test_par_2d.sh \
  test_par_3d.sh \
  test_par_2d_dc_disp.sh \
  test_par_2d_dc_force.sh \
  test_par_3d_top2vol.sh \
  test_par_3d_top2vol_dc_force.sh \
  test_par_3d_top2vol_dc_disp.sh

TEST_EXTENSIONS = .sh
TESTS = 

# Mesh directories and conditionals
if HAVESALOME
MESHDIR2 = ./../../data/meshes/2D/Geo-Files/Salome
MESHDIR3 = ./../../data/meshes/3D/Geo-Files
else !HAVESALOME
MESHDIR2 = ./../../data/meshes/2D/Geo-Files/Gmsh
MESHDIR3 = ./../../data/meshes/3D/Geo-Files
# Enable tests if Salome is NOT used
TESTS += $(SOILDYNAMICS_TESTS)
endif

# Make test scripts executable
check_SCRIPTS = $(TESTS)

# Export variables for test environment
AM_TESTS_ENVIRONMENT = \
  export NP='$(NP)'; \
  export MESHDIR2='$(MESHDIR2)'; \
  export MESHDIR3='$(MESHDIR3)';

EXTRA_DIST = $(SOILDYNAMICS_TESTS)
NP = 4

all-local:
	@echo ""

copy-executables:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess

$(SOILDYNAMICS_TESTS): copy-executables

# --- Test Script Generation ---

test_seq_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 -problem soildynamics -sequential -dirichletconditions 1 -testflags > PSD_PreProcess-2D_soildynamics.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)/#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics.log' >> $@
	@chmod +x $@

test_seq_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 -problem soildynamics -sequential -dirichletconditions 1 -testflags > PSD_PreProcess-3D_soildynamics.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)/#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics.log' >> $@
	@chmod +x $@

test_par_2d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 -testflags > PSD_PreProcess-2D_soildynamics_Parallel.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel.log' >> $@
	@chmod +x $@

test_par_3d.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 -problem soildynamics -dirichletconditions 1 -testflags > PSD_PreProcess-3D_soildynamics_Parallel.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#$(MESHDIR3)/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel.log' >> $@
	@chmod +x $@

test_par_2d_dc_disp.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 -problem soildynamics -timediscretization newmark_beta -useGFP -doublecouple displacement_based -testflags > PSD_PreProcess-2D_soildynamics_Parallel_doublecouple_displacement-based.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel_doublecouple_displacement-based.log' >> $@
	@chmod +x $@

test_par_2d_dc_force.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 2 -problem soildynamics -timediscretization newmark_beta -useGFP -doublecouple force_based -testflags > PSD_PreProcess-2D_soildynamics_Parallel_doublecouple_force-based.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#$(MESHDIR2)/#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel_doublecouple_force-based.log' >> $@
	@chmod +x $@

test_par_3d_top2vol.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_force-based.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_force-based.log' >> $@
	@chmod +x $@

test_par_3d_top2vol_dc_force.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -doublecouple force_based -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_doublecouple_force-based.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_doublecouple_force-based.log' >> $@
	@chmod +x $@

test_par_3d_top2vol_dc_disp.sh:
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo './PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -doublecouple displacement_based -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_doublecouple_displacement-based.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo 'find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \;' >> $@
	@echo './PSD_Solve -n 2 Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_doublecouple_displacement-based.log' >> $@
	@chmod +x $@				
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output *.csv *.edp-e
	rm  -f *~ *.log *.edp *.sh *.trs  PSD_Solve PSD_PreProcess PSD_Solve_Seq *.data
	rm  -rf top-ii-vol-meshes	
	

distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
