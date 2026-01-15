# Define test scripts
TESTS = test_1.sh \
        test_2.sh \
        test_3.sh

TEST_EXTENSIONS = .sh

# Make test scripts executable
check_SCRIPTS = $(TESTS)

# Ensure test input files are distributed
EXTRA_DIST = Test_1.edp \
             Test_2.edp \
             Test_3.edp

all-local:
	@echo ""

# Generate test wrapper scripts
test_1.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_1 : gofastplugins load test"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_1.edp -v 10 > Test_1.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_2.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_2 : gofastplugins GFPeigenAlone test"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_2.edp > Test_2.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_3.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_3 : gofastplugins GFPeigen test"' >> $@
	@echo './../../../psd-solve/PSD_Solve -n 1 Test_3.edp > Test_3.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@
			
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log	*.sh *.trs

distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
