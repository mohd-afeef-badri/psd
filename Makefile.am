SUBDIRS = src data 
EXTRA_DIST=README.MD

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
	@cp  ./man/*.html ${prefix}/PSD/Doc/.
	@cp  ./man/*.png  ${prefix}/PSD/Doc/.	
	@echo "  			  "
	@echo " Finished installing							  "
	@echo "==========================================================================="
	@echo "  ->   It is advised to do a make check 					  "
	@echo "==========================================================================="
	@echo "  									  "
	
check: 				
	@echo "  			  "
	@cp  ./data/Makefile1 ${prefix}/PSD/Solver/Makefile
	@cd ${prefix}/PSD/Solver && make check && rm Makefile
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
																
