LIST_COMPILE= soil-laws.cpp
	
all-local: soil-laws.so
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

soil-laws.so: soil-laws.cpp
	$(FFCXX) -auto soil-laws.cpp './../hujeux-law-lib/hujeux.o' './../hujeux-law-lib/utils.o'
	@echo ""	

install-exec-local:
	@cp soil-laws.so ${prefix}/include/psd/soil-laws.so
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~  *.so *.o

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in	
