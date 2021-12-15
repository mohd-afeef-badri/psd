	
all-local: 
	@echo ""

check-local: check-header check-Elastodynamics
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

NP = 4

check-Elastodynamics:	
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem elastodynamics -sequential -dirichletconditions 1 -tractionconditions 1 -testflags > PSD_PreProcess-2D_elastodynamics.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_elastodynamics.log
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem elastodynamics -sequential -dirichletconditions 1 -tractionconditions 1 -testflags > PSD_PreProcess-3D_elastodynamics.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_elastodynamics.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 -testflags > PSD_PreProcess-2D_elastodynamics_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_elastodynamics_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Elastodynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 -testflags > PSD_PreProcess-3D_elastodynamics_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/dt;/dt;break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_elastodynamics_Parallel.log
					
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
