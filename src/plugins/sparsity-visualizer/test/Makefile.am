LIST_COMPILE= Test_1.edp \
Test_2.edp

all-local: 
	@echo ""
	
check-local: check-header Test_1 Test_2
	@echo ""
	@echo "*============================================================*"
	@echo " Checking sparisity-visualizer plugin : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking sparisity-visualizer plugin : RUNNING                      "
	@echo "*============================================================*"
	@echo ""
	
Test_1: Test_1.edp
	@echo "Test_1 : sparisity-visualizer load test"
	@./../../../psd-solve/PSD_Solve -np 1 Test_1.edp >  Test_1.log
	@echo "  PASSED "

Test_2: Test_2.edp
	@echo "Test_2 : sparisity-visualizer testing matrix visulization of Laplace operator"
	@./../../../psd-solve/PSD_Solve -np 1 Test_2.edp >  Test_2.log
	@echo "  PASSED "	

			
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log	
	

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
