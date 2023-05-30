SHELL := /usr/bin/zsh

preprocess-stress-based:
	PSD_PreProcess -problem damage -model hybrid_phase_field -dimension 2 \
	-dirichletconditions 2 -getreactionforce -reactionforce stress_based   -crackdirichletcondition && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#ofstream ff(\"force.data\",append);#ofstream ff(\"force-stress.data\",append);#g" {} \;


solve-stress-based:
	PSD_Solve -np 1 Main.edp -mesh ./../../../data/meshes/2D/Geo-Files/Gmsh/tensile_crack.msh -split 22 -v 0


run-stress-based: preprocess-stress-based  solve-stress-based

preprocess-varf-based:
	PSD_PreProcess -problem damage -model hybrid_phase_field -dimension 2 \
	-dirichletconditions 2 -getreactionforce -reactionforce variational_based  -crackdirichletcondition && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#ofstream ff(\"force.data\",append);#ofstream ff(\"force-varf.data\",append);#g" {} \;

solve-varf-based:
	PSD_Solve -np 1 Main.edp -mesh ./../../../data/meshes/2D/Geo-Files/Gmsh/tensile_crack.msh -split 22 -v 0

run-varf-based: preprocess-varf-based  solve-varf-based

gnuplot:
	gnuplot gnuplot-compare.gnu -p

run: preprocess-stress-based  solve-stress-based preprocess-varf-based  solve-varf-based gnuplot

clean:
	@rm -rf  *.edp  *.csv
