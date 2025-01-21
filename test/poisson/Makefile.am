LOG_MODE ?= file
LOG_FILE_PREFIX ?= TestLogs

if HAVESALOME

CHECK_LIST= 

MESHDIR2=./../../data/meshes/2D/Geo-Files/Salome
MESHDIR3=./../../data/meshes/3D/Geo-Files
else !HAVESALOME

CHECK_LIST=check-sequential \
check-sequential-adapt \
check-sequential-adapt-aniso \
check-sequential-adapt-iso \
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
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) > $(LOG_FILE_PREFIX)-PreProcess-2D.log && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-2D.log; \
	else \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) | tee /dev/stdout && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D"
	@echo "*============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) > $(LOG_FILE_PREFIX)-PreProcess-3D.log && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D.log; \
	else \
		./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) | tee /dev/stdout && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi


ADAPT_FLAG = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend freefem
check-sequential-adapt:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Adapt"
	@echo "*============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ADAPT_FLAG) > $(LOG_FILE_PREFIX)-PreProcess-2D-adapt.log && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-2D-adapt.log; \
	else \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ADAPT_FLAG) | tee /dev/stdout && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi


ANISO_FLAG = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend freefem -adaptmesh_type anisotropic
check-sequential-adapt-aniso:
	@echo ""
	@echo "============================================================*"
	@echo " Sequential 2D Anisotropic Adapt"
	@echo "============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ANISO_FLAG) > $(LOG_FILE_PREFIX)-PreProcess-2D-adapt-aniso.log && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-2D-adapt-aniso.log; \
	else \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ANISO_FLAG) | tee /dev/stdout && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi


ISO_FLAG = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend freefem -adaptmesh_type isotropic
check-sequential-adapt-iso:
	@echo ""
	@echo "============================================================*"
	@echo " Sequential 2D Isotropic Adapt"
	@echo "============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ISO_FLAG) > $(LOG_FILE_PREFIX)-PreProcess-2D-adapt-iso.log && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-2D-adapt-iso.log; \
	else \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ISO_FLAG) | tee /dev/stdout && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi



NP = 4
PARALLEL_FLAG_LE = -problem poisson -testflags
# Parallel 2D
check-parallel:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D "
	@echo "*============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_LE) > $(LOG_FILE_PREFIX)-PreProcess-2D_Parallel.log; \
	else \
		./PSD_PreProcess -dimension 2 $(PARALLEL_FLAG_LE) | tee /dev/stdout; \
	fi
	@if [ "$(LOG_MODE)" = "file" ]; then \
		find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
		./PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-2D_Parallel.log; \
	else \
		find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
		./PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D "
	@echo "*============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) > $(LOG_FILE_PREFIX)-PreProcess-3D_Parallel.log; \
	else \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) | tee /dev/stdout; \
	fi
	@if [ "$(LOG_MODE)" = "file" ]; then \
		find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
		./PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D_Parallel.log; \
	else \
		find . -name Main.edp -exec sed -i -e "s#../Plugins/#./../ff-files/#g" {} \; && \
		./PSD_Solve -n $(NP) Main.edp -mesh $(MESHDIR3)/bar.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi


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
