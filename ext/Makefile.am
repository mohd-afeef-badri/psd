
MFRONT_VERSION=3.4.0
MGIS_VERSION=1.2
PETSC_VERSION=3.18.2
FREEFEM_VERSION=4.12
GMSH_VERSION=4.10.4
MUMPS_VERSION=5.5.1
METIS_VERSION=5.1.0
PARMETIS_VERSION=4.0.3
SLEPC_VERSION=d9df183c341775ffc91510ec6827e13db44a25cd
SCALAPACK_VERSION=2.2.0
HPDDM_VERSION=2.2.2
HYPRE_VERSION=2.25.0

#################################################
# UBUNTU 22.04
#################################################
#SALOME_OS=UB22.04
#SALOME_OS_TAG=-native-$(SALOME_OS)-SRC
#SALOME_TAG=-22b4348cf247e9a72539dca3b6f2d65f

#################################################
# UBUNTU 20.04
#################################################
#SALOME_OS=UB20.04
#SALOME_OS_TAG=-native-$(SALOME_OS)-SRC
#SALOME_TAG=

#################################################
# UBUNTU 18.04
#################################################
#SALOME_OS=UB18.04
#SALOME_OS_TAG=-$(SALOME_OS)-SRC
#SALOME_TAG=

#################################################
# CENTOS 7
#################################################
#SALOME_OS=CO7
#SALOME_OS_TAG=-MPI-$(SALOME_OS)-SRC
#SALOME_TAG=

SALOME_OS=UB22.04
SALOME_OS_TAG=-native-$(SALOME_OS)-SRC
SALOME_TAG=-22b4348cf247e9a72539dca3b6f2d65f

SALOME_VERSION=9.9.0

ENVFILE=envvar.tmp


PETSC_ARCH_PSD  =fr

if BUILDDEPENDENCIES
LIST_MAKE_EXECUTE = gmsh-build \
mfront-build \
mgis-build \
petsc-build \
freefem-build \
salome-build
else
LIST_MAKE_EXECUTE =
endif


GMSH_DOWNLOAD    = wget -c https://gmsh.info/bin/Linux/gmsh-$(GMSH_VERSION)-Linux64.tgz \
                       -O gmsh-$(GMSH_VERSION).tar.gz
FREEFEM_DOWNLOAD = wget -c https://github.com/FreeFem/FreeFem-sources/archive/refs/tags/v$(FREEFEM_VERSION).tar.gz \
                       -O freefem-$(FREEFEM_VERSION).tar.gz
HPDDM_DOWNLOAD   =  wget -c https://github.com/hpddm/hpddm/archive/v$(HPDDM_VERSION).tar.gz \
                       -O hpddm-$(HPDDM_VERSION).tar.gz
HYPRE_DOWNLOAD   =  wget -c https://github.com/hypre-space/hypre/archive/v$(HYPRE_VERSION).tar.gz \
                       -O hypre-$(HYPRE_VERSION).tar.gz
MFRONT_DOWNLOAD  = wget -c https://github.com/thelfer/tfel/archive/refs/tags/TFEL-$(MFRONT_VERSION).tar.gz \
                       -O mfront-$(MFRONT_VERSION).tar.gz
MGIS_DOWNLOAD    = wget -c https://github.com/thelfer/MFrontGenericInterfaceSupport/archive/refs/tags/MFrontGenericInterfaceSupport-$(MGIS_VERSION).tar.gz \
                       -O mgis-$(MGIS_VERSION).tar.gz
PETSC_DOWNLOAD   = wget -c https://gitlab.com/petsc/petsc/-/archive/v$(PETSC_VERSION)/petsc-v$(PETSC_VERSION).tar.gz \
                       -O petsc-$(PETSC_VERSION).tar.gz
MUMPS_DOWNLOAD   =  wget -c https://graal.ens-lyon.fr/MUMPS/MUMPS_$(MUMPS_VERSION).tar.gz \
                       -O mumps-$(MUMPS_VERSION).tar.gz
METIS_DOWNLOAD   =  wget -c https://bitbucket.org/petsc/pkg-metis/get/v$(METIS_VERSION)-p10.tar.gz \
                       -O metis-$(METIS_VERSION).tar.gz
SLEPC_DOWNLOAD   =  wget -c https://gitlab.com/slepc/slepc/-/archive/v$(SLEPC_VERSION)/slepc-v$(SLEPC_VERSION).tar.gz \
                       -O slepc-$(SLEPC_VERSION).tar.gz
PARMETIS_DOWNLOAD    =  wget -c https://bitbucket.org/petsc/pkg-parmetis/get/v$(PARMETIS_VERSION)-p8.tar.gz \
                       -O parmetis-$(PARMETIS_VERSION).tar.gz
SCALAPACK_DOWNLOAD   =  wget -c https://bitbucket.org/petsc/pkg-scalapack/get/v$(SCALAPACK_VERSION)-p1.tar.gz \
                       -O scalapack-$(SCALAPACK_VERSION).tar.gz
SALOME_DOWNLOAD      =  wget -c https://files.salome-platform.org/Salome/Salome$(SALOME_VERSION)/SALOME-$(SALOME_VERSION)$(SALOME_OS_TAG)$(SALOME_TAG).tar.gz \
                       -O salome-$(SALOME_VERSION).tar.gz
PETSC_PATCH_DOWNLOAD = wget https://raw.githubusercontent.com/FreeFem/FreeFem-sources/master/3rdparty/ff-petsc/petsc-cmake-seq.patch


if MAC
MAKEANDINSTALL = make -j4 && make MacOsX && cp -r ./idp ${prefix}/lib/ff++/$(FREEFEM_VERSION)/.
else !MAC
MAKEANDINSTALL = make -j4 && make install
endif


define mfrontenv
export PATH=\$$PATH:${prefix}/bin \nexport LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:${prefix}/lib
endef

all-local: make-directories $(LIST_MAKE_EXECUTE)
	@echo ""


make-directories:
	@mkdir -p ${prefix}/bin
	@mkdir -p ${prefix}/share/doc
	@mkdir -p ${prefix}/share/man

download-dependencies:
	@if [ ! -f gmsh-$(GMSH_VERSION).tar.gz ]; then \
		$(GMSH_DOWNLOAD); \
	fi
	@if [ ! -f hpddm-$(HPDDM_VERSION).tar.gz ]; then \
		$(HPDDM_DOWNLOAD); \
	fi
	@if [ ! -f hypre-$(HYPRE_VERSION).tar.gz ]; then \
		$(HYPRE_DOWNLOAD); \
	fi
	@if [ ! -f mfront-$(MFRONT_VERSION).tar.gz ]; then \
		$(MFRONT_DOWNLOAD); \
	fi
	@if [ ! -f mgis-$(MGIS_VERSION).tar.gz ]; then \
		$(MGIS_DOWNLOAD); \
	fi
	@if [ ! -f petsc-$(PETSC_VERSION).tar.gz ]; then \
		$(PETSC_DOWNLOAD); \
	fi
	@if [ ! -f freefem-$(FREEFEM_VERSION).tar.gz ]; then \
		$(FREEFEM_DOWNLOAD); \
	fi
	@if [ ! -f mumps-$(MUMPS_VERSION).tar.gz ]; then \
		$(MUMPS_DOWNLOAD); \
	fi
	@if [ ! -f metis-$(METIS_VERSION).tar.gz ]; then \
		$(METIS_DOWNLOAD); \
	fi
	@if [ ! -f slepc-$(SLEPC_VERSION).tar.gz ]; then \
		$(SLEPC_DOWNLOAD); \
	fi
	@if [ ! -f parmetis-$(PARMETIS_VERSION).tar.gz ]; then \
		$(PARMETIS_DOWNLOAD); \
	fi
	@if [ ! -f scalapack-$(SCALAPACK_VERSION).tar.gz ]; then \
		$(SCALAPACK_DOWNLOAD); \
	fi
	@if [ ! -f salome-$(SALOME_VERSION).tar.gz ]; then \
		$(SALOME_DOWNLOAD); \
	fi
	@if [ ! -f petsc-scalapack.patch ]; then \
		$(PETSC_PATCH_DOWNLOAD); \
	fi

#--------------------------------------------------------------------------------
# Gmsh installation
#  - Not working for MAC OS
#  - Download from wget version GMSH_VERSION
#  - User can override download by providing ext/gmsh-$(GMSH_VERSION).tar.gz
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
	@echo "  yourself by downloading the precompiled 'dmg' from"
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
	[ -d gmsh-$(GMSH_VERSION)-Linux64 ] && mv gmsh-$(GMSH_VERSION)-Linux64 gmsh-$(GMSH_VERSION)
	@echo ""
	@echo "*---------------------------------*"
	@echo " installing gmsh "
	@echo "*---------------------------------*"
	@echo ""
	cd gmsh-$(GMSH_VERSION)                      && \
	cp -rf ./bin/* ${prefix}/bin/.               && \
	cp -rf ./share/doc/*  ${prefix}/share/doc/.  && \
	cp -rf ./share/man  ${prefix}/share/man      && \
	touch gmsh-$(GMSH_VERSION).so
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing Gmsh v$(GMSH_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""
endif

gmsh-$(GMSH_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(GMSH_DOWNLOAD)
endif

#--------------------------------------------------------------------------------
# MFront installation
#  - Download from wget version MFRONT_VERSION
#  - User can override download by providing ext/mfront-$(MFRONT_VERSION).tar.gz
#--------------------------------------------------------------------------------

mfront-build: mfront-$(MFRONT_VERSION)/build/mfront/src/libTFELMFront.so


mfront-$(MFRONT_VERSION)/build/mfront/src/libTFELMFront.so: mfront-$(MFRONT_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling mfront for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring mfront-$(MFRONT_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf mfront-$(MFRONT_VERSION).tar.gz
	[ -d tfel-TFEL-$(MFRONT_VERSION) ] && mv tfel-TFEL-$(MFRONT_VERSION) mfront-$(MFRONT_VERSION)
	cd mfront-$(MFRONT_VERSION)   && \
	rm -rf build                  && \
	mkdir -p build                && \
	cd build                      && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-cxx-17=ON -DCMAKE_INSTALL_PREFIX=${prefix} -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)  && \
	make -j8 && make install
	@echo -e "$(mfrontenv)" > ${prefix}/mfront-env.sh
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing mfront v$(MFRONT_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""

mfront-$(MFRONT_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(MFRONT_DOWNLOAD)
endif


#--------------------------------------------------------------------------------
# Mgis installation
#  - Download from wget version MGIS_VERSION
#  - User can override download by providing ext/mgis-$(MGIS_VERSION).tar.gz
#--------------------------------------------------------------------------------

mgis-build: mgis-$(MGIS_VERSION)/build/src/libMFrontGenericInterface.so

mgis-$(MGIS_VERSION)/build/src/libMFrontGenericInterface.so: mgis-$(MGIS_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling Mgis for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring mgis-$(MGIS_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf mgis-$(MGIS_VERSION).tar.gz
	[ -d MFrontGenericInterfaceSupport-MFrontGenericInterfaceSupport-$(MGIS_VERSION) ] && mv MFrontGenericInterfaceSupport-MFrontGenericInterfaceSupport-$(MGIS_VERSION) mgis-$(MGIS_VERSION)
	cd mgis-$(MGIS_VERSION)     && \
	rm -rf build                && \
	mkdir -p build              && \
	cd build                    && \
	echo "PATH=${prefix}/bin:$$PATH" > $(ENVFILE)                         && \
	echo "LD_LIBRARY_PATH=${prefix}/lib:$$LD_LIBRARY_PATH"  >> $(ENVFILE) && \
	eval `cat $(ENVFILE)` && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-cxx-17=ON -DCMAKE_INSTALL_PREFIX=${prefix}  -DCMAKE_C_COMPILER=$(CC)  -DCMAKE_CXX_COMPILER=$(CXX)  && \
	make -j8 && make install
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing mgis v$(MGIS_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""

mgis-$(MGIS_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(MGIS_DOWNLOAD)
endif



#--------------------------------------------------------------------------------
# PETSc installation
#  - Download from wget version PETSC_VERSION
#  - User can override download by providing ext/petsc-$(PETSC_VERSION).tar.gz
#--------------------------------------------------------------------------------

if BUILDZIPPEDDEPENDENCIES
PETSC_DEP = --download-mumps=$(CURDIR)/mumps-$(MUMPS_VERSION).tar.gz         \
	--download-metis=$(CURDIR)/metis-$(METIS_VERSION).tar.gz             \
	--download-parmetis=$(CURDIR)/parmetis-$(PARMETIS_VERSION).tar.gz    \
	--download-slepc=$(CURDIR)/slepc-$(SLEPC_VERSION).tar.gz             \
	--download-hpddm=$(CURDIR)/hpddm-$(HPDDM_VERSION).tar.gz             \
	--download-hypre=$(CURDIR)/hypre-$(HYPRE_VERSION).tar.gz             \
	--download-scalapack=$(CURDIR)/scalapack-$(SCALAPACK_VERSION).tar.gz
else !BUILDZIPPEDDEPENDENCIES
PETSC_DEP = --download-mumps \
	--download-metis     \
	--download-parmetis  \
	--download-slepc     \
	--download-hpddm     \
	--download-hypre     \
	--download-scalapack
endif

petsc-build: petsc-$(PETSC_VERSION)/$(PETSC_ARCH_PSD)/lib/libpetsc.so

petsc-$(PETSC_VERSION)/$(PETSC_ARCH_PSD)/lib/libpetsc.so: petsc-cmake-seq.patch petsc-$(PETSC_VERSION).tar.gz
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
	[ -d petsc-v$(PETSC_VERSION) ] && mv petsc-v$(PETSC_VERSION) petsc-$(PETSC_VERSION)
	cd petsc-$(PETSC_VERSION) && \
	patch -p1 < ../petsc-cmake-seq.patch     && \
	./configure \
	--with-scalar-type=real \
	--prefix=${prefix}/ff-petsc/r \
	--with-cc=$(MPICC) COPTFLAGS='$(CXXFLAGS)' \
	--with-cxx=$(MPICXX) CXXOPTFLAGS='$(CXXFLAGS)' --with-cxx-dialect=C++11 \
	--with-mpiexec=$(MPIRUN) \
	--with-fc=$(MPIFC) FOPTFLAGS='$(FCFLAGS)' \
	--with-cudac=0 --with-ssl=0 --with-x=1 \
	--with-debugging=no \
	--with-fortran-bindings=no \
	$(PETSC_DEP) \
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
	$(PETSC_DOWNLOAD)
endif

petsc-cmake-seq.patch:
if !BUILDZIPPEDDEPENDENCIES
	$(PETSC_PATCH_DOWNLOAD)
endif


#--------------------------------------------------------------------------------
# FreeFEM installation
#  - Download from wget version FREEFEM_VERSION
#  - User can override download by providing ext/freefem-$(PETSC_VERSION).tar.gz
#--------------------------------------------------------------------------------

freefem-build: freefem-$(FREEFEM_VERSION)/plugin/mpi/PETSc.so

freefem-$(FREEFEM_VERSION)/plugin/mpi/PETSc.so: freefem-$(FREEFEM_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling FreeFEM for you be patient:"
	@echo "*============================================================*"
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring FreeFem-$(FREEFEM_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf freefem-$(FREEFEM_VERSION).tar.gz
	[ -d FreeFem-sources-$(FREEFEM_VERSION) ] && mv FreeFem-sources-$(FREEFEM_VERSION) freefem-$(FREEFEM_VERSION)
	cd freefem-$(FREEFEM_VERSION)    && \
	patch -p1 < ../FreeFEM.patch     && \
	autoreconf -i                    && \
	./configure \
	--prefix=${prefix} \
	CXX=$(MPICXX) CXXOPTFLAGS='$(CXXFLAGS)'  \
	FC=$(FC) FCOPTFLAGS='$(FCFLAGS)' \
	CC=$(MPICC) CCOPTFLAGS='$(CXXFLAGS)' \
	F77=$(F77) F77OPTFLAGS='$(FCFLAGS)' \
	MPICXX=$(MPICXX) MPICXXOPTFLAGS='$(CXXFLAGS)' \
	MPIRUN=$(MPIRUN) \
	--without-petsc_complex \
	--disable-superlu \
	--with-hdf5=no &&  \
	$(MAKEANDINSTALL)

freefem-$(FREEFEM_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(FREEFEM_DOWNLOAD)
endif

#--------------------------------------------------------------------------------
# SALOME installation
#  - Download from wget version SALOME_VERSION
#  - User can override download by providing ext/salome-$(SALOME_VERSION).tar.gz
#--------------------------------------------------------------------------------

salome-build: salome-$(SALOME_VERSION)/salome-$(SALOME_VERSION).so

salome-$(SALOME_VERSION)/salome-$(SALOME_VERSION).so: salome-$(SALOME_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling SALOME for you be patient:"
	@echo "*============================================================*"
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring SALOME-$(SALOME_VERSION).tar.gz"
	@echo "*---------------------------------*"
	tar -xf salome-$(SALOME_VERSION).tar.gz
	[ -d SALOME-$(SALOME_VERSION)$(SALOME_OS_TAG) ] && mv SALOME-$(SALOME_VERSION)$(SALOME_OS_TAG) salome-$(SALOME_VERSION)
	@echo ""
	@echo "*---------------------------------*"
	@echo " installing SALOME "
	@echo "*---------------------------------*"
	@echo ""
	cd salome-$(SALOME_VERSION)                    			 && \
	cp ./salome ./salome-tmp                    			 && \
	cp ./mesa_salome ./mesa_salome-tmp                    		 && \
	cp ./env_launch.sh ./env_launch.sh-tmp                    	 && \
	find . -name salome-tmp -exec sed -i -e 's#BINARIES-$(SALOME_OS)#BINARIES-SALOME#g' {} \;		&& \
	find . -name mesa_salome-tmp -exec sed -i -e 's#BINARIES-$(SALOME_OS)#BINARIES-SALOME#g' {} \;		&& \
	find . -name env_launch.sh-tmp -exec sed -i -e 's#BINARIES-$(SALOME_OS)#BINARIES-SALOME#g' {} \;	&& \
	cp -rf ./salome-tmp ${prefix}/bin/salome                		&& \
	cp -rf ./mesa_salome-tmp   ${prefix}/bin/mesa_salome  		 	&& \
	cp -rf ./env_launch.sh-tmp ${prefix}/bin/psd_salome_env_launch.sh	&& \
	cp -rf ./BINARIES-$(SALOME_OS)  ${prefix}/bin/BINARIES-SALOME		&& \
	touch salome-$(SALOME_VERSION).so
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing SALOME v$(SALOME_VERSION) "
	@echo "*---------------------------------*"
	@echo ""

salome-$(SALOME_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(SALOME_DOWNLOAD)
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
	rm  -rf Makefile Makefile.in
	rm  -rf petsc-$(PETSC_VERSION) freefem-$(FREEFEM_VERSION) mfront-$(MFRONT_VERSION)
	rm  -rf mgis-$(MGIS_VERSION) gmsh-$(GMSH_VERSION) salome-$(SALOME_VERSION)
	rm *.tar.gz

install-exec-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Nothing to install here:"
	@echo "*============================================================*"
	@echo ""
