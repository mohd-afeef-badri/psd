LIST_COMPILE=gofastplugins.cpp iovtk.cpp  MatrixPlotter.cpp
	
all-local: gofastplugins.so iovtk.so  MatrixPlotter.so 
	@echo "  			  "
	@echo " Finished installing plugins !!!!!!"
	@echo "  			  "
	@echo " Compilation list $(LIST_COMPILE)"
	@echo " ff-c++ used  $(FFINSTALLDIR)"
	@echo " Corresponds to FreeFEM  $(FFINSTALLDIR)FreeFem++"

gofastplugins.so:
	$(FFINSTALLDIR)ff-c++ -auto gofastplugins.cpp
	
MatrixPlotter.so:
	$(FFINSTALLDIR)ff-c++ -auto MatrixPlotter.cpp
	
iovtk.so:
	$(FFINSTALLDIR)ff-c++ -auto iovtk.cpp	

.cpp.$(DYLIB_SUFFIX): ff-c++
	 $(FFDIR)/bin/ff-c++ -auto $<


clean-local:
	@echo "  			  "
	@echo " Removing linking files ..."
	@echo "  			  "
	@echo "  			  "
	rm  -f *~  *.so *.o
