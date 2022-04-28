SHELL := /usr/bin/zsh

preprocess-plain-stress:	
	/home/mb258512/PSDInstall/bin/PSD_PreProcess -problem linear_elasticity -dimension 2 \
	-dirichletconditions 1 -postprocess u -bodyforceconditions 1 && \
	find . -name ControlParameters.edp -exec sed -i -e "s#,lambda;#,lambda, E, nu, L = 25., H = 1.;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#real E  = 200.e9  ,#     E  = 1.e5    ;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#nu)) ;#nu)) ;\n  lambda = 2*mu*lambda/(lambda+2*mu) ;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0On 2  #macro  Dbc0On 444#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0On 1#real   Rhog = 1.e-3;\n  macro  Fbc0On 0#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0Fy -78480.0#macro  Fbc0Fy -Rhog#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#endProcedure(\"Paraview Postprocess\",t0);#endProcedure(\"Paraview Postprocess\",t0);\n\n  cout << \"Max deflection Uy \"       << -u1(L,H/2.) << endl;\n  cout << \"Analytical Max deflection Uy \"   <<  (3*Rhog*(L^4))/(2*E*H^3) << endl;\n\n  ifstream rr(\"ref-plain-stress.data\");\n  ofstream ww(\"psd-plain-stress.data\");\n  for(int i=0; i<251; i++){\n    real Yin, Uyin; rr >> Yin >> Uyin;\n    ww << Yin <<\"\\t\"<< u1(Yin,H/2.) <<endl;}#g" {} \;


solve-plain-stress:	
	/home/mb258512/PSDInstall/bin/PSD_Solve -np 1 Main.edp -mesh bar.mesh -v 0



preprocess-plain-strain:	
	/home/mb258512/PSDInstall/bin/PSD_PreProcess -problem linear_elasticity -dimension 2 \
	-dirichletconditions 1 -postprocess u -bodyforceconditions 1 && \
	find . -name ControlParameters.edp -exec sed -i -e "s#,lambda;#,lambda, E, nu, L = 25., H = 1.;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#real E  = 200.e9  ,#     E  = 1.e5    ;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0On 2  #macro  Dbc0On 444#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0On 1#real   Rhog = 1.e-3;\n  macro  Fbc0On 0#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0Fy -78480.0#macro  Fbc0Fy -Rhog#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#endProcedure(\"Paraview Postprocess\",t0);#endProcedure(\"Paraview Postprocess\",t0);\n\n  cout << \"Max deflection Uy \"       << -u1(L,H/2.) << endl;\n  cout << \"Analytical Max deflection Uy \"   <<  (3*Rhog*(L^4))/(2*E*H^3) << endl;\n\n  ifstream rr(\"ref-plain-strain.data\");\n  ofstream ww(\"psd-plain-strain.data\");\n  for(int i=0; i<1001; i++){\n    real Yin, Uyin; rr >> Yin >> Uyin;\n    ww << Yin <<\"\\t\"<< u1(Yin,H/2.) <<endl;}#g" {} \;


solve-plain-strain:	
	/home/mb258512/PSDInstall/bin/PSD_Solve -np 1 Main.edp -mesh bar.mesh -v 0


gnuplot:
	gnuplot gnuplot-compare-plain-stress.gnu -p  ; \
	gnuplot gnuplot-compare-plain-strain.gnu -p	

run: preprocess solve gnuplot

mfront:
	source /home/mb258512/PSDInstall/mfront-env.sh

clean:
	@rm -rf VTUs* *.edp result* *.csv
