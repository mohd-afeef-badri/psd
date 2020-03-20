LIST_COMPILE=PSD_PreProcess.cpp
	
all-local: PSD_PreProcess 
	@echo "  			  "
	@echo " Finished installing PSD_PreProcess !!!!!!"
	@echo "  			  "
	@echo " Compilation list $(LIST_COMPILE)"


PSD_PreProcess: PSD_PreProcess.o
	g++ -o PSD_PreProcess PSD_PreProcess.o	


PSD_PreProcess.o:
	g++ -c PSD_PreProcess.cpp -std=c++11	



clean-local:
	@echo "  			  "
	@echo " Removing linking files ..."
	@echo "  			  "
	@echo "  			  "
	rm  -f *~  PSD_PreProcess *.o *.edp
