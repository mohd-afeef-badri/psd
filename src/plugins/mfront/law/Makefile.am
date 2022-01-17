SUBDIRS = test
LIST_COMPILE= Elasticity.mfront \
Nonlinear-IsotropicLinearHardeningPlasticity.mfront \
Iwan.mfront

all-local: Linear-Elasticity Nonlinear-IsotropicLinearHardeningPlasticity Iwan
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

Linear-Elasticity: Elasticity.mfront
if HAVEMFRONT
	${mfront}/bin/mfront --interface=generic  Elasticity.mfront
	${mfront}/bin/mfront --obuild
endif
	@echo "Compiled Elastic law support for mfront"

Nonlinear-IsotropicLinearHardeningPlasticity: IsotropicLinearHardeningPlasticity.mfront
if HAVEMFRONT
	${mfront}/bin/mfront --interface=generic  IsotropicLinearHardeningPlasticity.mfront
	${mfront}/bin/mfront --obuild
endif
	@echo "Compiled Isotropic Linear-Hardening Plasticity law support for mfront"

Iwan: Iwan.mfront
if HAVEMFRONT
	${mfront}/bin/mfront --interface=generic  Iwan.mfront
	${mfront}/bin/mfront --obuild
endif
	@echo "Compiled Iwan law support for mfront"
			
install-exec-local:
if HAVEMFRONT
	@cp src/libBehaviour.so ${prefix}/lib/.
endif
	@echo ""
	@echo "*============================================================*"
	@echo " Installation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

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
