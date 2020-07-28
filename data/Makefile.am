SUBDIRS=meshes/2D/Geo-Files meshes/3D/Geo-Files
EXTRA_DIST=   	      \
./meshes/2D/Geo-Files/bar.geo \
./meshes/2D/Geo-Files/bar-dynamic.geo \
./meshes/2D/Geo-Files/Notched-Plate.geo \
./meshes/2D/Geo-Files/sparsity.geo\
./meshes/2D/Geo-Files/tensile-crack.geo\
./meshes/3D/Geo-Files/bar.geo\
./meshes/3D/Geo-Files/tensile-crack.geo\
./meshes/3D/Geo-Files/bar-dynamic.geo

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ 
	@echo ""

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in

