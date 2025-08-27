

if HAVESALOME
#
MESH_EXTENSION =med
CAD_EXTENSION =py
CAD_FOLDER=SALOME
MESHER=${salome}/salome
MESHER_PREFIX=-t -w1
#
else !HAVESALOME
#
MESH_EXTENSION =msh
CAD_EXTENSION =geo
CAD_FOLDER=Gmsh
MESHER=$(GMSH)
MESHER_PREFIX=-2 -format msh2 -v 0
#
endif


MESH_FILES  = \
./$(CAD_FOLDER)/bar.$(MESH_EXTENSION) \
./$(CAD_FOLDER)/bar_dynamic.$(MESH_EXTENSION)  \
./$(CAD_FOLDER)/city.$(MESH_EXTENSION)  \
./$(CAD_FOLDER)/L_shaped_crack.$(MESH_EXTENSION)  \
./$(CAD_FOLDER)/notched_plate.$(MESH_EXTENSION) \
./$(CAD_FOLDER)/quasistatic.$(MESH_EXTENSION)  \
./$(CAD_FOLDER)/quater_cylinder.$(MESH_EXTENSION) \
./$(CAD_FOLDER)/soil.$(MESH_EXTENSION) \
./$(CAD_FOLDER)/soil_dc.$(MESH_EXTENSION)  \
./$(CAD_FOLDER)/sparsity.$(MESH_EXTENSION) \
./$(CAD_FOLDER)/tensile_crack.$(MESH_EXTENSION)


CAD_FILES  = \
./$(CAD_FOLDER)/bar.$(CAD_EXTENSION) \
./$(CAD_FOLDER)/bar_dynamic.$(CAD_EXTENSION)  \
./$(CAD_FOLDER)/city.$(CAD_EXTENSION)  \
./$(CAD_FOLDER)/L_shaped_crack.$(CAD_EXTENSION)  \
./$(CAD_FOLDER)/notched_plate.$(CAD_EXTENSION) \
./$(CAD_FOLDER)/quasistatic.$(CAD_EXTENSION)  \
./$(CAD_FOLDER)/quater_cylinder.$(CAD_EXTENSION) \
./$(CAD_FOLDER)/soil.$(CAD_EXTENSION) \
./$(CAD_FOLDER)/soil_dc.$(CAD_EXTENSION)  \
./$(CAD_FOLDER)/sparsity.$(CAD_EXTENSION) \
./$(CAD_FOLDER)/tensile_crack.$(CAD_EXTENSION)


all-local: $(MESH_FILES)
	@echo ""
	@echo "*============================================================*"
	@echo " Creating 2D meshes in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " CAD file list: $(CAD_FILES)"


./$(CAD_FOLDER)/quater_cylinder.$(MESH_EXTENSION): ./$(CAD_FOLDER)/quater_cylinder.$(CAD_EXTENSION)
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/quater_cylinder.$(CAD_EXTENSION)
	@echo ""

./$(CAD_FOLDER)/bar.$(MESH_EXTENSION): ./$(CAD_FOLDER)/bar.$(CAD_EXTENSION)
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/bar.$(CAD_EXTENSION)
	@echo ""

./$(CAD_FOLDER)/bar_dynamic.$(MESH_EXTENSION): ./$(CAD_FOLDER)/bar_dynamic.$(CAD_EXTENSION)
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/bar_dynamic.$(CAD_EXTENSION)
	@echo ""

./$(CAD_FOLDER)/quasistatic.$(MESH_EXTENSION): ./$(CAD_FOLDER)/quasistatic.$(CAD_EXTENSION)
if HAVESALOME
else !HAVESALOME
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/quasistatic.$(CAD_EXTENSION)
endif
	@echo ""

./$(CAD_FOLDER)/notched_plate.$(MESH_EXTENSION): ./$(CAD_FOLDER)/notched_plate.$(CAD_EXTENSION)
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/notched_plate.$(CAD_EXTENSION)
	@echo ""

./$(CAD_FOLDER)/city.$(MESH_EXTENSION): ./$(CAD_FOLDER)/city.$(CAD_EXTENSION)
if HAVESALOME
else !HAVESALOME
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/city.$(CAD_EXTENSION)
endif
	@echo ""

./$(CAD_FOLDER)/L_shaped_crack.$(MESH_EXTENSION): ./$(CAD_FOLDER)/L_shaped_crack.$(CAD_EXTENSION)
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/L_shaped_crack.$(CAD_EXTENSION)
	@echo ""

./$(CAD_FOLDER)/sparsity.$(MESH_EXTENSION): ./$(CAD_FOLDER)/sparsity.$(CAD_EXTENSION)
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/sparsity.$(CAD_EXTENSION)
	@echo ""

./$(CAD_FOLDER)/soil_dc.$(MESH_EXTENSION): ./$(CAD_FOLDER)/soil_dc.$(CAD_EXTENSION)
if HAVESALOME
else !HAVESALOME
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/soil_dc.$(CAD_EXTENSION)
endif
	@echo ""

./$(CAD_FOLDER)/tensile_crack.$(MESH_EXTENSION): ./$(CAD_FOLDER)/tensile_crack.$(CAD_EXTENSION)
if !HAVESALOME
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/tensile_crack.$(CAD_EXTENSION)
	$(GMSH) ./$(CAD_FOLDER)/tensile_crack.$(MESH_EXTENSION)  -format msh2 -refine -v 0
	$(GMSH) ./$(CAD_FOLDER)/tensile_crack.$(MESH_EXTENSION)  -format msh2 -refine -v 0
	$(GMSH) ./$(CAD_FOLDER)/tensile_crack.$(MESH_EXTENSION)  -format msh2 -refine -v 0
	$(GMSH) ./$(CAD_FOLDER)/tensile_crack.$(MESH_EXTENSION)  -format msh2 -refine -v 0
endif
	@echo ""


./$(CAD_FOLDER)/soil.$(MESH_EXTENSION): ./$(CAD_FOLDER)/soil.$(CAD_EXTENSION)
	$(MESHER) $(MESHER_PREFIX) ./$(CAD_FOLDER)/soil.$(CAD_EXTENSION)
if !HAVESALOME
	$(GMSH) ./$(CAD_FOLDER)/soil.$(MESH_EXTENSION)  -format msh2 -refine -v 0
	$(GMSH) ./$(CAD_FOLDER)/soil.$(MESH_EXTENSION)  -format msh2 -refine -v 0
	$(GMSH) ./$(CAD_FOLDER)/soil.$(MESH_EXTENSION)  -format msh2 -refine -v 0
	$(GMSH) ./$(CAD_FOLDER)/soil.$(MESH_EXTENSION)  -format msh2 -refine -v 0
	$(GMSH) ./$(CAD_FOLDER)/soil.$(MESH_EXTENSION)  -format msh2 -refine -v 0
endif
	@echo ""


copy-to-meshes:
	@mkdir -p ../Meshes
	@ls $(CAD_FOLDER) | egrep "^soil_dc.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^soil.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "./$(CAD_FOLDER)/^bar.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^quasistatic.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^bar_dynamic.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^tensile_crack.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^sparsity.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^notched_plate.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^L_shaped_crack.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^city.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.
	@ls $(CAD_FOLDER) | egrep "^quater_cylinder.$(MESH_EXTENSION)" | xargs -I {} cp $(CAD_FOLDER)/{} ../Meshes/.

tutorials: copy-to-meshes

install-devel-local: copy-to-meshes

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm -rf *~  *./$(CAD_FOLDER)/.msh *./$(CAD_FOLDER)/.med
	rm -rf ../Meshes
	@echo ""


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
