LIST_COMPILE= Test_1 \
Test_2

all-local:
	@echo ""

if HAVEMED
check-local: check-header $(LIST_COMPILE)
	@echo ""
	@echo "*============================================================*"
	@echo " Checking medio plugin : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""
else !HAVEMED
check-local: check-header
	@echo ""
	@echo "*============================================================*"
	@echo " Skipping medio plugin test                     "
	@echo "*============================================================*"
	@echo ""
endif

check-header:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking medio plugin : RUNNING                      "
	@echo "*============================================================*"
	@echo ""

Test_1: Test_1.edp
	@echo "Test_1 : medio save test"
	@./../../../psd-solve/PSD_Solve -np 1 Test_1.edp -v 1 >  Test_1.log
	@echo "  PASSED "

Test_2: Test_2.edp
	@echo "Test_2 : medio load test"
	@./../../../psd-solve/PSD_Solve -np 1 Test_2.edp -v 1 >  Test_2.log
	@echo "  PASSED "
	
MedCoupling_Test: MedCoupling_Test.cpp
	@echo "MedCoupling unit tests"
	$(CXX) MedCoupling_Test.cpp $(CXXFLAGS_MED)  $(LDFLAGS_MED) $(LIBS_MED)  -DMEDCOUPLING
	@echo ""


clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.med
	rm  -f *~ *.log *.out *.txt


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
