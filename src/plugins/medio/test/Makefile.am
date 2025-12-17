# Define test scripts
TESTS = 
TEST_EXTENSIONS = .sh

if HAVEMED
TESTS += test_1.sh \
         test_2.sh
endif

# Make test scripts executable
check_SCRIPTS = $(TESTS)

# Ensure test input files are distributed
EXTRA_DIST = Test_1.edp \
             Test_2.edp \
             MedCoupling_Test.cpp

all-local:
	@echo ""

if HAVEMED
test_1.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_1 : medio save test"' >> $@
	@echo './../../../psd-solve/PSD_Solve -np 1 Test_1.edp -v 1 > Test_1.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_2.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_2 : medio load test"' >> $@
	@echo './../../../psd-solve/PSD_Solve -np 1 Test_2.edp -v 1 > Test_2.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@
endif

# Optional MedCoupling unit test (not part of standard test suite)
# Build manually with: make MedCoupling_Test
MedCoupling_Test: MedCoupling_Test.cpp
	@echo "MedCoupling unit tests"
	$(CXX) MedCoupling_Test.cpp $(CXXFLAGS_MED) $(LDFLAGS_MED) $(LIBS_MED) -DMEDCOUPLING -o $@
	@echo "Built MedCoupling_Test executable"

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.med
	rm  -f *~ *.log *.out *.txt *.sh *.trs


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
