SUBDIRS = src data 
EXTRA_DIST=README.MD Changelog.MD

AUTOMAKE_LIST=autom4te.cache \
config.h \
config.status \
configure \
install-sh \
missing \
Makefile \
Makefile.in \
aclocal.m4 \
config.h.in \
config.log \
stamp-h1 \
.swp


install-exec-local:
	@mkdir -p ${prefix}/PSD
	@mkdir -p ${prefix}/PSD/Meshes		
	@mkdir -p ${prefix}/PSD/Meshes/2D
	@mkdir -p ${prefix}/PSD/Meshes/3D
	@mkdir -p ${prefix}/PSD/Plugins
	@mkdir -p ${prefix}/PSD/Solver
#	@mkdir -p ${prefix}/PSD/Solver/ScriptModules
	@mkdir -p ${prefix}/PSD/Doc	
	@cp  ./data/meshes/2D/Meshes/* ${prefix}/PSD/Meshes/2D/.	
	@cp  ./data/meshes/3D/Meshes/* ${prefix}/PSD/Meshes/3D/.
	@cp  ./src/plugins/gofastplugins.so ${prefix}/PSD/Plugins/gofastplugins.so
	@cp  ./src/plugins/iovtk.so ${prefix}/PSD/Plugins/iovtk.so
	@cp  ./src/plugins/MatrixPlotter.so ${prefix}/PSD/Plugins/MatrixPlotter.so
	@cp  ./src/ff-files/DDmacro.edp ${prefix}/PSD/Plugins/DDmacro.edp
	@cp  ./src/ff-files/DDplotMacro.edp ${prefix}/PSD/Plugins/DDplotMacro.edp	
	@cp  ./src/ff-files/MacroTools.edp ${prefix}/PSD/Plugins/MacroTools.edp	
#	@cp  ./src/ff-files/SolverGenerator.edp ${prefix}/PSD/Solver/SolverGenerator.edp
	@cp  ./src/ff-files/simulation-log.csv ${prefix}/PSD/Solver/.
#	@cp  ./src/scripts/* ${prefix}/PSD/Solver/ScriptModules/.	
	@cp  ./src/psd-preprocessor/PSD_PreProcess ${prefix}/PSD/Solver/PSD_PreProcess
	@cp  ./man/*.html ${prefix}/PSD/Doc/.
	@cp  ./man/*.png  ${prefix}/PSD/Doc/.	
	@echo "  			  "
	@echo " Finished installing							  "
	@echo "==========================================================================="
	@echo "  ->   It is advised to check the solver for that do:			  "
	@echo "  			  						  "
	@echo "  			  						  "			
	@echo "  	make check 	                      "
	@echo "  			  						  "	
	@echo "  			  						  "	
	@echo " ****Note****						  "	
	@echo " # If you used the FFINSTALLDIR and GMSH while 'make'  "			
	@echo " # please use these flags  during  make check as well  "	
	@echo "  			  						  "
	@echo "  			  						  "				
	@echo "==========================================================================="
	@echo "  									  "
	
install-Super-Comp:
	@mkdir -p ${prefix}/PSD-Super-Comp
	@mkdir -p ${prefix}/PSD-Super-Comp/Meshes		
	@mkdir -p ${prefix}/PSD-Super-Comp/Meshes/2D
	@mkdir -p ${prefix}/PSD-Super-Comp/Meshes/3D
	@mkdir -p ${prefix}/PSD-Super-Comp/Plugins
	@mkdir -p ${prefix}/PSD-Super-Comp/Solver
#	@mkdir -p ${prefix}/PSD-Super-Comp/Solver/ScriptModules
	@mkdir -p ${prefix}/PSD-Super-Comp/Doc	
	@cp  ./data/meshes/2D/Meshes/* ${prefix}/PSD-Super-Comp/Meshes/2D/.	
	@cp  ./data/meshes/3D/Meshes/* ${prefix}/PSD-Super-Comp/Meshes/3D/.
	@cp  ./src/plugins/gofastplugins.cpp ${prefix}/PSD-Super-Comp/Plugins/gofastplugins.cpp
	@cp  ./src/plugins/iovtk.cpp ${prefix}/PSD-Super-Comp/Plugins/iovtk.cpp
	@cp  ./src/ff-files/DDmacro.edp ${prefix}/PSD-Super-Comp/Plugins/DDmacro.edp
	@cp  ./src/ff-files/DDplotMacro.edp ${prefix}/PSD-Super-Comp/Plugins/DDplotMacro.edp	
	@cp  ./src/ff-files/MacroTools.edp ${prefix}/PSD-Super-Comp/Plugins/MacroTools.edp	
#	@cp  ./src/ff-files/SolverGenerator.edp ${prefix}/PSD-Super-Comp/Solver/SolverGenerator.edp
	@cp  ./src/ff-files/simulation-log.csv ${prefix}/PSD-Super-Comp/Solver/.	
#	@cp  ./src/scripts/* ${prefix}/PSD-Super-Comp/Solver/ScriptModules/.
	@cp  ./src/psd-preprocessor/PSD_PreProcess ${prefix}/PSD-Super-Comp/Solver/PSD_PreProcess
	@cp  ./man/*.html ${prefix}/PSD-Super-Comp/Doc/.
	@cp  ./man/*.png  ${prefix}/PSD-Super-Comp/Doc/.	
	@echo "  			  "
	@echo "==========================================================================="
	@echo " Finished installing the supercomputer copy of PSD			  "
	@echo "  			  						  "			
	@echo " ****Note****								  "
	@echo "  			  						  "			
	@echo " # You still need to manullay install the plugins in the /plugins folder	  "			
	@echo " # Once PSD is trasfered on the Super-computer goto the /plugins folder &  "
	@echo "    $ make plugins 	  						  "	
	@echo "  			  						  "				
	@echo "==========================================================================="
	@echo "  									  "	
	
check: 				
	@echo "  			  "
	cd ${prefix}/PSD/Solver &&  \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 2  -bodyforce  -sequential -glut $(FFINSTALLDIR)ffglut   && \
	$(FF) Main.edp -glut $(FFINSTALLDIR)ffglut   -v 10 -ns -nw   && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 3  -bodyforce  -sequential -glut $(FFINSTALLDIR)ffglut   && \
	$(FF) Main.edp -glut $(FFINSTALLDIR)ffglut  -v 10 -ns -nw && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 2  -bodyforce -glut $(FFINSTALLDIR)ffglut && \
	$(FFMPI) -np 4  Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 3  -bodyforce -glut $(FFINSTALLDIR)ffglut && \
	$(FFMPI) -np 4  Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF) SolverGenerator.edp    -v 10  -dimension 2 -nonlinear -sequential -glut $(FFINSTALLDIR)ffglut && \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 3 -nonlinear -sequential -glut $(FFINSTALLDIR)ffglut && \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FF) Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 2 -nonlinear   -glut $(FFINSTALLDIR)ffglut && \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 4  Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 3 -nonlinear   -glut $(FFINSTALLDIR)ffglut && \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dtr;/dtr;break;/g" {} \; && \
	$(FFMPI) -np 4  Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF) SolverGenerator.edp    -v 10  -dimension 2 -dynamic -sequential -glut $(FFINSTALLDIR)ffglut && \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	$(FF) Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 3 -dynamic -sequential -glut $(FFINSTALLDIR)ffglut && \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	$(FF) Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 2 -dynamic   -glut $(FFINSTALLDIR)ffglut && \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	$(FFMPI) -np 4  Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw && \
	$(FF)  SolverGenerator.edp    -v 10  -dimension 3 -dynamic   -glut $(FFINSTALLDIR)ffglut && \
	find  -name LinearFormBuilderAndSolver.edp -exec sed -i "s/dt;/dt;break;/g" {} \; && \
	$(FFMPI) -np 4  Main.edp -v 10 -ksp_type cg -glut $(FFINSTALLDIR)ffglut  -ns -nw
	rm  -rf *.edp	
	@echo "  			  "
	@echo "==========================================================================="
	@echo "  ->   Finshed checking the solver, you are all set			  "
	@echo "==========================================================================="
	@echo "  									  "	
	
clean-automake:
	@echo "  			  "
	rm  -rf ${AUTOMAKE_LIST}
	rm  -rf ./data/Makefile ./data/Makefile.in
	rm  -rf ./data/meshes/2D/Geo-Files/Makefile ./data/meshes/2D/Geo-Files/Makefile.in
	rm  -rf ./data/meshes/3D/Geo-Files/Makefile ./data/meshes/3D/Geo-Files/Makefile.in
	rm  -rf ./src/Makefile ./src/Makefile.in
	rm  -rf ./src/plugins/Makefile ./src/plugins/Makefile.in
																
