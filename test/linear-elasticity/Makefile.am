
if HAVESALOME

CHECK_LIST= 

MESHDIR2=./../../data/meshes/2D/Geo-Files/Salome
MESHDIR3=./../../data/meshes/3D/Geo-Files
else !HAVESALOME

CHECK_LIST=check-sequential \
check-sequential-materialtensor \
check-parallel \
check-parallel-materialtensor \
check-mfront

MESHDIR2=./../../data/meshes/2D/Geo-Files/Gmsh
MESHDIR3=./../../data/meshes/3D/Geo-Files

endif

all-local:
	@echo ""

if !HAVESALOME

endif

check-local: check-header $(CHECK_LIST)
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Linear Elasticity : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Linear Elasticity : RUNNING                      "
	@echo "*============================================================*"
	@echo ""



SEQUENTIAL_FLAG_LE = -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -testflags
check-sequential:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) > PreProcess-2D.log && \
	./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) > PreProcess-3D.log && \
	./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D.log


SEQUENTIAL_MT_FLAG_LE = -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -testflags -withmaterialtensor
check-sequential-materialtensor:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_MT_FLAG_LE) > PreProcess-2D_withmaterialtensor.log && \
	./PSD_Solve_Seq Main.edp -v 1 -mesh $(MESHDIR2)/bar.msh -ns -nw > Solve-2D_withmaterialtensor.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_MT_FLAG_LE) > PreProcess-3D_withmaterialtensor.log && \
	./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_withmaterialtensor.log

NP = 4
PARALLEL_FLAG_LE = -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags
check-parallel:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_LE) > PreProcess-2D_Parallel.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) > PSD_PreProcess-3D_linear-elasticity_Parallel.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with pseudo-nonlinear model"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_LE) -model pseudo_nonlinear > PreProcess-2D_Parallel_pseudo_nonlinear.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel_pseudo_nonlinear.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity with pseudo-nonlinear model"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) -model pseudo_nonlinear > PreProcess-3D_Parallel_pseudo_nonlinear.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_Parallel_pseudo_nonlinear.log


PARALLEL_MT_FLAG_LE = -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags -withmaterialtensor
check-parallel-materialtensor:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_MT_FLAG_LE) > PreProcess-2D_Parallel_withmaterialtensor.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel_withmaterialtensor.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 $(PARALLEL_MT_FLAG_LE) > PreProcess-3D_Parallel_withmaterialtensor.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_Parallel_withmaterialtensor.log

PARALLEL_MF_FLAG_LE = -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags -useMfront
check-mfront:
if HAVEMGIS
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with mfront"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_MF_FLAG_LE) > PreProcess-2D_Parallel_Mfornt.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#mfront#./../../src/plugins/mfront/cpp/mfront#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel_Mfornt.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with mfront and pseudononlinear model"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_MF_FLAG_LE) -model pseudo_nonlinear > PreProcess-2D_Parallel_Mfornt_pseudo_nonlinear.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#mfront#./../../src/plugins/mfront/cpp/mfront#g" {} \; && \
	./PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh  -v 1 -ns -nw > Solve-2D_Parallel_Mfornt_pseudo_nonlinear.log
else !HAVEMGIS
	@echo ""
endif

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output *.csv *.edp-e
	rm  -f *~ *.log *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq *.csv


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
