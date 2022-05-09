SHELL := /usr/bin/zsh

preprocess-varf-based:	
	PSD_PreProcess -problem linear_elasticity -dimension 2 -getreactionforce -reactionforce variational_based \
	-dirichletconditions 1 -bodyforceconditions 1  -useMfront&& \
	find . -name ControlParameters.edp -exec sed -i -e "s#  macro E()  200.e9#  real  L = 5., H = 1.;\n  macro E()  1.e5  #g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0On 2  #macro  Dbc0On 4#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0On 1#real fx = 0.1;\n  real fy = -1.; \n  macro  Fbc0On 0#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0Fy -78480.0#macro  Fbc0Fx fx //\n  macro  Fbc0Fy fy#g" {} \; && \
	find . -name MeshAndFeSpace.edp -exec sed -i -e "s#loadfemesh(Th,ThName);#Th = square(100, 20, [L*x,H*y],flags=2);#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#endProcedure(\"force calculation\",t0);#endProcedure(\"force calculation\",t0);\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Analytic vertical reaction Ry      :: \"   << -L*H*fy << endl;\n  cout << \"Analytic horizontal reaction Rx    :: \"   <<  -L*H*fx << endl;\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Error vertical reaction Ry      :: \"   << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;\n  cout << \"Error horizontal reaction Rx    :: \"   <<  (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl;\n\n  ofstream ee(\"psd-varf-based-err.data\");\n  ee << \" 0 \\t E(f(x)) \\t\" << (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl; \n  ee << \" 1 \\t E(f(y)) \\t\" << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;#g" {} \;


preprocess-varf-based-pseudo_nonlinear:	
	PSD_PreProcess -problem linear_elasticity -dimension 2 -getreactionforce -reactionforce variational_based \
	-dirichletconditions 1 -bodyforceconditions 1  -useMfront -model pseudo_nonlinear && \
	find . -name ControlParameters.edp -exec sed -i -e "s#  macro E()  200.e9#  real  L = 5., H = 1.;\n  macro E()  1.e5  #g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0On 2  #macro  Dbc0On 4#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0On 1#real fx = 0.1;\n  real fy = -1.; \n  macro  Fbc0On 0#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0Fy -78480.0#macro  Fbc0Fx fx //\n  macro  Fbc0Fy fy#g" {} \; && \
	find . -name MeshAndFeSpace.edp -exec sed -i -e "s#loadfemesh(Th,ThName);#Th = square(100, 20, [L*x,H*y],flags=2);#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#endProcedure(\"force calculation\",t0);#endProcedure(\"force calculation\",t0);\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Analytic vertical reaction Ry      :: \"   << -L*H*fy << endl;\n  cout << \"Analytic horizontal reaction Rx    :: \"   <<  -L*H*fx << endl;\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Error vertical reaction Ry      :: \"   << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;\n  cout << \"Error horizontal reaction Rx    :: \"   <<  (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl;\n\n  ofstream ee(\"psd-varf-based-err-pseudo-nonlinear.data\");\n  ee << \" 0 \\t E(f(x)) \\t\" << (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl; \n  ee << \" 1 \\t E(f(y)) \\t\" << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;#g" {} \;


preprocess-stress-based:	
	PSD_PreProcess -problem linear_elasticity -dimension 2 -getreactionforce -reactionforce stress_based \
	-dirichletconditions 1 -bodyforceconditions 1 -useMfront && \
	find . -name ControlParameters.edp -exec sed -i -e "s#  macro E()  200.e9#  real  L = 5., H = 1.;\n  macro E()  1.e5  #g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0On 2  #macro  Dbc0On 4#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0On 1#real fx = 0.1;\n  real fy = -1.; \n  macro  Fbc0On 0#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0Fy -78480.0#macro  Fbc0Fx fx //\n  macro  Fbc0Fy fy#g" {} \; && \
	find . -name MeshAndFeSpace.edp -exec sed -i -e "s#loadfemesh(Th,ThName);#Th = square(100, 20, [L*x,H*y],flags=2);#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#lambda#(E*nu/((1.+nu)*(1.-2.*nu)))#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#mu#(E/(2.*(1.+nu)) )#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#endProcedure(\"force calculation\",t0);#endProcedure(\"force calculation\",t0);\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Analytic vertical reaction Ry      :: \"   << -L*H*fy << endl;\n  cout << \"Analytic horizontal reaction Rx    :: \"   <<  -L*H*fx << endl;\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Error vertical reaction Ry      :: \"   << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;\n  cout << \"Error horizontal reaction Rx    :: \"   <<  (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl;\n\n  ofstream ee(\"psd-stress-based-err.data\");\n  ee << \" 0 \\t E(f(x)) \\t\" << (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl; \n  ee << \" 1 \\t E(f(y)) \\t\" << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;#g" {} \;

preprocess-stress-based-pseudo_nonlinear:	
	PSD_PreProcess -problem linear_elasticity -dimension 2 -getreactionforce -reactionforce stress_based \
	-dirichletconditions 1 -bodyforceconditions 1 -useMfront -model pseudo_nonlinear && \
	find . -name ControlParameters.edp -exec sed -i -e "s#  macro E()  200.e9#  real  L = 5., H = 1.;\n  macro E()  1.e5  #g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Dbc0On 2  #macro  Dbc0On 4#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0On 1#real fx = 0.1;\n  real fy = -1.; \n  macro  Fbc0On 0#g" {} \; && \
	find . -name ControlParameters.edp -exec sed -i -e "s#macro  Fbc0Fy -78480.0#macro  Fbc0Fx fx //\n  macro  Fbc0Fy fy#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#def(Sigx) =#def(Sigx) = [Sig11,Sig12/sqrt(2.)];/*#g" {} \; && \
	find . -name MeshAndFeSpace.edp -exec sed -i -e "s#loadfemesh(Th,ThName);#Th = square(100, 20, [L*x,H*y],flags=2);#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#Sigma_xy#Sigma_xy*/#g" {} \; && \
	find . -name LinearFormBuilderAndSolver.edp -exec sed -i -e "s#endProcedure(\"force calculation\",t0);#endProcedure(\"force calculation\",t0);\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Analytic vertical reaction Ry      :: \"   << -L*H*fy << endl;\n  cout << \"Analytic horizontal reaction Rx    :: \"   <<  -L*H*fx << endl;\n\n  cout << \" ----------------------------------\"   << endl;\n  cout << \"Error vertical reaction Ry      :: \"   << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;\n  cout << \"Error horizontal reaction Rx    :: \"   <<  (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl;\n\n  ofstream ee(\"psd-stress-based-err-pseudo-nonlinear.data\");\n  ee << \" 0 \\t E(f(x)) \\t\" << (abs(forcetotx - (-L*H*fx)))/abs(L*H*fx)*100 << endl; \n  ee << \" 1 \\t E(f(y)) \\t\" << (abs(forcetoty - (-L*H*fy)))/abs(L*H*fy)*100 << endl;#g" {} \;

solve:	
	PSD_Solve -np 1 Main.edp  -v 0 -split 4
	
gnuplot:
	gnuplot  gnuplot.gnu -p		

run:
	make  preprocess-stress-based && make solve
	make  preprocess-varf-based && make solve
	make  preprocess-stress-based-pseudo_nonlinear && make solve
	make  preprocess-varf-based-pseudo_nonlinear && make solve
	make gnuplot

mfront:
	source /home/mb258512/PSDInstall/mfront-env.sh

clean:
	@rm -rf *.edp *.csv *.data *.eps
