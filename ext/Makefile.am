
MFRONT_VERSION=3.4.0
MGIS_VERSION=1.2
PETSC_VERSION=3.16.1
FREEFEM_VERSION=4.10
GMSH_VERSION=4.8.4

ENVFILE=envvar.tmp

PETSC_ARCH_PSD  =fr

if BUILDDEPENDENCIES
LIST_MAKE_EXECUTE = gmsh-build \
mfront-build \
mgis-build \
petsc-build \
FreeFEM-build
else
LIST_MAKE_EXECUTE =
endif



if MAC
MAKEANDINSTALL = make -j4 && make MacOsX && cp -r ./idp ${prefix}/lib/ff++/$(FREEFEM_VERSION)/.
else !MAC
MAKEANDINSTALL = make -j4 && make install
endif

define mfrontenv
export PATH=\$$PATH:${prefix}/bin \nexport LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:${prefix}/lib
endef

all-local: $(LIST_MAKE_EXECUTE)
	@echo ""



#--------------------------------------------------------------------------------
# Gmsh installation
#  - Not working for MAC OS
#  - Download from wget version GMSH_VERSION
#  - User can override downlaod by providing ext/gmsh-$(GMSH_VERSION).tar.gz
#--------------------------------------------------------------------------------

gmsh-build: gmsh-$(GMSH_VERSION)/gmsh-$(GMSH_VERSION).so

gmsh-$(GMSH_VERSION)/gmsh-$(GMSH_VERSION).so: gmsh-$(GMSH_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling gmsh for you be patient:   "
	@echo "*============================================================*"
	@echo ""
if MAC
	@echo ""
	@echo "*---------------------------------*"
	@echo " IMPORTANT NOTE:   "
	@echo "*---------------------------------*"
	@echo ""
	@echo "  PSD Cannot install Gmsh for MacOS please install this"
	@echo "  yourself by downlding the precompiled 'dmg' from"
	@echo ""
	@echo "     https://gmsh.info/"
	@echo ""
	@echo "  Note in the ./configure step you will have to provide"
	@echo ""
	@echo "  --with-Gmsh=/your/gmsh/install/bin"
	@echo ""
	@echo "  with /your/gmsh/install/bin being the path where you install"
	@echo "  the dmg install"
endif
if !MAC
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring gmsh-$(GMSH_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf gmsh-$(GMSH_VERSION).tar.gz
if !BUILDZIPPEDDEPENDENCIES
	mv gmsh-$(GMSH_VERSION)-Linux64 gmsh-$(GMSH_VERSION)
endif
	@echo ""
	@echo "*---------------------------------*"
	@echo " installing gmsh "
	@echo "*---------------------------------*"
	@echo ""
	touch gmsh-$(GMSH_VERSION)/gmsh-$(GMSH_VERSION).so
	cd gmsh-$(GMSH_VERSION) && \
	cp -rf ./bin/* ${prefix}/bin/. && \
	cp -rf ./share/doc/*  ${prefix}/share/doc/.  && \
	cp -rf ./share/man  ${prefix}/share/man
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing Gmsh v$(GMSH_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""
endif

gmsh-$(GMSH_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	wget -c  https://gmsh.info/bin/Linux/gmsh-$(GMSH_VERSION)-Linux64.tgz -O gmsh-$(GMSH_VERSION).tar.gz
endif

#--------------------------------------------------------------------------------
# MFront installation
#  - Download from wget version MFRONT_VERSION
#  - User can override downlaod by providing ext/Mfront-sources-$(MFRONT_VERSION).tar.gz
#--------------------------------------------------------------------------------

mfront-build: Mfront-sources-$(MFRONT_VERSION)/build/mfront/src/libTFELMFront.so


Mfront-sources-$(MFRONT_VERSION)/build/mfront/src/libTFELMFront.so: Mfront-sources-$(MFRONT_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling mfront for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring mfront-$(MFRONT_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf Mfront-sources-$(MFRONT_VERSION).tar.gz
if !BUILDZIPPEDDEPENDENCIES
	mv tfel-TFEL-$(MFRONT_VERSION) Mfront-sources-$(MFRONT_VERSION)
endif
	cd Mfront-sources-$(MFRONT_VERSION) &&  rm -rf build && mkdir -p build && cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-cxx-17=ON -DCMAKE_INSTALL_PREFIX=${prefix} -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)  && \
	make -j8 && make install
	@echo -e "$(mfrontenv)" > ${prefix}/mfront-env.sh
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing mfront v$(MFRONT_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""

Mfront-sources-$(MFRONT_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	wget -c https://github.com/thelfer/tfel/archive/refs/tags/TFEL-$(MFRONT_VERSION).tar.gz -O Mfront-sources-$(MFRONT_VERSION).tar.gz
endif


#--------------------------------------------------------------------------------
# Mgis installation
#  - Download from wget version MGIS_VERSION
#  - User can override downlaod by providing ext/Mgis-sources-$(MGIS_VERSION).tar.gz
#--------------------------------------------------------------------------------

mgis-build: Mgis-sources-$(MGIS_VERSION)/build/src/libMFrontGenericInterface.so

Mgis-sources-$(MGIS_VERSION)/build/src/libMFrontGenericInterface.so: Mgis-sources-$(MGIS_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling Mgis for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring Mgis-$(MGIS_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf Mgis-sources-$(MGIS_VERSION).tar.gz
if !BUILDZIPPEDDEPENDENCIES
	mv MFrontGenericInterfaceSupport-MFrontGenericInterfaceSupport-$(MGIS_VERSION) Mgis-sources-$(MGIS_VERSION)
endif
	cd Mgis-sources-$(MGIS_VERSION) && rm -rf build && mkdir -p build && cd build && \
	echo "PATH=${prefix}/bin:$$PATH" > $(ENVFILE)   && echo "LD_LIBRARY_PATH=${prefix}/lib:$$LD_LIBRARY_PATH"  >> $(ENVFILE) && \
	eval `cat $(ENVFILE)` && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-cxx-17=ON -DCMAKE_INSTALL_PREFIX=${prefix}  -DCMAKE_C_COMPILER=$(CC)  -DCMAKE_CXX_COMPILER=$(CXX)  && \
	make -j8 && make install
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing mgis v$(MGIS_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""

Mgis-sources-$(MGIS_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	wget -c https://github.com/thelfer/MFrontGenericInterfaceSupport/archive/refs/tags/MFrontGenericInterfaceSupport-$(MGIS_VERSION).tar.gz -O Mgis-sources-$(MGIS_VERSION).tar.gz
endif



#--------------------------------------------------------------------------------
# PETSc installation
#  - Download from wget version PETSC_VERSION
#  - User can override downlaod by providing ext/petsc-$(PETSC_VERSION).tar.gz
#--------------------------------------------------------------------------------

petsc-build: petsc-$(PETSC_VERSION)/$(PETSC_ARCH_PSD)/lib/libpetsc.so

petsc-$(PETSC_VERSION)/$(PETSC_ARCH_PSD)/lib/libpetsc.so: petsc-$(PETSC_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling PETSc, HPDDM, METIS, PARMETIS, SCALAPACK,   "
	@echo " MUMPS, SLEPC, SUITSPAR for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring Petsc-$(PETSC_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf petsc-$(PETSC_VERSION).tar.gz
if !BUILDZIPPEDDEPENDENCIES
	mv petsc-v$(PETSC_VERSION) petsc-$(PETSC_VERSION)
endif
	cd petsc-$(PETSC_VERSION) && ./configure \
	--with-scalar-type=real \
	--prefix=${prefix}/ff-petsc/r \
	--with-cc=$(MPICC) COPTFLAGS='$(CXXFLAGS)' \
	--with-cxx=$(MPICXX) CXXOPTFLAGS='$(CXXFLAGS)' --with-cxx-dialect=C++11 \
	--with-mpiexec=mpirun \
	--with-fc=$(MPIFC) FOPTFLAGS='$(FCFLAGS)' \
	--with-cudac=0 --with-ssl=0 --with-x=0 \
	--with-debugging=no \
	--with-fortran-bindings=no \
	--download-mumps=$(CURDIR)/mumps-sources.tar.gz \
	--download-metis=$(CURDIR)/metis-sources.tar.gz \
	--download-parmetis=$(CURDIR)/parmetis-sources.tar.gz  \
	--download-slepc=$(CURDIR)/slepc-sources.tar.gz \
	--download-hpddm=$(CURDIR)/hpddm-sources.tar.gz \
	--download-scalapack=$(CURDIR)/scalapack-sources.tar.gz \
	PETSC_ARCH=$(PETSC_ARCH_PSD)
	cd petsc-$(PETSC_VERSION) &&  \
	make PETSC_DIR=$(CURDIR)/petsc-$(PETSC_VERSION) PETSC_ARCH=fr all &&  \
	make PETSC_DIR=$(CURDIR)/petsc-$(PETSC_VERSION) PETSC_ARCH=fr install
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing Petsc v$(PETSC_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""

petsc-$(PETSC_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	wget -c https://gitlab.com/petsc/petsc/-/archive/v$(PETSC_VERSION)/petsc-v$(PETSC_VERSION).tar.gz -O petsc-$(PETSC_VERSION).tar.gz
endif


#--------------------------------------------------------------------------------
# FreeFEM installation
#  - Download from wget version PETSC_VERSION
#  - User can override downlaod by providing ext/petsc-$(PETSC_VERSION).tar.gz
#--------------------------------------------------------------------------------

FreeFEM-build: FreeFem-sources-$(FREEFEM_VERSION)/plugin/mpi/PETSc.so

FreeFem-sources-$(FREEFEM_VERSION)/plugin/mpi/PETSc.so: FreeFem-sources-$(FREEFEM_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling FreeFEM for you be patient:"
	@echo "*============================================================*"
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring FreeFem-$(FREEFEM_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf FreeFem-sources-$(FREEFEM_VERSION).tar.gz
	cd FreeFem-sources-$(FREEFEM_VERSION) && autoreconf -i && \
	./configure \
	--prefix=${prefix} \
	CXX=$(MPICXX) CXXOPTFLAGS='$(CXXFLAGS)'  \
	FC=$(FC) FCOPTFLAGS='$(FCFLAGS)' \
	CC=$(MPICC) CCOPTFLAGS='$(CXXFLAGS)' \
	F77=$(F77) F77OPTFLAGS='$(FCFLAGS)' \
	MPICXX=$(MPICXX) MPICXXOPTFLAGS='$(CXXFLAGS)' \
	MPIRUN=mpirun \
	--without-petsc_complex \
	--disable-superlu \
	--with-hdf5=no &&  \
	$(MAKEANDINSTALL)

FreeFem-sources-$(FREEFEM_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	wget -c https://github.com/FreeFem/FreeFem-sources/archive/refs/tags/v$(FREEFEM_VERSION).tar.gz -O FreeFem-sources-$(FREEFEM_VERSION).tar.gz
endif




check-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Nothing to check here:"
	@echo "*============================================================*"
	@echo ""

clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log


maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in petsc-$(PETSC_VERSION) FreeFem-sources-$(FREEFEM_VERSION)
	rm  -rf Mfront-sources-$(MFRONT_VERSION) Mgis-sources-$(MGIS_VERSION) gmsh-$(GMSH_VERSION)

install-exec-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Nothing to install here:"
	@echo "*============================================================*"
	@echo ""
