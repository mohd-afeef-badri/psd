LIST_COMPILE= Test_1.edp \
Test_2.edp

all-local: 
	@echo ""
	
check-local: check-header Test_1 Test_2
	@echo ""
	@echo "*============================================================*"
	@echo " Checking soil-laws plugin : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking soil-laws plugin : RUNNING                      "
	@echo "*============================================================*"
	@echo ""
	
Test_1: Test_1.edp
	@echo "Test_1 : soil-laws load test"
	@./../../../psd-solve/PSD_Solve -n 1 Test_1.edp >  Test_1.log
	@./../../../psd-solve/PSD_Solve -n 2 Test_1.edp >  Test_1_NP2.log
	@echo "  PASSED "

Test_2: Test_2.edp
	@echo "Test_2 : soil-laws testing PSDHujeuxSoilLaw routiner"
	@./../../../psd-solve/PSD_Solve -n 1 Test_2.edp >  Test_2.log
	@./../../../psd-solve/PSD_Solve -n 2 Test_2.edp >  Test_2_NP2.log
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
