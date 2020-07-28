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

check-local: utils.o 	hujeux.o		
	@echo ""
	@echo "*============================================================*"
	@echo " Checking  hujeux  & utils routines in hujeux-law-lib          "
	@echo "*============================================================*"
	@echo ""
	$(CXX) -c test.cpp  -O2 -finline-functions -std=c++11
	$(CXX) -O2 -o hujeux-utils-tester utils.o hujeux.o test.o  -std=c++11
	./hujeux-utils-tester	> PSD-check.log	

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.so *.o *.output

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
