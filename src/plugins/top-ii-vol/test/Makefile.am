# Define test scripts
TESTS = test_1.sh \
        test_2.sh \
        test_3.sh \
        test_4.sh \
        test_5.sh \
        test_6.sh

TEST_EXTENSIONS = .sh

# Make test scripts executable
check_SCRIPTS = $(TESTS)

# Ensure test input files are distributed
EXTRA_DIST = Test_1.edp \
             Test_2.edp \
             Test_3.edp \
             Test_4.edp \
             Test_5.edp \
             Test_6.edp

all-local:
	@echo ""

# Generate test wrapper scripts
test_1.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_1 : top-ii-vol load test"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_1.edp > Test_1.log || exit 1' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_1.edp > Test_1_NP2.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_2.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_2 : top-ii-vol testing point-cloud partitioning"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_2.edp > Test_2.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_3.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_3 : top-ii-vol testing point-cloud meshing and partitioning"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_3.edp > Test_3.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_4.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_4 : top-ii-vol testing point-cloud meshing and X-partitioning"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_4.edp > Test_4.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_5.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_5 : top-ii-vol testing point-cloud meshing and Y-partitioning"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_5.edp > Test_5.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_6.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_6 : top-ii-vol testing point-cloud meshing and Z-partitioning"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 2 Test_6.edp > Test_6.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log *.sh *.trs

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
