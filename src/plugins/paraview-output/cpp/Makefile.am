LIST_COMPILE= iovtk.cpp
	
all-local: iovtk.so
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

iovtk.so: iovtk.cpp
	$(FFCXX) -auto iovtk.cpp
	@echo ""	

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.so *.o
