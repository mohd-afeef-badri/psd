# Define test scripts
TESTS = hujeux_utils_test.sh

TEST_EXTENSIONS = .sh

# Make test scripts executable
check_SCRIPTS = $(TESTS)

LIST_COMPILE = utils.cpp hujeux.cpp druckerprager.cpp
	
all-local: utils.o hujeux.o druckerprager.o
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

utils.o: utils.cpp utils.h
	@echo ""
	$(FFCXX) -O3 -finline-functions -std=c++11 -fpic -c 	utils.cpp
	
hujeux.o: hujeux.cpp hujeux.h utils.cpp utils.h
	@echo ""
	$(FFCXX) -O3 -finline-functions -std=c++11 -fpic -c 	hujeux.cpp
	
druckerprager.o: druckerprager.cpp druckerprager.o utils.cpp utils.h
	@echo ""
	$(FFCXX) -O3 -finline-functions -std=c++11 -fpic -c 	druckerprager.cpp

# Build test executable
hujeux-utils-tester: utils.o hujeux.o test.o
	$(CXX) -O2 -o $@ utils.o hujeux.o test.o -std=c++11

test.o: test.cpp
	$(CXX) -c test.cpp -O2 -finline-functions -std=c++11

# Generate test wrapper script
hujeux_utils_test.sh: hujeux-utils-tester
	@echo '#!/bin/bash' > $@
	@echo 'echo ""' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo " Checking hujeux & utils routines in hujeux-law-lib          "' >> $@
	@echo 'echo "*============================================================*"' >> $@
	@echo 'echo ""' >> $@
	@echo './hujeux-utils-tester > PSD-check.log || exit 1' >> $@
	@echo 'echo "  PASSED "' >> $@
	@chmod +x $@

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.$(SO_SUFFIX) *.o *.output *.log *.sh *.trs

distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
