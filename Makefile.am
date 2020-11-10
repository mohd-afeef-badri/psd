SUBDIRS = src data test/load
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

homepsd = $${HOME}
all-local: logo
	@echo "*============================================================*"
	@echo " 'make' finished now do 'make check'"
	@echo "*============================================================*"

logo:
	@echo ""
	@echo "*============================================================*"
	@echo "                        ___               __                  "
	@echo "                      / __ \\   _____   __/  /                "
	@echo "                     / /_/ /  / ___/ / __  /                  "
	@echo "                    / ___ /  (__  ) / /_/ /                   "
	@echo "                   /_/      /____/  \\___ /                   "
	@echo "                                                              "
	@echo "*============================================================*"
	@echo ""

#        ifeq ("x","y")	
#	   THIS IS COMMENTED
#        endif

install-exec-local:
	@mkdir -p ${prefix}/include/psd
	@echo "  			  "
	@echo "*============================================================*"
	@echo " Finished installing  PSD version $(VERSION)"
	@echo "*============================================================*"
	@echo ""	
	
install-devel:
	@echo ""
	@echo "*============================================================*"
	@echo " # Making required directories                   "
	@mkdir -p ${prefix}/PSD-devel
	@mkdir -p ${prefix}/PSD-devel/Meshes
	@mkdir -p ${prefix}/PSD-devel/PSD_PreProcess-devel					
	@mkdir -p ${prefix}/PSD-devel/Meshes/2D
	@mkdir -p ${prefix}/PSD-devel/Meshes/3D
	@mkdir -p ${prefix}/PSD-devel/Plugins
	@mkdir -p ${prefix}/PSD-devel/Solver
	@mkdir -p ${prefix}/PSD-devel/Doc
	@echo ""
	@echo " # Copying meshes                   "	
	@cp  ./data/meshes/2D/Geo-Files/*.msh ${prefix}/PSD-devel/Meshes/2D/.
	@cp  ./data/meshes/2D/Geo-Files/*.geo ${prefix}/PSD-devel/Meshes/2D/.			
	@cp  ./data/meshes/3D/Geo-Files/*.msh ${prefix}/PSD-devel/Meshes/3D/.
	@cp  ./data/meshes/3D/Geo-Files/*.geo ${prefix}/PSD-devel/Meshes/3D/.
	@cp  ./etc/*.xyz 	${prefix}/PSD-devel/Meshes/3D/.					
	@echo ""
	@echo " # Copying PSD plugins/support-files                  "		
	@cp  ./src/plugins/top-ii-vol/cpp/top-ii-vol.so ${prefix}/PSD/Plugins/top-ii-vol.so	
	@cp  ./src/plugins/go-fast-plugins/cpp/gofastplugins.so ${prefix}/PSD/Plugins/gofastplugins.so
	@cp  ./src/plugins/go-fast-plugins/cpp/gofastplugins.cpp ${prefix}/PSD/Plugins/gofastplugins.cpp	
	@cp  ./src/plugins/paraview-output/cpp/iovtk.so ${prefix}/PSD/Plugins/iovtk.so
	@cp  ./src/plugins/paraview-output/cpp/iovtk.cpp ${prefix}/PSD/Plugins/iovtk.cpp	
	@cp  ./src/ff-files/DDmacro.edp ${prefix}/PSD-devel/Plugins/DDmacro.edp
	@cp  ./src/ff-files/DDplotMacro.edp ${prefix}/PSD-devel/Plugins/DDplotMacro.edp	
	@cp  ./src/ff-files/MacroTools.edp ${prefix}/PSD-devel/Plugins/MacroTools.edp	
	@cp  ./src/ff-files/simulation-log.csv ${prefix}/PSD-devel/Solver/.
	@echo ""
	@echo " # Copying PSD PreProcessor and solver                  "	
	@cp  ./src/psd-preprocessor/PSD_PreProcess ${prefix}/PSD-devel/Solver/PSD_PreProcess
	@cp  ./src/psd-solve/PSD_Solve ${prefix}/PSD-devel/Solver/PSD_Solve	
	@cp  ./src/psd-preprocessor/*.cpp ${prefix}/PSD-devel/PSD_PreProcess-devel/.	
	@cp  ./src/psd-preprocessor/*.hpp ${prefix}/PSD-devel/PSD_PreProcess-devel/.
	@cp  ./etc/Makefile-psd-preprocess-devel ${prefix}/PSD-devel/PSD_PreProcess-devel/Makefile
	@echo ""
	@echo " # Copying PSD documentation                  "
	@echo "*============================================================*"
	@echo ""	
	@cp  ./man/*.html ${prefix}/PSD-devel/Doc/.
	@cp  ./man/*.pdf ${prefix}/PSD-devel/Doc/.
	@cp  ./man/*.png  ${prefix}/PSD-devel/Doc/.	
	@echo "  			  "
	@echo "*============================================================*"
	@echo " Finished installing  PSD version $(VERSION) developers edition"
	@echo "*============================================================*"
	@echo ""	
	
check-local: 				 		 																			
	@echo ""
	@echo "*============================================================*"
	@echo " 'make check' finished now do 'make install'"
	@echo "*============================================================*"	
	@echo ""

documentation:
	@echo ""
	@echo "*============================================================*"
	@echo " making documentation :"; pwd
	@echo "*============================================================*"
	@echo ""	
	pandoc Readme.MD -o Readme.pdf
	pandoc Readme.MD -o Readme.html
	mv Readme.html man/.
	mv Readme.pdf  man/.
	pandoc 	Changelog.MD -o Changelog.pdf
	pandoc 	Changelog.MD -o Changelog.html
	mv Changelog.html man/.
	mv Changelog.pdf  man/.		
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~
		
maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning maintainer mode"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf ${AUTOMAKE_LIST}
