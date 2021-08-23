
all-local:
	@echo ""

check-local: check-header check-linear-elasticity-Sequential check-linear-elasticity-Parallel check-linear-elasticity-Mfront
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

NP = 4

check-linear-elasticity-Sequential:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -testflags > PSD_PreProcess-2D_linear-elasticity.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -testflags > PSD_PreProcess-3D_linear-elasticity.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -withmaterialtensor -testflags > PSD_PreProcess-2D_linear-elasticity_withmaterialtensor.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_withmaterialtensor.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -sequential -problem linear_elasticity -dirichletconditions 1 -withmaterialtensor  -testflags > PSD_PreProcess-3D_linear-elasticity_withmaterialtensor.log && \
	find  -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity_withmaterialtensor.log


check-linear-elasticity-Parallel:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags > PSD_PreProcess-2D_linear-elasticity_Parallel.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -testflags > PSD_PreProcess-3D_linear-elasticity_Parallel.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with pseudo-nonlinear model"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -model pseudo_nonlinear -testflags > PSD_PreProcess-2D_linear-elasticity_Parallel_pseudo_nonlinear.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_Parallel_pseudo_nonlinear.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity with pseudo-nonlinear model"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -model pseudo_nonlinear -testflags > PSD_PreProcess-3D_linear-elasticity_Parallel_pseudo_nonlinear.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity_Parallel_pseudo_nonlinear.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -withmaterialtensor -testflags > PSD_PreProcess-2D_linear-elasticity_Parallel_withmaterialtensor.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_Parallel_withmaterialtensor.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D linear-elasticity with material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -withmaterialtensor -testflags > PSD_PreProcess-3D_linear-elasticity_Parallel_withmaterialtensor.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_linear-elasticity_Parallel_withmaterialtensor.log

check-linear-elasticity-Mfront:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with mfront building material tensor"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -useMfront -testflags > PSD_PreProcess-2D_linear-elasticity_Parallel_Mfornt.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_Parallel_Mfornt.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D linear-elasticity with mfront building material tensor and pseudononlinear model"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -bodyforceconditions 1 -problem linear_elasticity -dirichletconditions 1 -useMfront -model pseudo_nonlinear -testflags > PSD_PreProcess-2D_linear-elasticity_Parallel_Mfornt_pseudo_nonlinear.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_linear-elasticity_Parallel_Mfornt_pseudo_nonlinear.log

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
