SUBDIRS = src data 
EXTRA_DIST=README.MD


install-exec-local:
	@mkdir -p ${prefix}/PSD
	@mkdir -p ${prefix}/PSD/Meshes		
	@mkdir -p ${prefix}/PSD/Meshes/2D
	@mkdir -p ${prefix}/PSD/Meshes/3D
	@mkdir -p ${prefix}/PSD/Plugins
	@mkdir -p ${prefix}/PSD/Solver
	@mkdir -p ${prefix}/PSD/Solver/ScriptModules
	@mkdir -p ${prefix}/PSD/Doc	
	@cp  ./data/meshes/2D/Meshes/* ${prefix}/PSD/Meshes/2D/.	
	@cp  ./data/meshes/3D/Meshes/* ${prefix}/PSD/Meshes/3D/.
	@cp  ./src/plugins/gofastplugins.so ${prefix}/PSD/Plugins/gofastplugins.so
	@cp  ./src/plugins/iovtk.so ${prefix}/PSD/Plugins/iovtk.so
	@cp  ./src/plugins/MatrixPlotter.so ${prefix}/PSD/Plugins/MatrixPlotter.so
	@cp  ./src/ff-files/DDmacro.edp ${prefix}/PSD/Plugins/DDmacro.edp
	@cp  ./src/ff-files/MacroTools.edp ${prefix}/PSD/Plugins/MacroTools.edp	
	@cp  ./src/ff-files/SolverGenerator.edp ${prefix}/PSD/Solver/SolverGenerator.edp
	@cp  ./src/scripts/* ${prefix}/PSD/Solver/ScriptModules/.
	@cp  ./man/* ${prefix}/PSD/Doc/.
	@echo "  			  "
	@echo " Finished installing"
	@echo "==========================================================================="
	@echo "  ->   It is adviced to do a make check 					  "
	@echo "==========================================================================="
	
check: 				
	@echo "  			  "
	@cp  ./data/Makefile1 ${prefix}/PSD/Solver/Makefile
	@cd ${prefix}/PSD/Solver && make check && rm Makefile
