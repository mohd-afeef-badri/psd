LIST_COMPILE = hujeux.cpp utils.cpp
	
all-local: hujeux.o utils.o
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

hujeux.o: hujeux.cpp hujeux.h utils.cpp utils.h
	@echo ""
	$(FFCXX) -O3 -finline-functions -std=c++11 -fpic -c 	hujeux.cpp
	
utils.o: utils.cpp utils.h
	@echo ""
	$(FFCXX) -O3 -finline-functions -std=c++11 -fpic -c 	utils.cpp

check-local: utils.o 	hujeux.o		
	@echo ""
	@echo "*============================================================*"
	@echo " Testing  hujeux  & utils routines in hujeux-law-lib          "
	@echo "*============================================================*"
	@echo ""
	$(CXX) -c test.cpp  -O2 -finline-functions -std=c++11
	$(CXX) -O2 -o hujeux-utils-tester utils.o hujeux.o test.o  -std=c++11
	./hujeux-utils-tester		

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.so *.o *.output
