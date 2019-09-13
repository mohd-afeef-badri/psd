LIST_COMPILE= bar.geo  tensile-crack.geo  bar-dynamic.geo quasistatic.geo   
	
all-local: bar.msh tensile-crack.msh bar-dynamic.msh  quasistatic.msh  
	@echo "  			  "
	@echo " Finished Creating 3D meshes  !!!!!!"
	@echo "  			  "
	@echo "  			  "		
	@echo " Compilation list $(LIST_COMPILE)"
	@echo " gmsh used  $(GMSH)"

tensile-crack.msh:
	$(GMSH) -3  tensile-crack.geo -o tensile-crack.msh -format msh2 -v 0
	
quasistatic.msh:
	$(GMSH) -3 quasistatic.geo -o quasistatic.msh -format msh2 -v 0	

bar.msh:
	$(GMSH) -3 bar.geo -o bar.msh -format msh2 -v 0

bar-dynamic.msh:
	$(GMSH) -3 bar-dynamic.geo -o bar-dynamic.msh -format msh2 -v 0	

install-exec-local:
	@mkdir -p ../Meshes
	@ls | egrep "^bar.msh" | xargs -I {} mv {} ../Meshes/.
	@ls | egrep "^quasistatic.msh" | xargs -I {} mv {} ../Meshes/.		
	@ls | egrep "^bar-dynamic.msh" | xargs -I {} mv {} ../Meshes/.	
	@ls | egrep "^tensile-crack.msh" | xargs -I {} mv {} ../Meshes/.
	
clean-local:
	@echo "  			  "
	@echo "  			  "
	@echo " Removing mesh files ......"
	@echo "  			  "
	@echo "  			  "
	rm -f *~ *.msh
	rm -rf ../Meshes
	@echo "  			  "		
