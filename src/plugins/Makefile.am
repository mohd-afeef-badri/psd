LIST_COMPILE=gofastplugins.cpp iovtk.cpp  MatrixPlotter.cpp
	
all-local: gofastplugins.so iovtk.so  MatrixPlotter.so 
	@echo "  			  "
	@echo " Finished installing plugins !!!!!!"
	@echo "  			  "

gofastplugins.so: gofastplugins.cpp
	$(FFCXX) -auto gofastplugins.cpp
	
MatrixPlotter.so: MatrixPlotter.cpp
	$(FFCXX) -auto MatrixPlotter.cpp
	
iovtk.so: iovtk.cpp
	$(FFCXX) -auto iovtk.cpp


clean-local:
	@echo "  			  "
	@echo " Removing linking files ..."
	@echo "  			  "
	@echo "  			  "
	rm  -f *~  *.so *.o
