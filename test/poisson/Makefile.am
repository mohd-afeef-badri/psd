
if HAVESALOME

CHECK_LIST= 

MESHDIR2=./../../data/meshes/2D/Geo-Files/Salome
MESHDIR3=./../../data/meshes/3D/Geo-Files
else !HAVESALOME

CHECK_LIST=check-sequential \
check-parallel

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
	@echo " Checking Poisson : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Poisson : RUNNING                      "
	@echo "*============================================================*"
	@echo ""



SEQUENTIAL_FLAG_LE = -sequential -problem poisson -testflags
check-sequential:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) > PreProcess-2D.log && \
	./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) > PreProcess-3D.log && \
	./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D.log


NP = 4
PARALLEL_FLAG_LE = -problem poisson -testflags
check-parallel:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_LE) > PreProcess-2D_Parallel.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > Solve-2D_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) > PSD_PreProcess-3D_Parallel.log && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -n $(NP)  Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > Solve-3D_Parallel.log

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq *.csv


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
