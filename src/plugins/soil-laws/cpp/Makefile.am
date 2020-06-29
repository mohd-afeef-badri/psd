LIST_COMPILE= soil-law.cpp
	
all-local: soil-law.so
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

soil-law.so: soil-law.cpp
	$(FFCXX) -auto soil-law.cpp
	@echo ""	

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.so *.o
