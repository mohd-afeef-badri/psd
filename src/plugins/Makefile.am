LIST_COMPILE=gofastplugins.cpp iovtk.cpp  MatrixPlotter.cpp
	
all-local: gofastplugins.so iovtk.so  MatrixPlotter.so 
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

gofastplugins.so: gofastplugins.cpp
	$(FFCXX) -auto gofastplugins.cpp
	@echo ""	
	
MatrixPlotter.so: MatrixPlotter.cpp
	$(FFCXX) -auto MatrixPlotter.cpp
	@echo ""	
	
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
