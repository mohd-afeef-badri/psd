LIST_COMPILE= Test_1.edp \
Test_2.edp \
Test_3.edp


all-local: 
	@echo ""
	
check-local: check-header Test_1 Test_2 Test_3
	@echo ""
	@echo "*============================================================*"
	@echo " Checking gofastplugins plugin : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking gofastplugins plugin : RUNNING                      "
	@echo "*============================================================*"
	@echo ""
	
Test_1: Test_1.edp
	@echo "Test_1 : gofastplugins load test"
	@./../../../psd-solve/PSD_Solve -n 1 Test_1.edp -v 10 >  Test_1.log
	@echo "  PASSED "

Test_2: Test_2.edp
	@echo "Test_2 : gofastplugins GFPeigenAlone test"
	@./../../../psd-solve/PSD_Solve -n 1 Test_2.edp >  Test_2.log
	@echo "  PASSED "	

Test_3: Test_3.edp
	@echo "Test_3 : gofastplugins GFPeigen test"
	@./../../../psd-solve/PSD_Solve -n 1 Test_3.edp >  Test_3.log
	@echo "  PASSED "
			
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log	
	

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
