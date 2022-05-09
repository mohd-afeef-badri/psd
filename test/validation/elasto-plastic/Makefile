SHELL := /usr/bin/zsh

preprocess:	
	/home/mb258512/PSDInstall/bin/PSD_PreProcess -problem elasto_plastic -model von_mises -dimension 2 \
	-tractionconditions 1 -dirichletconditions 2 -useMfront && \
	find . -name ControlParameters.edp -exec sed -i -e "s#Dbc0On 2#Dbc0On 1#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0Ux#//macro  Dbc0Ux 0.#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#Dbc1On 2#Dbc1On 3#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc1Uy#//macro  Dbc1Uy#g" {} \; && \
	find . -name OtherParameters.edp -exec sed -i -e "s# real nRes, nRes0;# real nRes, nRes0;\n if(mpirank==0)\n  ofstream rr(\"result.data\");#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#  //------------------Screen output ----------------------//#  //------------------Screen output ----------------------//\n  if(mpirank==0) rr << u(Ri,0) << \"\\\t\" << tl <<endl;#g" {} \; && \

solve:	
	/home/mb258512/PSDInstall/bin/PSD_Solve -np 4 Main.edp -mesh ./../../../data/meshes/2D/Geo-Files/quater_cylinder.msh -v 0

gnuplot:
	gnuplot gnuplot-compare.gnu -p	

run: preprocess solve gnuplot

clean:
	@rm -rf *.edp *.data *.csv *.eps
