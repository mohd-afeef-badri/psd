# Define test scripts
TESTS =
TEST_EXTENSIONS = .sh

if !HAVESALOME
TESTS += test_sequential.sh \
         test_sequential_gfp.sh \
         test_sequential_gfp_newmark.sh \
         test_sequential_gfp_getenergies.sh \
         test_parallel.sh \
         test_parallel_gfp.sh \
         test_parallel_gfp_newmark.sh \
         test_parallel_gfp_getenergies.sh \
         test_parallel_gfp_getenergies_newmark_pseudononlinear.sh

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
SEQUENTIAL_FLAG_ED = -problem elastodynamics -sequential -dirichletconditions 1 -tractionconditions 1 -testflags
SEQUENTIAL_FLAG_ED_NB = $(SEQUENTIAL_FLAG_ED) -useGFP -timediscretization newmark_beta
PARALLEL_FLAG_ED = -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 -testflags
PARALLEL_FLAG_ED_NB = $(PARALLEL_FLAG_ED) -useGFP -timediscretization newmark_beta
PARALLEL_FLAG_ED_NB_NL = $(PARALLEL_FLAG_ED_NB) -model pseudo_nonlinear -getenergies

all-local:
	@echo ""

# This target copies executables and must complete before tests run
copy-executables:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Elastodynamics : RUNNING                          "
	@echo "*============================================================*"
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
	@echo 'echo " Sequential 2D Elastodynamics"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_ED) > PreProcess-2D.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 3D Elastodynamics"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_ED) > PreProcess-3D.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D.log' >> $@
	@chmod +x $@

test_sequential_gfp.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 2D Elastodynamics GFP update"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_ED) -useGFP > PreProcess-2D_GFP.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_GFP.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 3D Elastodynamics GFP update"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_ED) -useGFP > PreProcess-3D_GFP.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D_GFP.log' >> $@
	@chmod +x $@

test_sequential_gfp_getenergies.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 2D Elastodynamics GFP update and plot energies"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_ED) -useGFP -getenergies > PreProcess-2D_GFP_getenergies.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_GFP_getenergies.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 3D Elastodynamics GFP update and plot energies"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_ED) -useGFP -getenergies > PreProcess-3D_GFP_getenergies.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D_GFP_getenergies.log' >> $@
	@chmod +x $@

test_sequential_gfp_newmark.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 2D Elastodynamics GFP update and Newmark-Beta"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_ED_NB) > PreProcess-2D_GFP_Newmark.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_GFP_Newmark.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Sequential 3D Elastodynamics GFP update and Newmark-Beta"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_ED_NB) > PreProcess-3D_GFP_Newmark.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D_GFP_Newmark.log' >> $@
	@chmod +x $@

test_parallel.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 2D Elastodynamics"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED) > PreProcess-2D_Parallel.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_Parallel.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D Elastodynamics"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED) > PreProcess-3D_Parallel.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D_Parallel.log' >> $@
	@chmod +x $@

test_parallel_gfp.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 2D Elastodynamics GFP update"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED) -useGFP > PreProcess-2D_Parallel_GFP.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_Parallel_GFP.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D Elastodynamics GFP update"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED) -useGFP > PreProcess-3D_Parallel_GFP.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D_Parallel_GFP.log' >> $@
	@chmod +x $@

test_parallel_gfp_newmark.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 2D Elastodynamics GFP update and Newmark-Beta"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED_NB) > PreProcess-2D_parallel_GFP_Newmark.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_parallel_GFP_Newmark.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D Elastodynamics GFP update and Newmark-Beta"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED_NB) > PreProcess-3D_parallel_GFP_Newmark.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D_parallel_GFP_Newmark.log' >> $@
	@chmod +x $@

test_parallel_gfp_getenergies.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 2D Elastodynamics GFP update and plot energies"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED) -useGFP -getenergies > PreProcess-2D_Parallel_GFP_getenergies.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_Parallel_GFP_getenergies.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D Elastodynamics GFP update and plot energies"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED) -useGFP -getenergies > PreProcess-3D_Parallel_GFP_getenergies.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D_Parallel_GFP_getenergies.log' >> $@
	@chmod +x $@

test_parallel_gfp_getenergies_newmark_pseudononlinear.sh: copy-executables
	@echo '#!/bin/bash' > $@
	@echo 'set -e' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 2D Elastodynamics Newmark-beta, GFP update, plot energies, pseudo NL"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED_NB_NL) > PreProcess-2D_Parallel_GFP_getenergies_pseudoNL.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_Parallel_GFP_getenergies_pseudoNL.log' >> $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Parallel 3D Elastodynamics Newmark-beta, GFP update, plot energies, pseudo NL"' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED_NB_NL) > PreProcess-3D_Parallel_GFP_getenergies_pseudoNL.log' >> $@
	@echo 'find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \;' >> $@
	@echo 'find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \;' >> $@
	@echo './PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar_dynamic.msh -v 1 -ns -nw > Solve-3D_Parallel_GFP_getenergies_pseudoNL.log' >> $@
	@chmod +x $@

endif
				
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output *.csv *.edp-e
	rm  -f *~ *.log *.edp   *.sh *.trs PSD_Solve PSD_PreProcess PSD_Solve_Seq *.data	
	

distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
