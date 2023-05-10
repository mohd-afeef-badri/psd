LIST_COMPILE= Test_1 \
Test_2 \
Test_3 \
Test_4 \
Test_5 \
Test_6 \
Test_7 \
Test_8 \
Test_PrintStats

all-local:
	@echo ""

if HAVEMGIS
check-local: check-header $(LIST_COMPILE)
	@echo ""
	@echo "*============================================================*"
	@echo " Checking mfront plugin : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""
else !HAVEMGIS
check-local: check-header
	@echo ""
	@echo "*============================================================*"
	@echo " Skipping mfront plugin test                     "
	@echo "*============================================================*"
	@echo ""
endif
check-header:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking mfront plugin : RUNNING                      "
	@echo "*============================================================*"
	@echo ""

Test_1: Test_1.edp
	@echo "Test_1 : mfront load test"
	@./../../../psd-solve/PSD_Solve -np 1 Test_1.edp -v 1 >  Test_1.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_1.edp -v 1 >  Test_1_NP2.log
	@echo "  PASSED "

Test_2: Test_2.edp
	@echo "Test_2 : mfront testing PsdMfrontHandler routine"
	@./../../../psd-solve/PSD_Solve -np 1 Test_2.edp -v 1 -mfront_behaviour Elasticity >  Test_2.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_2.edp -v 1 -mfront_behaviour Elasticity >  Test_2_NP2.log
	@./../../../psd-solve/PSD_Solve -np 1 Test_2.edp -v 1 -mfront_behaviour desmorat20152d >  Test_2_desmorat20152d.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_2.edp -v 1 -mfront_behaviour desmorat20152d >  Test_2_NP2_desmorat20152d.log
	@./../../../psd-solve/PSD_Solve -np 1 Test_2.edp -v 1 -mfront_behaviour desmorat3Dnonlocal >  Test_2_desmorat3Dnonlocal.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_2.edp -v 1 -mfront_behaviour desmorat3Dnonlocal >  Test_2_NP2_desmorat3Dnonlocal.log
	@echo "  PASSED "

Test_3: Test_3.edp
	@echo "Test_3 : mfront testing PsdMfrontHandler routine with different types of approximations (GENERALISEDPLANESTRAIN, PLANESTRAIN, TRIDIMENSIONAL, etc)."
	@./../../../psd-solve/PSD_Solve -np 1 Test_3.edp -v 1 -mfront_behaviour Elasticity >  Test_3.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_3.edp -v 1 -mfront_behaviour Elasticity >  Test_3_NP2.log
	@./../../../psd-solve/PSD_Solve -np 1 Test_3.edp -v 1 -mfront_behaviour desmorat20152d >  Test_3_desmorat20152d.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_3.edp -v 1 -mfront_behaviour desmorat20152d >  Test_3_NP2_desmorat20152d.log
	@echo "  PASSED "

Test_4: Test_4.edp
	@echo "Test_4 : mfront testing sending and printing material properties to Mfront"
	@./../../../psd-solve/PSD_Solve -np 1 Test_4.edp -v 1 -mfront_behaviour Elasticity >  Test_4.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_4.edp -v 1 -mfront_behaviour Elasticity >  Test_4_NP2.log
	@./../../../psd-solve/PSD_Solve -np 1 Test_4.edp -v 1 -mfront_behaviour desmorat20152d >  Test_4_desmorat20152d.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_4.edp -v 1 -mfront_behaviour desmorat20152d >  Test_4_NP2_desmorat20152d.log
	@echo "  PASSED "

Test_5: Test_5.edp
	@echo "Test_5 : mfront testing construction and printing mfrontMaterialTensor"
	@./../../../psd-solve/PSD_Solve -np 1 Test_5.edp -v 1 -mfront_behaviour Elasticity >  Test_5.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_5.edp -v 1 -mfront_behaviour Elasticity >  Test_5_NP2.log
	@./../../../psd-solve/PSD_Solve -np 1 Test_5.edp -v 1 -mfront_behaviour desmorat20152d >  Test_5_desmorat20152d.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_5.edp -v 1 -mfront_behaviour desmorat20152d >  Test_5_NP2_desmorat20152d.log
	@echo "  PASSED "

Test_6: Test_6.edp
	@echo "Test_6 : mfront testing construction and printing mfrontStressTensor"
	@./../../../psd-solve/PSD_Solve -np 1 Test_6.edp -v 1 -mfront_behaviour Elasticity >  Test_6.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_6.edp -v 1 -mfront_behaviour Elasticity >  Test_6_NP2.log
	@echo "  PASSED "

Test_7: Test_7.edp
	@echo "Test_7 : mfront testing construction and printing mfrontStressTensor and mfrontMaterialTensor"
	@./../../../psd-solve/PSD_Solve -np 1 Test_7.edp -v 1 >  Test_7.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_7.edp -v 1 >  Test_7_NP2.log
	@echo "  PASSED "
	
Test_8: Test_8.edp
	@echo "Test_8 : mfront testing construction and printing mfrontStressTensor for desmorat law incrementally"
	@./../../../psd-solve/PSD_Solve -np 1 Test_8.edp -v 1 -mfront_behaviour desmorat20152d >  Test_8_desmorat20152d.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_8.edp -v 1 -mfront_behaviour desmorat20152d >  Test_8_NP2_desmorat20152d.log
	@echo "  PASSED "

Test_PrintStats: Test_PrintStats.edp
	@echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Elasticity "
	@./../../../psd-solve/PSD_Solve -np 1 Test_PrintStats.edp -v 1 -mfront_behaviour Elasticity >  Test_PrintStats_Elasticity.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_PrintStats.edp -v 1 -mfront_behaviour Elasticity >  Test_PrintStats_NP2_Elasticity.log
	@echo "  PASSED "	
	@echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() IsotropicLinearHardeningPlasticity "
	@./../../../psd-solve/PSD_Solve -np 1 Test_PrintStats.edp -v 1 -mfront_behaviour IsotropicLinearHardeningPlasticity >  Test_PrintStats_IsotropicLinearHardeningPlasticity.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_PrintStats.edp -v 1 -mfront_behaviour IsotropicLinearHardeningPlasticity >  Test_PrintStats_NP2_IsotropicLinearHardeningPlasticity.log
	@echo "  PASSED "	
	@echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Iwan "
	@./../../../psd-solve/PSD_Solve -np 1 Test_PrintStats.edp -v 1 -mfront_behaviour Iwan >  Test_PrintStats_Iwan.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_PrintStats.edp -v 1 -mfront_behaviour Iwan >  Test_PrintStats_NP2_Iwan.log	
	@echo "  PASSED "
	@echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Desmorat 2D "
	@./../../../psd-solve/PSD_Solve -np 1 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat20152d >  Test_PrintStats_desmorat20152d.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat20152d >  Test_PrintStats_NP2_desmorat20152d.log
	@echo "  PASSED "
	@echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Desmorat 2D nonlocal "
	@./../../../psd-solve/PSD_Solve -np 1 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat20152dnonlocal >  Test_PrintStats_desmorat20152dnonlocal.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat20152dnonlocal >  Test_PrintStats_NP2_desmorat20152dnonlocal.log
	@echo "  PASSED "
	@echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Desmorat 3D nonlocal "
	@./../../../psd-solve/PSD_Solve -np 1 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat3Dnonlocal >  Test_PrintStats_desmorat3Dnonlocal.log
	@./../../../psd-solve/PSD_Solve -np 2 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat3Dnonlocal >  Test_PrintStats_NP2_desmorat3Dnonlocal.log
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
