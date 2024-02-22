

if HAVESALOME
#
CHECK_LIST= 

MESHDIR2=./../../data/meshes/2D/Geo-Files/Salome
MESHDIR3=./../../data/meshes/3D/Geo-Files
#
else !HAVESALOME
#
CHECK_LIST=check-sequential \
check-sequential-gfp \
check-sequential-gfp-newmark \
check-sequential-gfp-getenergies \
check-parallel \
check-parallel-gfp \
check-sequential-gfp-newmark \
check-parallel-gfp-getenergies \
check-parallel-gfp-getenergies-newmark-pseudononlinear

MESHDIR2=./../../data/meshes/2D/Geo-Files/Gmsh
MESHDIR3=./../../data/meshes/3D/Geo-Files
#
endif

	
all-local: 
	@echo ""

check-local: check-header $(CHECK_LIST)
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Elastodynamics : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Elastodynamics : RUNNING                      "
	@echo "*============================================================*"
	@echo ""



SEQUENTIAL_FLAG_ED = -problem elastodynamics -sequential -dirichletconditions 1 -tractionconditions 1 -testflags 
check-sequential:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_ED) > PreProcess-2D.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_ED) > PreProcess-3D.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve_Seq Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D.log

check-sequential-gfp:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Elastodynamics GFP update"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_ED) -useGFP > PreProcess-2D_GFP.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve_Seq Main.edp  -mesh $(MESHDIR2)/bar_dynamic.msh  -v 1 -ns -nw > Solve-2D_GFP.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Elastodynamics GFP update"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_ED)  -useGFP > PreProcess-3D_GFP.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve_Seq Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D_GFP.log

check-sequential-gfp-getenergies:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Elastodynamics GFP update and plot energies"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_ED) -useGFP -getenergies > PreProcess-2D_GFP_getenergies.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve_Seq Main.edp  -mesh $(MESHDIR2)/bar_dynamic.msh  -v 1 -ns -nw > Solve-2D_GFP_getenergies.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Elastodynamics GFP update and plot energies"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_ED)  -useGFP -getenergies > PreProcess-3D_GFP_getenergies.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve_Seq Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D_GFP_getenergies.log
	


SEQUENTIAL_FLAG_ED_NB = $(SEQUENTIAL_FLAG_ED)  -useGFP -timediscretization newmark_beta
check-sequential-gfp-newmark:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Elastodynamics GFP update  and Newmark-Beta"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_ED_NB) > PreProcess-2D_GFP_Newmark.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve_Seq Main.edp  -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_GFP_Newmark.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Elastodynamics GFP update and Newmark-Beta"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_ED_NB) > PreProcess-3D_GFP_Newmark.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve_Seq Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D_GFP_Newmark.log
		
NP = 4
PARALLEL_FLAG_ED = -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 -testflags
check-parallel:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED) > PreProcess-2D_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp  -mesh $(MESHDIR2)/bar_dynamic.msh  -v 1 -ns -nw > Solve-2D_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED) > PreProcess-3D_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D_Parallel.log

check-parallel-gfp:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Elastodynamics GFP update"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED) -useGFP > PreProcess-2D_Parallel_GFP.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp  -mesh $(MESHDIR2)/bar_dynamic.msh  -v 1 -ns -nw > Solve-2D_Parallel_GFP.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Elastodynamics GFP update"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED) -useGFP > PreProcess-3D_Parallel_GFP.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D_Parallel_GFP.log

PARALLEL_FLAG_ED_NB = $(PARALLEL_FLAG_ED)  -useGFP -timediscretization newmark_beta
check-sequential-gfp-newmark:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Elastodynamics GFP update  and Newmark-Beta"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED_NB) > PreProcess-2D_parallel_GFP_Newmark.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP) Main.edp  -mesh $(MESHDIR2)/bar_dynamic.msh -v 1 -ns -nw > Solve-2D_parallel_GFP_Newmark.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Elastodynamics GFP update and Newmark-Beta"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED_NB) > PreProcess-3D_parallel_GFP_Newmark.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP) Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D_parallel_GFP_Newmark.log
	
check-parallel-gfp-getenergies:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Elastodynamics GFP update  and plot energies"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED) -useGFP -getenergies > PreProcess-2D_Parallel_GFP_getenergies.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp  -mesh $(MESHDIR2)/bar_dynamic.msh  -v 1 -ns -nw > Solve-2D_Parallel_GFP_getenergies.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Elastodynamics GFP update  and plot energies"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED) -useGFP -getenergies > PreProcess-3D_Parallel_GFP_getenergies.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D_Parallel_GFP_getenergies.log

PARALLEL_FLAG_ED_NB_NL = $(PARALLEL_FLAG_ED_NB)  -model pseudo_nonlinear -getenergies
check-parallel-gfp-getenergies-newmark-pseudononlinear:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Elastodynamics Newmark-beta, GFP update,  plot energies, pseudo NL"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_ED_NB_NL)  > PreProcess-2D_Parallel_GFP_getenergies_pseudoNL.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp  -mesh $(MESHDIR2)/bar_dynamic.msh  -v 1 -ns -nw > Solve-2D_Parallel_GFP_getenergies_pseudoNL.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D ElastodynamicsNewmark-beta, GFP update,  plot energies, pseudo NL"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_ED_NB_NL) > PreProcess-3D_Parallel_GFP_getenergies_pseudoNL.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp  -mesh $(MESHDIR3)/bar_dynamic.msh  -v 1 -ns -nw > Solve-3D_Parallel_GFP_getenergies_pseudoNL.log
	

				
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq *.data	
	

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
