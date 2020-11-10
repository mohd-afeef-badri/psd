

install-exec-local:
	@cp DDmacro.edp ${prefix}/include/psd/DDmacro.edp
	@cp DDplotMacro.edp ${prefix}/include/psd/DDplotMacro.edp
	@cp MacroTools.edp ${prefix}/include/psd/MacroTools.edp

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm -f *~ 
	@echo ""
	
maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
