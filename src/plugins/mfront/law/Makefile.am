SUBDIRS = test

LIST_COMPILE = Elasticity.mfront \
Nonlinear-IsotropicLinearHardeningPlasticity.mfront \
Iwan.mfront

DEP1 = src/libBehaviour.$(SO_SUFFIX)

all-local: $(DEP1)
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

$(DEP1): Elasticity.mfront IsotropicLinearHardeningPlasticity.mfront Iwan.mfront HelloWorld.mfront
if HAVEMFRONT
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled HelloWorld support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  HelloWorld.mfront
	${mfront}/bin/mfront --obuild
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiling Elastic law support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  Elasticity.mfront
	${mfront}/bin/mfront --obuild
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiling Isotropic Linear-Hardening Plasticity law support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  IsotropicLinearHardeningPlasticity.mfront
	${mfront}/bin/mfront --obuild
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled Iwan law support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  Iwan.mfront
	${mfront}/bin/mfront --obuild
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled Hujeux law support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  HujeuxECP1985.mfront
	${mfront}/bin/mfront --obuild
endif
	@echo ""

install-exec-local:
if HAVEMFRONT
	@cp src/libBehaviour.$(SO_SUFFIX) ${prefix}/lib/.
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
	rm  -rf *~  *.so *.o $(DEP1) ./src ./include/MFront ./include/TFEL


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
