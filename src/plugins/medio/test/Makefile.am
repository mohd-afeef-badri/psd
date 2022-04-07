LIST_COMPILE= Test_1 

all-local:
	@echo ""

if HAVESALOME
check-local: check-header $(LIST_COMPILE)
	@echo ""
	@echo "*============================================================*"
	@echo " Checking medio plugin : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""
else !HAVESALOME
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
	@echo "Test_1 : medio load test"
	@./../../../psd-solve/PSD_Solve -np 1 Test_1.edp -v 1 >  Test_1.log
	@echo "  PASSED "

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.med
	rm  -f *~ *.log


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
