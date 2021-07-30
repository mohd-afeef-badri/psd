	
all-local: 
	@echo ""
	
check-local: check-header Test_1 Test_2 Test_3 Test_4 Test_5 Test_6
	@echo ""
	@echo "*============================================================*"
	@echo " Checking top-ii-vol plugin : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""

check-header:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking top-ii-vol plugin : RUNNING                      "
	@echo "*============================================================*"
	@echo ""
	
Test_1: Test_1.edp
	@echo "Test_1 : top-ii-vol load test"
	@./../../../psd-solve/PSD_Solve -np 1 Test_1.edp >  Test_1.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_1.edp >  Test_1_NP2.log	
	@echo "  PASSED "

Test_2: Test_2.edp
	@echo "Test_2 :  top-ii-vol testing point-cloud  partitioning"
	@./../../../psd-solve/PSD_Solve -np 2 Test_2.edp >  Test_2.log		
	@echo "  PASSED "	

Test_3: Test_3.edp
	@echo "Test_3 :  top-ii-vol testing point-cloud meshing and partitioning"
	@./../../../psd-solve/PSD_Solve -np 2 Test_3.edp >  Test_3.log		
	@echo "  PASSED "

Test_4: Test_4.edp
	@echo "Test_4 :  top-ii-vol testing point-cloud meshing and X-partitioning"
	@./../../../psd-solve/PSD_Solve -np 2 Test_4.edp >  Test_4.log		
	@echo "  PASSED "

Test_5: Test_5.edp
	@echo "Test_5 :  top-ii-vol testing point-cloud meshing and Y-partitioning"
	@./../../../psd-solve/PSD_Solve -np 2 Test_5.edp >  Test_5.log		
	@echo "  PASSED "
	
Test_6: Test_6.edp
	@echo "Test_6 :  top-ii-vol testing point-cloud meshing and Z-partitioning"
	@./../../../psd-solve/PSD_Solve -np 2 Test_6.edp >  Test_6.log		
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
