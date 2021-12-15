	
all-local: 
	@echo ""

check-local: check-header check-Soildynamics
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Soildynamics : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Soildynamics : RUNNING                      "
	@echo "*============================================================*"
	@echo ""

NP = 4

check-Soildynamics:
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 2D Soildynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem soildynamics -sequential -dirichletconditions 1 -testflags > PSD_PreProcess-2D_soildynamics.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics.log		
	@echo ""
	@echo "*============================================================*"
	@echo " Sequential 3D Soildynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -sequential -dirichletconditions 1 -testflags > PSD_PreProcess-3D_soildynamics.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve_Seq Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Soildynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 -testflags > PSD_PreProcess-2D_soildynamics_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -dirichletconditions 1 -testflags > PSD_PreProcess-3D_soildynamics_Parallel.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/#./../../data/meshes/3D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Soildynamics with doublecouple (displacement-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem soildynamics -timediscretization newmark_beta -useGFP -doublecouple displacement_based -testflags > PSD_PreProcess-2D_soildynamics_Parallel_doublecouple_displacement-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel_doublecouple_displacement-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D Soildynamics with doublecouple (force-based)"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -problem soildynamics -timediscretization newmark_beta -useGFP -doublecouple force_based -testflags > PSD_PreProcess-2D_soildynamics_Parallel_doublecouple_force-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-2D_soildynamics_Parallel_doublecouple_force-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics with top-ii-vol meshing "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_force-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_force-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics with doublecouple (force-based) and top-ii-vol meshing "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -doublecouple force_based -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_doublecouple_force-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_doublecouple_force-based.log
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 3D Soildynamics with doublecouple (displacement-based) and top-ii-vol meshing"
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta -useGFP -top2vol-meshing -doublecouple displacement_based -testflags > PSD_PreProcess-3D_soildynamics_Parallel_top2vol_doublecouple_displacement-based.log && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s/t += dt;/break;/g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/gofastplugins#./../plugins/go-fast-plugins/cpp/gofastplugins#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/top-ii-vol#./../plugins/top-ii-vol/cpp/top-ii-vol#g" {} \; && \
	find . -name Main.edp -exec sed -i -e "s#../Plugins/DDmacro.edp#./../ff-files/DDmacro.edp#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#../Meshes/3D/Point-Cloud#./../../etc/Point-Cloud#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 1 -ns -nw > PSD_Solve-3D_soildynamics_Parallel_top2vol_doublecouple_displacement-based.log
					
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq *.data
	rm  -rf top-ii-vol-meshes	
	

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
