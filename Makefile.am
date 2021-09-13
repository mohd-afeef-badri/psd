SUBDIRS = src data test ext
EXTRA_DIST=README.MD Changelog.MD

AUTOMAKE_LIST=autom4te.cache \
config.h \
config.status \
configure \
depcomp  \
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
	@echo "  			  "
	@echo "*============================================================*"
	@echo " 'make' finished now do 'make install' or 'sudo make install'"
	@echo "*============================================================*"
	@echo "  			  "

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
	@echo "  			  "
	@echo "*============================================================*"
	@echo " IMPORTANT: In order to test everthing is ok do 'make check'"
	@echo "*============================================================*"
	@echo ""	

tutorials:
	@echo "*============================================================*"
	@echo ""
	@echo " ## tutorials ##   making directories       "
	@mkdir -p $${HOME}/PSD-tutorials/Meshes
	@mkdir -p $${HOME}/PSD-tutorials
	@mkdir -p $${HOME}/PSD-tutorials/elastodynamics
	@mkdir -p $${HOME}/PSD-tutorials/soildynamics
	@mkdir -p $${HOME}/PSD-tutorials/fracture-mechanics
	@mkdir -p $${HOME}/PSD-tutorials/linear-elasticity				
	@mkdir -p $${HOME}/PSD-tutorials/Doc
	@mkdir -p $${HOME}/PSD-tutorials/Meshes/2D
	@mkdir -p $${HOME}/PSD-tutorials/Meshes/3D		
	@echo " ## tutorials ##   Copying PSD documentation       "
	@cp  ./man/*.html $${HOME}/PSD-tutorials/Doc/.
	@cp  ./man/*.pdf  $${HOME}/PSD-tutorials/Doc/.
	@cp  ./man/*.png  $${HOME}/PSD-tutorials/Doc/.	
	@echo " ## tutorials ##   Copying meshes                  "	
	@cp  ./data/meshes/2D/Geo-Files/*.msh  $${HOME}/PSD-tutorials/Meshes/2D/.
	@cp  ./data/meshes/2D/Geo-Files/*.geo  $${HOME}/PSD-tutorials/Meshes/2D/.			
	@cp  ./data/meshes/3D/Geo-Files/*.msh  $${HOME}/PSD-tutorials/Meshes/3D/.
	@cp  ./data/meshes/3D/Geo-Files/*.geo  $${HOME}/PSD-tutorials/Meshes/3D/.
	@cp  ./etc/*.xyz 	               $${HOME}/PSD-tutorials/Meshes/3D/.
	@echo " ## tutorials ##   Copying text                  "	
	@echo ""			
	@cp  ./demos/elastodynamics/*.pdf      $${HOME}/PSD-tutorials/elastodynamics/.
	@cp  ./demos/soildynamics/*.pdf        $${HOME}/PSD-tutorials/soildynamics/.
	@cp  ./demos/linear-elasticity/*.pdf   $${HOME}/PSD-tutorials/linear-elasticity/.
	@cp  ./demos/fracture-mechanics/*.pdf  $${HOME}/PSD-tutorials/fracture-mechanics/.
	@echo "  tutorials installed at :    " $${HOME}/PSD-tutorials/;	
	@echo "  			  "
	@echo "*============================================================*"
	@echo " Finished installing  PSD version $(VERSION) tutorials"
	@echo "*============================================================*"
	@echo ""	
	
install-devel:
	@echo ""
	@echo "*============================================================*"
	@echo " # Making required directories                   "
	@mkdir -p $${HOME}/PSD-devel
	@mkdir -p $${HOME}/PSD-devel/Meshes
	@mkdir -p $${HOME}/PSD-devel/PSD_PreProcess-devel					
	@mkdir -p $${HOME}/PSD-devel/Meshes/2D
	@mkdir -p $${HOME}/PSD-devel/Meshes/3D
	@mkdir -p $${HOME}/PSD-devel/Plugins
	@mkdir -p $${HOME}/PSD-devel/Solver
	@mkdir -p $${HOME}/PSD-devel/Doc
	@echo ""
	@echo " # Copying meshes                   "	
	@cp  ./data/meshes/2D/Geo-Files/*.msh $${HOME}/PSD-devel/Meshes/2D/.
	@cp  ./data/meshes/2D/Geo-Files/*.geo $${HOME}/PSD-devel/Meshes/2D/.			
	@cp  ./data/meshes/3D/Geo-Files/*.msh $${HOME}/PSD-devel/Meshes/3D/.
	@cp  ./data/meshes/3D/Geo-Files/*.geo $${HOME}/PSD-devel/Meshes/3D/.
	@cp  ./etc/*.xyz 	              $${HOME}/PSD-devel/Meshes/3D/.					
	@echo ""
	@echo " # Copying PSD plugins/support-files                  "		
	@cp  ./src/plugins/top-ii-vol/cpp/top-ii-vol.so          $${HOME}/PSD-devel/Plugins/top-ii-vol.so	
	@cp  ./src/plugins/go-fast-plugins/cpp/gofastplugins.so  $${HOME}/PSD-devel/Plugins/gofastplugins.so
	@cp  ./src/plugins/go-fast-plugins/cpp/gofastplugins.cpp $${HOME}/PSD-devel/Plugins/gofastplugins.cpp
	@cp  ./src/plugins/petsc/cpp/PSD-PETSc.so                $${HOME}/PSD-devel/Plugins/PSD-PETSc.so
	@cp  ./src/plugins/petsc/cpp/PSD-PETSc.cpp               $${HOME}/PSD-devel/Plugins/PSD-PETSc.cpp		
	@cp  ./src/plugins/paraview-output/cpp/PSD-iovtk.so      $${HOME}/PSD-devel/Plugins/PSD-iovtk.so
	@cp  ./src/plugins/paraview-output/cpp/PSD-iovtk.cpp     $${HOME}/PSD-devel/Plugins/PSD-iovtk.cpp	
	@cp  ./src/ff-files/DDmacro.edp                          $${HOME}/PSD-devel/Plugins/DDmacro.edp
	@cp  ./src/ff-files/DDplotMacro.edp                      $${HOME}/PSD-devel/Plugins/DDplotMacro.edp	
	@cp  ./src/ff-files/MacroTools.edp                       $${HOME}/PSD-devel/Plugins/MacroTools.edp	
	@cp  ./src/ff-files/simulation-log.csv                   $${HOME}/PSD-devel/Solver/.
	@echo ""
	@echo " # Copying PSD PreProcessor and solver                  "	
	@cp  ./src/psd-preprocessor/PSD_PreProcess $${HOME}/PSD-devel/Solver/PSD_PreProcess
	@cp  ./src/psd-solve/PSD_Solve             $${HOME}/PSD-devel/Solver/PSD_Solve	
	@cp  ./src/psd-preprocessor/*.cpp          $${HOME}/PSD-devel/PSD_PreProcess-devel/.	
	@cp  ./src/psd-preprocessor/*.hpp          $${HOME}/PSD-devel/PSD_PreProcess-devel/.
	@cp  ./etc/Makefile-psd-preprocess-devel   $${HOME}/PSD-devel/PSD_PreProcess-devel/Makefile
	@echo ""
	@echo " # Copying PSD documentation                  "
	@echo "*============================================================*"
	@echo ""	
	@cp  ./man/*.html $${HOME}/PSD-devel/Doc/.
	@cp  ./man/*.pdf  $${HOME}/PSD-devel/Doc/.
	@cp  ./man/*.png  $${HOME}/PSD-devel/Doc/.	
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

documentation-readme: Readme.pdf Readme.html Readme.tex
	@echo ""

Readme.pdf: Readme.MD
	pandoc Readme.MD -o Readme.pdf -V geometry:margin=0.5in  --highlight-style espresso --pdf-engine=xelatex
	cp Readme.pdf  man/.	

Readme.tex: Readme.MD
	pandoc Readme.MD -o Readme.tex -r markdown-auto_identifiers --pdf-engine=xelatex --listings
	mv Readme.tex  etc/.
	
Readme.html: Readme.MD
	pandoc Readme.MD -o Readme.html
	cp Readme.html man/.				
	
documentation-Changelog: Changelog.pdf Changelog.html Changelog.tex
	@echo ""

Changelog.pdf: Changelog.MD
	pandoc 	Changelog.MD -o Changelog.pdf -V geometry:margin=0.5in  --highlight-style espresso --pdf-engine=xelatex
	cp Changelog.pdf man/.
	
Changelog.tex: Changelog.MD
	pandoc 	Changelog.MD -o Changelog.tex -r markdown-auto_identifiers --pdf-engine=xelatex --listings
	mv Changelog.tex etc/.	

Changelog.html: Changelog.MD
	pandoc 	Changelog.MD -o Changelog.html
	cp Changelog.html  man/.			
	
documentation: documentation-readme documentation-Changelog
	@echo ""
	@echo "*============================================================*"
	@echo " making documentation :"; pwd
	@echo "*============================================================*"
	
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.pdf *.html
		
maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning maintainer mode"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf ${AUTOMAKE_LIST}
