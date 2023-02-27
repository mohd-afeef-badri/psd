SUBDIRS = test

LIST_COMPILE = HelloWorld.mfront  \
HujeuxECP1985.mfront \
Elasticity.mfront  \
IsotropicLinearHardeningPlasticity.mfront  \
Iwan.mfront

if HAVEMFRONT
LIST_OBJ_FILES = src/HelloWorld.o  \
src/HujeuxECP1985.o \
src/Elasticity.o  \
src/Hujeux.o  \
src/IsotropicLinearHardeningPlasticity.o  \
src/Iwan.o
else
LIST_OBJ_FILES =
endif


DEP1 = src/libBehaviour.$(SO_SUFFIX)

all-local: $(DEP1)
	@echo ""
	@echo "*============================================================*"
	@echo " Compilation done in :"; pwd
	@echo "*============================================================*"
	@echo ""
	@echo " Compilation list $(LIST_COMPILE)"

$(DEP1): $(LIST_OBJ_FILES)

src/Elasticity.o: Elasticity.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled Elasticity support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  Elasticity.mfront
	${mfront}/bin/mfront --obuild


src/IsotropicLinearHardeningPlasticity.o: IsotropicLinearHardeningPlasticity.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled IsotropicLinearHardeningPlasticity support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  IsotropicLinearHardeningPlasticity.mfront
	${mfront}/bin/mfront --obuild


src/HelloWorld.o: HelloWorld.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled HelloWorld support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  HelloWorld.mfront
	${mfront}/bin/mfront --obuild


src/Iwan.o: Iwan.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled Iwan support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  Iwan.mfront
	${mfront}/bin/mfront --obuild

src/HujeuxECP1985.o: HujeuxECP1985.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled HujeuxECP1985 support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  HujeuxECP1985.mfront
	${mfront}/bin/mfront --obuild

src/Hujeux.o: Hujeux.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled Hujeux support for mfront"
	@echo "----------------------------------------"
	@echo ""
	${mfront}/bin/mfront --interface=generic  Hujeux.mfront
	${mfront}/bin/mfront --obuild

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
