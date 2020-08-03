LIST_COMPILE= bar.geo  tensile-crack.geo  bar-dynamic.geo quasistatic.geo  soil.geo 
MESH_FILES  = bar.msh tensile-crack.msh bar-dynamic.msh  quasistatic.msh  soil.msh  
	
all-local: $(MESH_FILES) 
	@echo ""
	@echo "*============================================================*"
	@echo " Creating 3D meshes in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	@echo " Mesh geo list: $(LIST_COMPILE)"

tensile-crack.msh: tensile-crack.geo
	$(GMSH) -3  tensile-crack.geo -o tensile-crack.msh -format msh2 -v 0
	@echo ""		
	
quasistatic.msh: quasistatic.geo
	$(GMSH) -3 quasistatic.geo -o quasistatic.msh -format msh2 -v 0	
	@echo ""		

bar.msh: bar.geo
	$(GMSH) -3 bar.geo -o bar.msh -format msh2 -v 0
	@echo ""		

bar-dynamic.msh: bar-dynamic.geo
	$(GMSH) -3 bar-dynamic.geo -o bar-dynamic.msh -format msh2 -v 0
	@echo ""		

soil.msh: soil.geo
	$(GMSH) -3 soil.geo -o soil.msh -format msh2 -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0		
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0
	@echo ""				

install-exec-local:
	@mkdir -p ../Meshes
	@ls | egrep "^soil.msh" | xargs -I {} cp {} ../Meshes/.		
	@ls | egrep "^bar.msh" | xargs -I {} cp {} ../Meshes/.
	@ls | egrep "^quasistatic.msh" | xargs -I {} cp {} ../Meshes/.		
	@ls | egrep "^bar-dynamic.msh" | xargs -I {} cp {} ../Meshes/.	
	@ls | egrep "^tensile-crack.msh" | xargs -I {} cp {} ../Meshes/.

install-devel-local:
	@mkdir -p ../Meshes
	@ls | egrep "^soil.msh" | xargs -I {} cp {} ../Meshes/.		
	@ls | egrep "^bar.msh" | xargs -I {} cp {} ../Meshes/.
	@ls | egrep "^quasistatic.msh" | xargs -I {} cp {} ../Meshes/.		
	@ls | egrep "^bar-dynamic.msh" | xargs -I {} cp {} ../Meshes/.	
	@ls | egrep "^tensile-crack.msh" | xargs -I {} cp {} ../Meshes/.
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm -f *~ *.msh
	rm -rf ../Meshes
	@echo ""

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
