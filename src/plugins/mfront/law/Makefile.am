SUBDIRS = test

LIST_COMPILE = HelloWorld.mfront  \
HujeuxECP1985.mfront \
##Hujeux.mfront \
Elasticity.mfront  \
IsotropicLinearHardeningPlasticity.mfront  \
Iwan.mfront \
desmorat20152d.mfront \
desmorat20152dnonlocal.mfront \
desmorat3Dnonlocal.mfront \
desmoratplanestress.mfront \
desmoratplanestressDelta.mfront

if HAVEMFRONT
LIST_OBJ_FILES = src/HelloWorld.o  \
src/HujeuxECP1985.o \
src/Elasticity.o  \
##src/Hujeux.o \
src/IsotropicLinearHardeningPlasticity.o  \
src/Iwan.o \
src/desmorat20152d.o \
src/desmorat20152dnonlocal.o \
src/desmorat3Dnonlocal.o \
src/desmoratplanestress.o \
src/desmoratplanestressDelta.o
else
LIST_OBJ_FILES =
endif

if HAVEMFRONTPREFIX
export PATH := $(MFRONT_PREFIX)/bin:$(PATH)
export LD_LIBRARY_PATH := $(MFRONT_PREFIX)/lib:$(LD_LIBRARY_PATH)
endif

DEP1 = src/libBehaviour.$(SO_SUFFIX)

.NOTPARALLEL:

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
	$(MFRONT) --interface=generic  Elasticity.mfront
	$(MFRONT) --obuild


src/IsotropicLinearHardeningPlasticity.o: IsotropicLinearHardeningPlasticity.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled IsotropicLinearHardeningPlasticity support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  IsotropicLinearHardeningPlasticity.mfront
	$(MFRONT) --obuild


src/HelloWorld.o: HelloWorld.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled HelloWorld support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  HelloWorld.mfront
	$(MFRONT) --obuild


src/Iwan.o: Iwan.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled Iwan support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  Iwan.mfront
	$(MFRONT) --obuild

src/HujeuxECP1985.o: HujeuxECP1985.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled HujeuxECP1985 support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  HujeuxECP1985.mfront
	$(MFRONT) --obuild

src/Hujeux.o: Hujeux.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled Hujeux support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  Hujeux.mfront
	$(MFRONT) --obuild

src/desmorat20152d.o: desmorat20152d.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled desmorat20152d support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  desmorat20152d.mfront
	$(MFRONT) --obuild

src/desmorat20152dnonlocal.o: desmorat20152dnonlocal.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled desmorat20152dnonlocal support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  desmorat20152dnonlocal.mfront
	$(MFRONT) --obuild

src/desmorat3Dnonlocal.o: desmorat3Dnonlocal.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled desmorat3Dnonlocal support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  desmorat3Dnonlocal.mfront
	$(MFRONT) --obuild
	
src/desmoratplanestress.o: desmoratplanestress.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled desmoratplanestress support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  desmoratplanestress.mfront
	$(MFRONT) --obuild

src/desmoratplanestressDelta.o: desmoratplanestressDelta.mfront
	@echo ""
	@echo "----------------------------------------"
	@echo "Compiled desmoratplanestressDelta support for mfront"
	@echo "----------------------------------------"
	@echo ""
	$(MFRONT) --interface=generic  desmoratplanestressDelta.mfront
	$(MFRONT) --obuild


install-exec-local:
if HAVEMFRONT
	@mkdir -p ${prefix}/lib
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
	rm  -rf *~  *.$(SO_SUFFIX) *.o $(DEP1) ./src ./include/MFront ./include/TFEL


distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in
