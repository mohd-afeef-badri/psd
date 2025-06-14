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
check-parallel \
check-sequential-adapt-iso-3d \
check-sequential-adapt-aniso-3d \
check-parallel-adapt-iso-3d \
check-parallel-adapt-aniso-3d \
check-parallel-adapt-iso-grouping-3d \
check-parallel-adapt-aniso-grouping-3d \
check-parallel-adapt-iso-automatic-grouping-3d \
check-parallel-adapt-aniso-automatic-grouping-3d

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
	@echo "*============================================================*"
	@echo " Sequential 2D Anisotropic Adapt"
	@echo "*============================================================*"
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
	@echo "*============================================================*"
	@echo " Sequential 2D Isotropic Adapt"
	@echo "*============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ISO_FLAG) > $(LOG_FILE_PREFIX)-PreProcess-2D-adapt-iso.log && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-2D-adapt-iso.log; \
	else \
		./PSD_PreProcess -dimension 2 $(SEQUENTIAL_FLAG_LE) $(ISO_FLAG) | tee /dev/stdout && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR2)/bar.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi

ISO_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend mmg -adaptmesh_type isotropic -adaptmesh_metric_backend mshmet
check-sequential-adapt-iso-3d:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D isotropic Adapt"
	@echo "*============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) $(ISO_FLAG_3D) > $(LOG_FILE_PREFIX)-PreProcess-3D-adapt-iso.log && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D-adapt-iso.log; \
	else \
		./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) $(ISO_FLAG_3D) | tee /dev/stdout && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi


ANISO_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend mmg -adaptmesh_type anisotropic -adaptmesh_metric_backend mshmet
check-sequential-adapt-aniso-3d:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Anisotropic Adapt"
	@echo "*============================================================*"
	@echo ""
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) $(ANISO_FLAG_3D) > $(LOG_FILE_PREFIX)-PreProcess-3D-adapt-aniso.log && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D-adapt-aniso.log; \
	else \
		./PSD_PreProcess -dimension 3 $(SEQUENTIAL_FLAG_LE) $(ANISO_FLAG_3D) | tee /dev/stdout && \
		./PSD_Solve_Seq Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw | tee /dev/stdout; \
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


PAR_ISO_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type isotropic -adaptmesh_metric_backend mshmet
check-parallel-adapt-iso-3d:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D isotropic Adapt"
	@echo "*============================================================*"
	@echo ""
	@mkdir -p VTUs
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_FLAG_3D) > $(LOG_FILE_PREFIX)-PreProcess-3D-adapt-iso_Parallel.log && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D-adapt-iso_Parallel.log; \
	else \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_FLAG_3D) | tee /dev/stdout && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi

PAR_ANISO_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type anisotropic -adaptmesh_metric_backend mshmet
check-parallel-adapt-aniso-3d:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D anisotropic Adapt"
	@echo "*============================================================*"
	@echo ""
	@mkdir -p VTUs
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_FLAG_3D) > $(LOG_FILE_PREFIX)-PreProcess-3D-adapt-aniso_Parallel.log && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D-adapt-aniso_Parallel.log; \
	else \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_FLAG_3D) | tee /dev/stdout && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi


PAR_ISO_METHOD2_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type isotropic -adaptmesh_metric_backend mshmet -adaptmesh_parmmg_method partition_regrouping
check-parallel-adapt-iso-grouping-3d:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D isotropic Adapt Grouping Method"
	@echo "*============================================================*"
	@echo ""
	@mkdir -p VTUs
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_METHOD2_FLAG_3D) > $(LOG_FILE_PREFIX)-PreProcess-3D-adapt-iso-grouping_Parallel.log && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D-adapt-iso-grouping_Parallel.log; \
	else \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_METHOD2_FLAG_3D) | tee /dev/stdout && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi

PAR_ANISO_METHOD2_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type anisotropic -adaptmesh_metric_backend mshmet -adaptmesh_parmmg_method partition_regrouping
check-parallel-adapt-aniso-grouping-3d:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D anisotropic Adapt Grouping Method"
	@echo "*============================================================*"
	@echo ""
	@mkdir -p VTUs
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_METHOD2_FLAG_3D) > $(LOG_FILE_PREFIX)-PreProcess-3D-adapt-aniso-grouping_Parallel.log && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D-adapt-aniso-grouping_Parallel.log; \
	else \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_METHOD2_FLAG_3D) | tee /dev/stdout && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi

PAR_ISO_METHOD3_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type isotropic -adaptmesh_metric_backend mshmet -adaptmesh_parmmg_method partition_automatic_regrouping
check-parallel-adapt-iso-automatic-grouping-3d:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D isotropic Adapt Automatic Grouping Method"
	@echo "*============================================================*"
	@echo ""
	@mkdir -p VTUs
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_METHOD3_FLAG_3D) > $(LOG_FILE_PREFIX)-PreProcess-3D-adapt-iso-automatic_grouping_Parallel.log && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D-adapt-iso-automatic_grouping_Parallel.log; \
	else \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ISO_METHOD3_FLAG_3D) | tee /dev/stdout && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw | tee /dev/stdout; \
	fi

PAR_ANISO_METHOD3_FLAG_3D = -adaptmesh -adaptmesh_iter 1 -adaptmesh_backend parmmg -adaptmesh_type anisotropic -adaptmesh_metric_backend mshmet -adaptmesh_parmmg_method partition_automatic_regrouping
check-parallel-adapt-aniso-automatic-grouping-3d:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D anisotropic Adapt Automatic Grouping Method"
	@echo "*============================================================*"
	@echo ""
	@mkdir -p VTUs
	@if [ "$(LOG_MODE)" = "file" ]; then \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_METHOD3_FLAG_3D) > $(LOG_FILE_PREFIX)-PreProcess-3D-adapt-aniso-automatic_grouping_Parallel.log && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw > $(LOG_FILE_PREFIX)-Solve-3D-adapt-aniso-automatic_grouping_Parallel.log; \
	else \
		./PSD_PreProcess -dimension 3 $(PARALLEL_FLAG_LE) $(PAR_ANISO_METHOD3_FLAG_3D) | tee /dev/stdout && \
		find . -name ControlParameters.edp -exec sed -i -e "s#ddoptions(2) = 0.01;#ddoptions(2) = 0.05;#g" {} \; && \
		./PSD_Solve -np $(NP) Main.edp -mesh $(MESHDIR3)/cube.msh -v 1 -ns -nw | tee /dev/stdout; \
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
