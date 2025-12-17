# Define test scripts
TESTS = 
TEST_EXTENSIONS = .sh

if HAVEMGIS
TESTS += test_0.sh \
         test_1.sh \
         test_2.sh \
         test_3.sh
endif

# Make test scripts executable
check_SCRIPTS = $(TESTS)

# Export variables for test environment
AM_TESTS_ENVIRONMENT = \
  export CXX='$(CXX)'; \
  export mgis='$(mgis)'; \
  export SO_SUFFIX='$(SO_SUFFIX)';

# Ensure test source files are distributed
EXTRA_DIST = HelloWorld-For-A-Quadrature-Point-3D.cxx \
             Elasticity-For-A-Quadrature-Point.cxx \
             Elasticity-For-A-Quadrature-Point-3D.cxx \
             Iwan-For-A-Quadrature-Point-3D.cxx \
             Elasticity-For-A-Quadrature-Point_Threaded.cxx \
             Hujeux-For-A-Quadrature-Point-3D.cxx

all-local:
	@echo ""

LIST_TESTS = Test_0 \
	     Test_1 \
	     Test_2 \
	     Test_3


if HAVEMGIS
test_0.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_0 : mfront unit test for HelloWorld"' >> $@
	@echo '$(CXX) $(srcdir)/HelloWorld-For-A-Quadrature-Point-3D.cxx -std=c++20 $(mgis)/lib/libMFrontGenericInterface.$(SO_SUFFIX) -I$(mgis)/include -Wl,-rpath,$(mgis)/lib -o test_0_exec || exit 1' >> $@
	@echo './test_0_exec > Test_0.log || exit 1' >> $@
	@echo 'rm -f test_0_exec' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_1.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_1 : mfront unit test for Elasticity (Quadrature point)"' >> $@
	@echo '$(CXX) $(srcdir)/Elasticity-For-A-Quadrature-Point.cxx -std=c++20 $(mgis)/lib/libMFrontGenericInterface.$(SO_SUFFIX) -I$(mgis)/include -Wl,-rpath,$(mgis)/lib -o test_1_exec || exit 1' >> $@
	@echo './test_1_exec > Test_1.log || exit 1' >> $@
	@echo 'rm -f test_1_exec' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_2.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_2 : mfront unit test for Elasticity (Quadrature point) in 3D"' >> $@
	@echo '$(CXX) $(srcdir)/Elasticity-For-A-Quadrature-Point-3D.cxx -std=c++20 $(mgis)/lib/libMFrontGenericInterface.$(SO_SUFFIX) -I$(mgis)/include -Wl,-rpath,$(mgis)/lib -o test_2_exec || exit 1' >> $@
	@echo './test_2_exec > Test_2.log || exit 1' >> $@
	@echo 'rm -f test_2_exec' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

test_3.sh:
	@echo '#!/bin/bash' > $@
	@echo 'echo "Test_3 : Iwan-For-A-Quadrature-Point-3D (Quadrature point) in 3D"' >> $@
	@echo '$(CXX) $(srcdir)/Iwan-For-A-Quadrature-Point-3D.cxx -std=c++20 $(mgis)/lib/libMFrontGenericInterface.$(SO_SUFFIX) -I$(mgis)/include -Wl,-rpath,$(mgis)/lib -o test_3_exec || exit 1' >> $@
	@echo './test_3_exec > Test_3.log || exit 1' >> $@
	@echo 'rm -f test_3_exec' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@
endif

# Additional manual tests
Test_4: Elasticity-For-A-Quadrature-Point_Threaded.cxx
	@echo "Test_4 : mfront OpenMP based unit test for Elasticity (Quadrature point) in 2D"
	@$(CXX) -std=c++20 Elasticity-For-A-Quadrature-Point_Threaded.cxx ${mgis}/lib/libMFrontGenericInterface.$(SO_SUFFIX) -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_4.log
	@echo "  PASSED "

Test_5: Hujeux-For-A-Quadrature-Point-3D.cxx
	@echo "Test_5 : Hujeux-For-A-Quadrature-Point-3D (Quadrature point) in 3D"
	@$(CXX) Hujeux-For-A-Quadrature-Point-3D.cxx -std=c++20 ${mgis}/lib/libMFrontGenericInterface.$(SO_SUFFIX) -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out
	@echo "  PASSED "

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat  *.output
	rm  -f *~ *.log	 *.o a.out *.sh *.trs


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
