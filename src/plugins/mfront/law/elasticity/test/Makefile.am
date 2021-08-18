LIST_COMPILE= Elasticity.cxx

all-local: 
	@echo ""

if HAVEMGIS	
check-local: check-header Test_1
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
	
Test_1: Elasticity.cxx
	@echo "Test_1 : mfront unit test for Elasticity"
	@$(CXX) Elasticity.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_1.log	
	@echo "  PASSED "	

			
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log	 *.o a.out
	

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
