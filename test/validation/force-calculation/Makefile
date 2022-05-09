SHELL := /usr/bin/zsh

preprocess-stress-based:	
	PSD_PreProcess -problem linear_elasticity -dimension 2 -getreactionforce -reactionforce stress_based \
	-dirichletconditions 1 -bodyforceconditions 1 && \
	find . -name ControlParameters.edp -exec sed -i -e "s#,lambda;#,lambda, E, nu, L = 5., H = 1.;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#real E  = 200.e9  ,#     E  = 1.e5    ;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0On 2  #macro  Dbc0On 444#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0On 1#real fx = 0.1;\n  real fy = -1.; \n  macro  Fbc0On 0#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0Fy -78480.0#macro  Fbc0Fx fx //\n  macro  Fbc0Fy fy#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#endProcedure(\"force calculation\",t0);#endProcedure(\"force calculation\",t0);\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Analytic vertical reaction Ry      :: \"   << -L*H*fy << endl;\n  cout << \"Analytic horizontal reaction Rx    :: \"   <<  -L*H*fx << endl;\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Error vertical reaction Ry      :: \"   << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;\n  cout << \"Error horizontal reaction Rx    :: \"   <<  (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl;\n\n  ofstream ee(\"psd-stress-based-err.data\");\n  ee << \" 0 \\t Errx \\t\" << (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl; \n  ee << \" 1 \\t Erry \\t\" << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;#g" {} \;


solve-stress-based:	
	PSD_Solve -np 1 Main.edp -mesh cantilever-beam.mesh -v 0 -split 4

preprocess-varf-based:	
	PSD_PreProcess -problem linear_elasticity -dimension 2 -getreactionforce -reactionforce variational_based \
	-dirichletconditions 1 -bodyforceconditions 1 && \
	find . -name ControlParameters.edp -exec sed -i -e "s#,lambda;#,lambda, E, nu, L = 5., H = 1.;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#real E  = 200.e9  ,#     E  = 1.e5    ;#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0On 2  #macro  Dbc0On 444#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0On 1#real fx = 0.1;\n  real fy = -1.; \n  macro  Fbc0On 0#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0Fy -78480.0#macro  Fbc0Fx fx //\n  macro  Fbc0Fy fy#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#endProcedure(\"force calculation\",t0);#endProcedure(\"force calculation\",t0);\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Analytic vertical reaction Ry      :: \"   << -L*H*fy << endl;\n  cout << \"Analytic horizontal reaction Rx    :: \"   <<  -L*H*fx << endl;\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Error vertical reaction Ry      :: \"   << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;\n  cout << \"Error horizontal reaction Rx    :: \"   <<  (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl;\n\n  ofstream ee(\"psd-varf-based-err.data\");\n  ee << \" 0 \\t Errx \\t\" << (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl; \n  ee << \" 1 \\t Erry \\t\" << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;#g" {} \;


solve-varf-based:	
	PSD_Solve -np 1 Main.edp -mesh cantilever-beam.mesh -v 0 -split 4

gnuplot:
	gnuplot gnuplot-compare-stress-based.gnu -p  ; \
	gnuplot gnuplot-compare-varf-based.gnu -p	

run: preprocess-stress-based solve-stress-based preprocess-varf-based solve-varf-based gnuplot

mfront:
	source /home/mb258512/PSDInstall/mfront-env.sh

clean:
	@rm -rf *.edp *.csv *.data *.eps
