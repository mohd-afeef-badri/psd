LIST_COMPILE=PSD_PreProcess.cpp
	
all-local: PSD_PreProcess 
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"


PSD_PreProcess: PSD_PreProcess.o
	$(CXX) -o PSD_PreProcess PSD_PreProcess.o
	@echo ""	


PSD_PreProcess.o:
	$(CXX) -c PSD_PreProcess.cpp -std=c++11	

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  PSD_PreProcess *.o *.edp 
	rm  -rf VTUs
	@echo ""	
