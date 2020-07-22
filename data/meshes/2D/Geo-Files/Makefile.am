LIST_COMPILE= bar.geo Notched-Plate.geo sparsity.geo tensile-crack.geo  bar-dynamic.geo  quasistatic.geo  soil.geo soil-dc.geo
MESH_FILES  = bar.msh Notched-Plate.msh sparsity.msh tensile-crack.msh  bar-dynamic.msh  quasistatic.msh  soil.msh soil-dc.msh 
	
all-local: $(MESH_FILES) 
	@echo ""
	@echo "*============================================================*"
	@echo " Creating 2D meshes in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	@echo " Mesh geo list: $(LIST_COMPILE)"

bar.msh: bar.geo
	$(GMSH) -2 bar.geo -o bar.msh -format msh2 -v 0
	@echo ""	
		
quasistatic.msh: quasistatic.geo
	$(GMSH) -2 quasistatic.geo -o quasistatic.msh -format msh2 -v 0
	@echo ""		
	
bar-dynamic.msh: bar-dynamic.geo
	$(GMSH) -2 bar-dynamic.geo -o bar-dynamic.msh -format msh2 -v 0
	@echo ""		
	
Notched-Plate.msh: Notched-Plate.geo
	$(GMSH) -2 Notched-Plate.geo -o Notched-Plate.msh -format msh2 -v 0
	@echo ""		

tensile-crack.msh: tensile-crack.geo
	$(GMSH) -2 tensile-crack.geo -o tensile-crack.msh -format msh2 -v 0
	$(GMSH) -1 tensile-crack.msh -o tensile-crack.msh -format msh2 -refine -v 0
	$(GMSH) -1 tensile-crack.msh -o tensile-crack.msh -format msh2 -refine -v 0		
	$(GMSH) -1 tensile-crack.msh -o tensile-crack.msh -format msh2 -refine -v 0
	@echo ""		

sparsity.msh: sparsity.geo
	$(GMSH) -2  sparsity.geo -o sparsity.msh -format msh2 -v 0
	@echo ""						

soil.msh: soil.geo
	$(GMSH) -2 soil.geo -o soil.msh -format msh2 -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0		
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0	
	@echo ""

soil-dc.msh: soil-dc.geo			
	$(GMSH) -2 soil-dc.geo -o soil-dc.msh -format msh2 -v 0	
	@echo ""
	
install-exec-local:
	@mkdir -p ../Meshes
	@ls | egrep "^soil-dc.msh" | xargs -I {} mv {} ../Meshes/.		
	@ls | egrep "^soil.msh" | xargs -I {} mv {} ../Meshes/.	
	@ls | egrep "^bar.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^quasistatic.msh" | xargs -I {} mv {} ../Meshes/.	
	@ls | egrep "^bar-dynamic.msh" | xargs -I {} mv {} ../Meshes/.	
	@ls | egrep "^tensile-crack.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^sparsity.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^Notched-Plate.msh" | xargs -I {} mv {} ../Meshes/.		
	
install-devel-local:
	@mkdir -p ../Meshes
	@ls | egrep "^soil-dc.msh" | xargs -I {} mv {} ../Meshes/.		
	@ls | egrep "^soil.msh" | xargs -I {} mv {} ../Meshes/.	
	@ls | egrep "^bar.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^quasistatic.msh" | xargs -I {} mv {} ../Meshes/.	
	@ls | egrep "^bar-dynamic.msh" | xargs -I {} mv {} ../Meshes/.	
	@ls | egrep "^tensile-crack.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^sparsity.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^Notched-Plate.msh" | xargs -I {} mv {} ../Meshes/.
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.msh
	rm -rf ../Meshes
	@echo ""
