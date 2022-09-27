LIST_COMPILE= bar.geo  tensile_crack.geo  bar_dynamic.geo quasistatic.geo  soil.geo L_shape.geo
MESH_FILES  = bar.msh tensile_crack.msh bar_dynamic.msh  quasistatic.msh  soil.msh L_shape.msh

all-local: $(MESH_FILES)
	@echo ""
	@echo "*============================================================*"
	@echo " Creating 3D meshes in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Mesh geo list: $(LIST_COMPILE)"

tensile_crack.msh: tensile_crack.geo
	$(GMSH) -3  tensile_crack.geo -o tensile_crack.msh -format msh2 -v 0
	@echo ""

quasistatic.msh: quasistatic.geo
	$(GMSH) -3 quasistatic.geo -o quasistatic.msh -format msh2 -v 0
	@echo ""

bar.msh: bar.geo
	$(GMSH) -3 bar.geo -o bar.msh -format msh2 -v 0
	@echo ""

L_shape.msh: L_shape.geo
	$(GMSH) -3 L_shape.geo -o L_shape.msh -format msh2 -v 0
	@echo ""

bar_dynamic.msh: bar_dynamic.geo
	$(GMSH) -3 bar_dynamic.geo -o bar-dynamic.msh -format msh2 -v 0
	@echo ""

soil.msh: soil.geo
	$(GMSH) -3 soil.geo -o soil.msh -format msh2 -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0
	$(GMSH) -1 soil.msh -o soil.msh -format msh2 -refine -v 0
	@echo ""

copy-to-meshes:
	@mkdir -p ../Meshes
	@ls | egrep "^soil.msh" | xargs -I {} cp {} ../Meshes/.
	@ls | egrep "^bar.msh" | xargs -I {} cp {} ../Meshes/.
	@ls | egrep "^L_shape.msh" | xargs -I {} cp {} ../Meshes/.
	@ls | egrep "^quasistatic.msh" | xargs -I {} cp {} ../Meshes/.
	@ls | egrep "^bar_dynamic.msh" | xargs -I {} cp {} ../Meshes/.
	@ls | egrep "^tensile_crack.msh" | xargs -I {} cp {} ../Meshes/.

tutorials: copy-to-meshes


install-devel-local: copy-to-meshes

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm -f *~ *.msh *.med
	rm -rf ../Meshes
	@echo ""

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
