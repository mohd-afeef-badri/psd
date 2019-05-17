LIST_COMPILE= bar.geo Notched-Plate.geo sparsity.geo tensile-crack.geo  bar-dynamic.geo  
	
all-local: bar.msh Notched-Plate.msh sparsity.msh tensile-crack.msh  bar-dynamic.msh  
	@echo "  			  "
	@echo " Finished Creating 2D meshes  !!!!!!"
	@echo "  			  "
	@echo "  			  "		
	@echo " Compilation list $(LIST_COMPILE)"
	@echo " gmsh used  $(GMSH)"

bar.msh:
	$(GMSH) -2 bar.geo -o bar.msh -format msh2 -v 0

bar-dynamic.msh:
	$(GMSH) -2 bar-dynamic.geo -o bar-dynamic.msh -format msh2 -v 0
	
Notched-Plate.msh:
	$(GMSH) -2 Notched-Plate.geo -o Notched-Plate.msh -format msh2 -v 0

tensile-crack.msh:
	$(GMSH) -2 tensile-crack.geo -o tensile-crack.msh -format msh2 -v 0

sparsity.msh:
	$(GMSH) -2  sparsity.geo -o sparsity.msh -format msh2 -v 0				

install-exec-local:
	@mkdir -p ../Meshes
	@ls | egrep "^bar.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^bar-dynamic.msh" | xargs -I {} mv {} ../Meshes/.	
	@ls | egrep "^tensile-crack.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^sparsity.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^Notched-Plate.msh" | xargs -I {} mv {} ../Meshes/.		
#	@mv bar.msh ../Meshes/bar.msh
#	@mv Notched-Plate.msh ../Meshes/Notched-Plate.msh	
#	@mv sparsity.msh ../Meshes/sparsity.msh	
#	@mv tensile-crack.msh ../Meshes/tensile-crack.msh	

clean-local:
	@echo "  			  "
	@echo "  			  "
	@echo " Removing useless files ......."
	@echo "  			  "
	@echo "  			  "
	rm  -f *~  *.msh
	rm -rf ../Meshes
	@echo "  			  "
	@echo "  			  "
	@echo " Finished removing !!!!!!!!"
	@echo "  			  "		
