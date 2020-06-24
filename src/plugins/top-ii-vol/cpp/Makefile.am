LIST_COMPILE=top-ii-vol.cpp
	
all-local: top-ii-vol.so
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

top-ii-vol.so: top-ii-vol.cpp
	$(FFCXX) -auto top-ii-vol.cpp
	@echo ""	

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.so *.o
