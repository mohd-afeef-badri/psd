LIST_COMPILE= Elasticity-For-A-Quadrature-Point.cxx

all-local: 
	@echo ""

if HAVEMGIS	
check-local: check-header Test_1
	@echo ""
	@echo "*============================================================*"
	@echo " Checking mfront Elastic law : SUCCESS                      "
	@echo "*============================================================*"
	@echo ""
else !HAVEMGIS
check-local: check-header
	@echo ""
	@echo "*============================================================*"
	@echo " Skipping mfront unit test for Elastic law                  "
	@echo "*============================================================*"
	@echo ""
endif

check-header:
	@echo ""
	@echo "*============================================================*"
	@echo " Checking mfront Elastic law : RUNNING                      "
	@echo "*============================================================*"
	@echo ""
	
Test_1: Elasticity-For-A-Quadrature-Point.cxx
	@echo "Test_1 : mfront unit test for Elasticity (Quadrature point)"
	$(CXX) Elasticity-For-A-Quadrature-Point.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_1.log	
	@echo "  PASSED "	

Test_2: Elasticity-For-A-Quadrature-Point.cxx
	@echo "Test_2 : mfront unit test for Elasticity (Quadrature point) in 3D"
	@$(CXX) Elasticity-For-A-Quadrature-Point-3D.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_2.log	
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
