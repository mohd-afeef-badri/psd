LIST_COMPILE= bar.geo  tensile-crack.geo   
	
all-local: bar.msh tensile-crack.msh   
	@echo "  			  "
	@echo " Finished Creating 3D meshes  !!!!!!"
	@echo "  			  "
	@echo "  			  "		
	@echo " Comilation list $(LIST_COMPILE)"
	@echo " gmsh used  $(GMSH)"

tensile-crack.msh:
	$(GMSH) -3  tensile-crack.geo -o tensile-crack.msh -format msh2 -v 0

bar.msh:
	$(GMSH) -3 bar.geo -o bar.msh -format msh2 -v 0

install-exec-local:
	@mkdir -p ../Meshes
	@ls | egrep "^bar.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^tensile-crack.msh" | xargs -I {} mv {} ../Meshes/.	
#	@mv bar.msh ../Meshes/bar.msh
#	@mv tensile-crack.msh ../Meshes/tensile-crack.msh
	
clean-local:
	@echo "  			  "
	@echo "  			  "
	@echo " Removing useless files ......."
	@echo "  			  "
	@echo "  			  "
	rm -f *~ *.msh
	rm -rf ../Meshes
	@echo "  			  "
	@echo "  			  "
	@echo " Finished removing !!!!!!!!"
	@echo "  			  "
	@echo "  			  "		
