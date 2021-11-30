
all-local:
	@echo ""

check-local: check-header check-elasto-plastic-Mfront
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Elasto Plasticity : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@cp ./../../src/psd-solve/PSD_Solve ./PSD_Solve
	@cp ./../../src/psd-solve/PSD_Solve_Seq ./PSD_Solve_Seq
	@cp ./../../src/psd-preprocessor/PSD_PreProcess ./PSD_PreProcess
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Linear Elasticity : RUNNING                      "
	@echo "*============================================================*"
	@echo ""

NP = 4

check-elasto-plastic-Mfront:
	@echo ""
	@echo "*============================================================*"
	@echo " Parallel 2D elasto-plasticity with mfront "
	@echo "*============================================================*"
	@echo ""
	./PSD_PreProcess -dimension 2 -tractionconditions 1 -problem elasto_plastic -dirichletconditions 2 -model von_mises -useMfront -testflags  > PSD_PreProcess-2D_elasto-plasticity_Parallel_Mfornt.log && \
	find -name ControlParameters.edp -exec sed -i "s#../Meshes/2D/#./../../data/meshes/2D/Geo-Files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#../Plugins/#./../ff-files/#g" {} \; && \
	find -name Main.edp -exec sed -i "s#mfront#./../../src/plugins/mfront/cpp/mfront#g" {} \; && \
	./PSD_Solve -np $(NP)  Main.edp -v 0 -ns -nw > PSD_PreProcess-2D_elasto-plasticity_Parallel_Mfornt.log

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log *.edp PSD_Solve PSD_PreProcess PSD_Solve_Seq


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
