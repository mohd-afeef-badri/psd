LIST_TESTS = Test_0 \
	     Test_1 \
	     Test_2 \
	     Test_3 \
	     Test_4

all-local:
	@echo ""

if HAVEMGIS	
check-local: check-header $(LIST_TESTS)
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

Test_0: HelloWorld-For-A-Quadrature-Point-3D.cxx
	@echo "Test_0 : mfront unit test for HelloWorld"
	$(CXX) HelloWorld-For-A-Quadrature-Point-3D.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_0.log
	@echo "  PASSED "
	
Test_1: Elasticity-For-A-Quadrature-Point.cxx
	@echo "Test_1 : mfront unit test for Elasticity (Quadrature point)"
	$(CXX) Elasticity-For-A-Quadrature-Point.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_1.log	
	@echo "  PASSED "	

Test_2: Elasticity-For-A-Quadrature-Point-3D.cxx
	@echo "Test_2 : mfront unit test for Elasticity (Quadrature point) in 3D"
	@$(CXX) Elasticity-For-A-Quadrature-Point-3D.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_2.log	
	@echo "  PASSED "
	

Test_3: Iwan-For-A-Quadrature-Point-3D.cxx
	@echo "Test_3 : Iwan-For-A-Quadrature-Point-3D (Quadrature point) in 3D"
	@$(CXX) Iwan-For-A-Quadrature-Point-3D.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_3.log
	@echo "  PASSED "

Test_4: Elasticity-For-A-Quadrature-Point_Threaded.cxx
	@echo "Test_4 : mfront OpenMP based unit test for Elasticity (Quadrature point) in 2D"
	@$(CXX) Elasticity-For-A-Quadrature-Point_Threaded.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out > Test_4.log	
	@echo "  PASSED "

Test_5: Hujeux-For-A-Quadrature-Point-3D.cxx
	@echo "Test_5 : Hujeux-For-A-Quadrature-Point-3D (Quadrature point) in 3D"
	@$(CXX) Hujeux-For-A-Quadrature-Point-3D.cxx ${mgis}/lib/libMFrontGenericInterface.so -I${mgis}/include -Wl,-rpath,${mgis}/lib
	@./a.out
	@echo "  PASSED "

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.pvtu *.info *.pdf *.xyz *.dat  *.output
	rm  -f *~ *.log	 *.o a.out
	

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
