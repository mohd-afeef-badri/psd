# Define test scripts
TESTS = 
TEST_EXTENSIONS = .sh

if HAVEMGIS
TESTS += test_1.sh \
         test_2.sh \
         test_3.sh \
         test_4.sh \
         test_5.sh \
         test_6.sh \
         test_7.sh \
         test_8.sh \
         test_printstats.sh
endif

# Make test scripts executable
check_SCRIPTS = $(TESTS)

# Ensure test scripts are distributed
EXTRA_DIST = Test_1.edp \
             Test_2.edp \
             Test_3.edp \
             Test_4.edp \
             Test_5.edp \
             Test_6.edp \
             Test_7.edp \
             Test_8.edp \
             Test_PrintStats.edp

all-local:
	@echo ""

# Generate test wrapper scripts
test_1.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_1 : mfront load test"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_1.edp -v 1 > Test_1.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_1.edp -v 1 > Test_1_NP2.log' >> $@
	@chmod +x $@

test_2.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_2 : mfront testing PsdMfrontHandler routine"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_2.edp -v 1 -mfront_behaviour Elasticity > Test_2.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_2.edp -v 1 -mfront_behaviour Elasticity > Test_2_NP2.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_2.edp -v 1 -mfront_behaviour desmorat20152d > Test_2_desmorat20152d.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_2.edp -v 1 -mfront_behaviour desmorat20152d > Test_2_NP2_desmorat20152d.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_2.edp -v 1 -mfront_behaviour desmorat3Dnonlocal > Test_2_desmorat3Dnonlocal.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_2.edp -v 1 -mfront_behaviour desmorat3Dnonlocal > Test_2_NP2_desmorat3Dnonlocal.log' >> $@
	@chmod +x $@

test_3.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_3 : mfront testing PsdMfrontHandler routine with different types of approximations"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_3.edp -v 1 -mfront_behaviour Elasticity > Test_3.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_3.edp -v 1 -mfront_behaviour Elasticity > Test_3_NP2.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_3.edp -v 1 -mfront_behaviour desmorat20152d > Test_3_desmorat20152d.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_3.edp -v 1 -mfront_behaviour desmorat20152d > Test_3_NP2_desmorat20152d.log' >> $@
	@chmod +x $@

test_4.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_4 : mfront testing sending and printing material properties to Mfront"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_4.edp -v 1 -mfront_behaviour Elasticity > Test_4.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_4.edp -v 1 -mfront_behaviour Elasticity > Test_4_NP2.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_4.edp -v 1 -mfront_behaviour desmorat20152d > Test_4_desmorat20152d.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_4.edp -v 1 -mfront_behaviour desmorat20152d > Test_4_NP2_desmorat20152d.log' >> $@
	@chmod +x $@

test_5.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_5 : mfront testing construction and printing mfrontMaterialTensor"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_5.edp -v 1 -mfront_behaviour Elasticity > Test_5.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_5.edp -v 1 -mfront_behaviour Elasticity > Test_5_NP2.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_5.edp -v 1 -mfront_behaviour desmorat20152d > Test_5_desmorat20152d.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_5.edp -v 1 -mfront_behaviour desmorat20152d > Test_5_NP2_desmorat20152d.log' >> $@
	@chmod +x $@

test_6.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_6 : mfront testing construction and printing mfrontStressTensor"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_6.edp -v 1 -mfront_behaviour Elasticity > Test_6.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_6.edp -v 1 -mfront_behaviour Elasticity > Test_6_NP2.log' >> $@
	@chmod +x $@

test_7.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_7 : mfront testing construction and printing mfrontStressTensor and mfrontMaterialTensor"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_7.edp -v 1 > Test_7.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_7.edp -v 1 > Test_7_NP2.log' >> $@
	@chmod +x $@

test_8.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_8 : mfront testing construction and printing mfrontStressTensor for desmorat law incrementally"' >> $@
	@echo '# Commented out as in original' >> $@
	@echo '#./../../../psd-solve/PSD_Solve -n 1 Test_8.edp -v 1 -mfront_behaviour desmorat20152d > Test_8_desmorat20152d.log' >> $@
	@echo '#./../../../psd-solve/PSD_Solve -n 2 Test_8.edp -v 1 -mfront_behaviour desmorat20152d > Test_8_NP2_desmorat20152d.log' >> $@
	@chmod +x $@

test_printstats.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Elasticity"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_PrintStats.edp -v 1 -mfront_behaviour Elasticity > Test_PrintStats_Elasticity.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_PrintStats.edp -v 1 -mfront_behaviour Elasticity > Test_PrintStats_NP2_Elasticity.log' >> $@
	@echo 'echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() IsotropicLinearHardeningPlasticity"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_PrintStats.edp -v 1 -mfront_behaviour IsotropicLinearHardeningPlasticity > Test_PrintStats_IsotropicLinearHardeningPlasticity.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_PrintStats.edp -v 1 -mfront_behaviour IsotropicLinearHardeningPlasticity > Test_PrintStats_NP2_IsotropicLinearHardeningPlasticity.log' >> $@
	@echo 'echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Iwan"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_PrintStats.edp -v 1 -mfront_behaviour Iwan > Test_PrintStats_Iwan.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_PrintStats.edp -v 1 -mfront_behaviour Iwan > Test_PrintStats_NP2_Iwan.log' >> $@
	@echo 'echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Desmorat 2D"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat20152d > Test_PrintStats_desmorat20152d.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat20152d > Test_PrintStats_NP2_desmorat20152d.log' >> $@
	@echo 'echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Desmorat 2D nonlocal"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat20152dnonlocal > Test_PrintStats_desmorat20152dnonlocal.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat20152dnonlocal > Test_PrintStats_NP2_desmorat20152dnonlocal.log' >> $@
	@echo 'echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Desmorat 3D nonlocal"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat3Dnonlocal > Test_PrintStats_desmorat3Dnonlocal.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_PrintStats.edp -v 1 -mfront_behaviour desmorat3Dnonlocal > Test_PrintStats_NP2_desmorat3Dnonlocal.log' >> $@
	@echo 'echo "Test_PrintStats : mfront testing PsdMfrontPrintBehaviourStats() Desmorat planestressDelta nonlocal"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_PrintStats.edp -v 1 -mfront_behaviour desmoratplanestressDelta > Test_PrintStats_desmoratplanestressDelta.log' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_PrintStats.edp -v 1 -mfront_behaviour desmoratplanestressDelta > Test_PrintStats_NP2_desmoratplanestressDelta.log' >> $@
	@chmod +x $@

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm -f *~ *.log *.sh *.trs

distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm -rf Makefile Makefile.in test-suite.log