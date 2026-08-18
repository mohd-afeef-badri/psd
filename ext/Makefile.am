#----------------------------------------------------------------------------------------
# This section in Makefile.am defines version variables for various libraries used in the
# project. These variables specify the versions of external dependencies used during the
# build process.
#----------------------------------------------------------------------------------------

# Define the versions used by the MEDCoupling source build
MEDCOUPLING_VERSION=9.14.0
MEDCOUPLING_TAG=V9_14_0
MEDCOUPLING_ARCHIVE_VERSION=9_14_0
MEDCOUPLING_CONFIGURATION_VERSION=9.14.0
HDF5_MED_VERSION=1.10.11
HDF5_MED_TAG=hdf5-1_10_11
MEDFILE_VERSION=4.1.1

# Define the version of Ipopt library
IPOPT_VERSION=3.12.4

# Define the version of parmmg
PARMMG_VERSION=1.5.0

# Define the version of mmg
MMG_VERSION=5.8.0

# Define the version of mshmet
MSHMET_VERSION=2012.04.25

# Define the version of ptscotch
PTSCOTCH_VERSION=7.0.11

# Define the version of MFront library
MFRONT_VERSION=5.1.0

# Define the version of MGIS library
MGIS_VERSION=3.1

# Define the version of PETSc library
PETSC_VERSION=3.25.3

# Define the version of FreeFEM library
FREEFEM_VERSION=4.17

# Define the version of Gmsh library
GMSH_VERSION=4.11.1

# Define the version of MUMPS Seq library
MUMPS_SEQ_VERSION=5.0.2

# Define the version of MUMPS library
MUMPS_VERSION=5.8.2

# Define the version of METIS library
METIS_VERSION=5.1.0

# Define the version of ParMETIS library
PARMETIS_VERSION=4.0.3

# Define the version of SLEPc library
SLEPC_VERSION=3.25.1

# Define the version of SCALAPACK library
SCALAPACK_VERSION=2.2.3

# Define the version of HPDDM library
HPDDM_VERSION=b79bf2a23284c4eca63ea04b5c18a325b664db1d

# Define the version of HYPRE library
HYPRE_VERSION=85b779557005b2eb94c231c1b516e988b87f4e53

# Define the version of BLAS/LAPACK library
F2CBLASLAPACK_VERSION=3.8.0

#----------------------------------------------------------------------------------------
# Check if BUILDDEPENDENCIES flag is set to determine the build execution list
#----------------------------------------------------------------------------------------

if BUILDDEPENDENCIES

LIST_MAKE_EXECUTE = make-directories \
                    download-dependencies \
                    mfront-build \
                    mgis-build   \
                    petsc-build  \
                    freefem-build

if BUILDMEDCOUPLING
LIST_MAKE_EXECUTE += \
                    gmsh-build \
                    medcoupling-build
else
if !MAC
LIST_MAKE_EXECUTE += gmsh-build
endif
endif

else
LIST_MAKE_EXECUTE =
endif


#----------------------------------------------------------------------------------------
# This section in Makefile.am contains various download commands to fetch the source code
# for different libraries and dependencies used in the project. The download URLs are
# specified based on the library versions and the target operating system.
#----------------------------------------------------------------------------------------

# Download Gmsh source code
GMSH_DOWNLOAD    = wget -c https://gmsh.info/bin/Linux/gmsh-$(GMSH_VERSION)-Linux64.tgz \
			-O gmsh-$(GMSH_VERSION).tar.gz
# Download FreeFEM source code
FREEFEM_DOWNLOAD = wget -c https://github.com/FreeFem/FreeFem-sources/archive/v$(FREEFEM_VERSION).tar.gz \
			-O freefem-$(FREEFEM_VERSION).tar.gz
# Download HPDDM source code
HPDDM_DOWNLOAD = wget -c https://github.com/hpddm/hpddm/archive/$(HPDDM_VERSION).tar.gz \
			-O hpddm-$(HPDDM_VERSION).tar.gz
# Download HYPRE source code
HYPRE_DOWNLOAD = wget -c https://github.com/hypre-space/hypre/archive/$(HYPRE_VERSION).tar.gz \
			-O hypre-$(HYPRE_VERSION).tar.gz
# Download MFront source code
MFRONT_DOWNLOAD = wget -c https://github.com/thelfer/tfel/archive/refs/tags/TFEL-$(MFRONT_VERSION).tar.gz \
			-O mfront-$(MFRONT_VERSION).tar.gz
# Download MGIS source code
MGIS_DOWNLOAD = wget -c https://github.com/thelfer/MFrontGenericInterfaceSupport/archive/refs/tags/MFrontGenericInterfaceSupport-$(MGIS_VERSION).tar.gz \
			-O mgis-$(MGIS_VERSION).tar.gz
# Download PETSc source code
PETSC_DOWNLOAD = wget -c https://gitlab.com/petsc/petsc/-/archive/v$(PETSC_VERSION)/petsc-v$(PETSC_VERSION).tar.gz \
			-O petsc-$(PETSC_VERSION).tar.gz
# Download MUMPS source code
MUMPS_DOWNLOAD = wget -c https://web.cels.anl.gov/projects/petsc/download/externalpackages/MUMPS_$(MUMPS_VERSION).tar.gz \
			-O mumps-$(MUMPS_VERSION).tar.gz
# Download MUMPS source code
MUMPS_SEQ_DOWNLOAD = wget -c https://ftp.mcs.anl.gov/pub/petsc/externalpackages/MUMPS_$(MUMPS_SEQ_VERSION).tar.gz \
			-O mumps-seq-$(MUMPS_SEQ_VERSION).tar.gz
# Download METIS source code
METIS_DOWNLOAD = wget -c  https://github.com/mohd-afeef-badri/psd-dependencies/raw/refs/heads/main/metis-$(METIS_VERSION).tar.gz \
			-O metis-$(METIS_VERSION).tar.gz
# Download SLEPc source code
SLEPC_DOWNLOAD = wget -c https://gitlab.com/slepc/slepc/-/archive/v$(SLEPC_VERSION)/slepc-v$(SLEPC_VERSION).tar.gz \
			-O slepc-$(SLEPC_VERSION).tar.gz
# Download ParMETIS source code
PARMETIS_DOWNLOAD = wget -c https://github.com/mohd-afeef-badri/psd-dependencies/raw/refs/heads/main/parmetis-$(PARMETIS_VERSION).tar.gz \
			-O parmetis-$(PARMETIS_VERSION).tar.gz
# Download SCALAPACK source code
SCALAPACK_DOWNLOAD = wget -c https://github.com/Reference-ScaLAPACK/scalapack/archive/v$(SCALAPACK_VERSION).tar.gz \
			-O scalapack-$(SCALAPACK_VERSION).tar.gz
# Download SCALAPACK source code
F2CBLASLAPACK_DOWNLOAD = wget -c https://web.cels.anl.gov/projects/petsc/download/externalpackages/f2cblaslapack-$(F2CBLASLAPACK_VERSION).q2.tar.gz \
			-O f2cblaslapack-$(F2CBLASLAPACK_VERSION).tar.gz
# Download parmmg source code
PARMMG_DOWNLOAD = wget https://github.com/MmgTools/ParMmg/archive/v$(PARMMG_VERSION).tar.gz \
			-O parmmg-$(PARMMG_VERSION).tar.gz
# Download mmg source code
MMG_DOWNLOAD = wget https://github.com/MmgTools/mmg/archive/v$(MMG_VERSION).tar.gz \
			-O mmg-$(MMG_VERSION).tar.gz
# Download ptscotch source code
PTSCOTCH_DOWNLOAD = wget https://gitlab.inria.fr/scotch/scotch/-/archive/v$(PTSCOTCH_VERSION)/scotch-v$(PTSCOTCH_VERSION).tar.gz \
			-O ptscotch-$(PTSCOTCH_VERSION).tar.gz
# Download mshmet source code
MSHMET_DOWNLOAD = wget https://raw.githubusercontent.com/FreeFem/FreeFEM-3rdparties/refs/heads/main/mshmet.$(MSHMET_VERSION).tgz \
			-O mshmet.$(MSHMET_VERSION).tgz
# Download PETSc patch for cmake
PETSC_PATCH_DOWNLOAD = wget https://raw.githubusercontent.com/FreeFem/FreeFem-sources/refs/heads/master/3rdparty/ff-petsc/petsc-cmake-seq.patch
# Download Ipopt source code
IPOPT_DOWNLOAD = wget -c http://www.coin-or.org/download/source/Ipopt/Ipopt-$(IPOPT_VERSION).tgz \
			-O Ipopt-$(IPOPT_VERSION).tgz
# Download MEDCoupling and its standalone build dependencies from source
MEDCOUPLING_DOWNLOAD = wget -c https://github.com/SalomePlatform/medcoupling/archive/refs/tags/$(MEDCOUPLING_TAG).tar.gz \
			-O medcoupling-$(MEDCOUPLING_VERSION).tar.gz
MEDCOUPLING_CONFIGURATION_DOWNLOAD = wget -c https://github.com/SalomePlatform/configuration/archive/refs/tags/$(MEDCOUPLING_TAG).tar.gz \
			-O medcoupling-configuration-$(MEDCOUPLING_CONFIGURATION_VERSION).tar.gz
HDF5_MED_DOWNLOAD = wget -c https://github.com/HDFGroup/hdf5/archive/refs/tags/$(HDF5_MED_TAG).tar.gz \
			-O hdf5-med-$(HDF5_MED_VERSION).tar.gz
MEDFILE_DOWNLOAD = wget -c https://files.salome-platform.org/Salome/medfile/med-$(MEDFILE_VERSION).tar.gz \
			-O med-$(MEDFILE_VERSION).tar.gz

#----------------------------------------------------------------------------------------
# This section in Makefile.am defines a target "all-local" that is executed during the
# build process. It depends on the targets "make-directories" and the list of make commands
# in the variable "LIST_MAKE_EXECUTE". It is used to build the required directories and
# execute the specified make commands.
#----------------------------------------------------------------------------------------

# Target to build the necessary directories and execute the specified make commands
all-local: $(LIST_MAKE_EXECUTE)
	@echo ""


#----------------------------------------------------------------------------------------
# This section in Makefile.am defines a target "make-directories" used to create specific
# directories during the build process. It is responsible for creating directories for
# binaries, documentation, and manual pages in the specified installation prefix.
#----------------------------------------------------------------------------------------

# Target to create the required directories during the build process
make-directories:
	@mkdir -p ${prefix}/bin
	@mkdir -p ${prefix}/share/doc
	@mkdir -p ${prefix}/share/man


#----------------------------------------------------------------------------------------
# This section in Makefile.am defines a target "download-dependencies" that is responsible
# for downloading the required source code for various libraries and dependencies if the
# source files are not already present in the build directory. It performs a series of
# checks for each library version and downloads the respective source code if necessary.
#----------------------------------------------------------------------------------------

# Target to download the required source code for libraries and dependencies
if BUILDMEDCOUPLING
MEDCOUPLING_DOWNLOAD_TARGETS = \
	medcoupling-$(MEDCOUPLING_VERSION).tar.gz \
	medcoupling-configuration-$(MEDCOUPLING_CONFIGURATION_VERSION).tar.gz \
	hdf5-med-$(HDF5_MED_VERSION).tar.gz \
	med-$(MEDFILE_VERSION).tar.gz
else !BUILDMEDCOUPLING
MEDCOUPLING_DOWNLOAD_TARGETS =
endif

download-dependencies: $(MEDCOUPLING_DOWNLOAD_TARGETS)
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
	@if [ ! -f mumps-seq-$(MUMPS_SEQ_VERSION).tar.gz ]; then \
		$(MUMPS_SEQ_DOWNLOAD); \
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
	@if [ ! -f f2cblaslapack-$(F2CBLASLAPACK_VERSION).tar.gz ]; then \
		$(F2CBLASLAPACK_DOWNLOAD); \
	fi
	@if [ ! -f petsc-cmake-seq.patch ]; then \
		$(PETSC_PATCH_DOWNLOAD); \
	fi
	@if [ ! -f Ipopt-$(IPOPT_VERSION).tgz ]; then \
		$(IPOPT_DOWNLOAD); \
	fi
	@if [ ! -f parmmg-$(PARMMG_VERSION).tar.gz ]; then \
		$(PARMMG_DOWNLOAD); \
	fi
	@if [ ! -f mmg-$(MMG_VERSION).tar.gz ]; then \
		$(MMG_DOWNLOAD); \
	fi
	@if [ ! -f ptscotch-$(PTSCOTCH_VERSION).tar.gz ]; then \
		$(PTSCOTCH_DOWNLOAD); \
	fi
	@if [ ! -f mshmet.$(MSHMET_VERSION).tgz ]; then \
		$(MSHMET_DOWNLOAD); \
	fi
	@if [ ! -f gmsh-$(GMSH_VERSION).tar.gz ]; then \
		$(GMSH_DOWNLOAD); \
	fi
#--------------------------------------------------------------------------------
# Gmsh installation
# This section in Makefile.am deals with the Gmsh installation process.
# - It downloads Gmsh from the specified version GMSH_VERSION unless the user provides
#   an override by providing the ext/gmsh-$(GMSH_VERSION).tar.gz file.
#--------------------------------------------------------------------------------

# Target gmsh-build: This target is used to build Gmsh using the downloaded source code.
gmsh-build: gmsh-$(GMSH_VERSION)/gmsh-$(GMSH_VERSION).$(SO_SUFFIX)

gmsh-$(GMSH_VERSION)/gmsh-$(GMSH_VERSION).$(SO_SUFFIX): gmsh-$(GMSH_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling gmsh for you be patient:   "
	@echo "*============================================================*"
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
	touch gmsh-$(GMSH_VERSION).$(SO_SUFFIX)
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing Gmsh v$(GMSH_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""

# Target gmsh-$(GMSH_VERSION).tar.gz: Downloads Gmsh unless BUILDZIPPEDDEPENDENCIES flag is set
gmsh-$(GMSH_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(GMSH_DOWNLOAD)
endif

#--------------------------------------------------------------------------------
# MFront installation
#  - Download from wget version MFRONT_VERSION
#  - User can override download by providing ext/mfront-$(MFRONT_VERSION).tar.gz
#--------------------------------------------------------------------------------

define mfrontenv
export PATH=${prefix}/bin:\$$PATH \nexport LD_LIBRARY_PATH=${prefix}/lib:\$$LD_LIBRARY_PATH
endef

if MAC
CMAKESYSROOT = '-DCMAKE_OSX_SYSROOT=$(SYSROOT)'
else !MAC
CMAKESYSROOT = 
endif

mfront-build: mfront-$(MFRONT_VERSION)/build/mfront/src/libTFELMFront.$(SO_SUFFIX)


mfront-$(MFRONT_VERSION)/build/mfront/src/libTFELMFront.$(SO_SUFFIX): mfront-$(MFRONT_VERSION).tar.gz
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
	cmake .. \
		-DCMAKE_BUILD_TYPE=Release \
		-Denable-cxx-17=ON \
		-DCMAKE_INSTALL_PREFIX=${prefix} \
		-DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX) \
		$(CMAKESYSROOT) \
		&& \
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

ENVFILE=envvar.tmp

mgis-build: mgis-$(MGIS_VERSION)/build/src/libMFrontGenericInterface.$(SO_SUFFIX)

mgis-$(MGIS_VERSION)/build/src/libMFrontGenericInterface.$(SO_SUFFIX): mgis-$(MGIS_VERSION).tar.gz
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
	cmake .. \
		-DCMAKE_BUILD_TYPE=Release \
		-Denable-cxx-17=ON \
		-DCMAKE_INSTALL_PREFIX=${prefix}  \
		-DCMAKE_C_COMPILER=$(CC)  \
		-DCMAKE_CXX_COMPILER=$(CXX)  \
		$(CMAKESYSROOT) \
		&& \
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

PETSC_ARCH_PSD  =fr

if MAC
PETSC_DEP = \
  --download-metis=$(CURDIR)/metis-$(METIS_VERSION).tar.gz \
  --download-parmetis=$(CURDIR)/parmetis-$(PARMETIS_VERSION).tar.gz \
  --download-mmg=$(CURDIR)/mmg-$(MMG_VERSION).tar.gz \
  --download-slepc=$(CURDIR)/slepc-$(SLEPC_VERSION).tar.gz \
  --download-hpddm=$(CURDIR)/hpddm-$(HPDDM_VERSION).tar.gz \
  --with-ptscotch-dir=/opt/homebrew \
  --with-blas-lapack-dir=/opt/homebrew/opt/openblas \
  --with-cc=$(MPICC) COPTFLAGS='$(CXXFLAGS)' \
  --with-cxx=$(MPICXX) CXXOPTFLAGS='$(CXXFLAGS)' \
  --with-cxx-dialect=C++11 \
  --with-mpiexec=$(MPIRUN) \
  --with-fc=0
else !MAC
PETSC_DEP = \
  --download-mumps=$(CURDIR)/mumps-$(MUMPS_VERSION).tar.gz \
  --download-metis=$(CURDIR)/metis-$(METIS_VERSION).tar.gz \
  --download-parmetis=$(CURDIR)/parmetis-$(PARMETIS_VERSION).tar.gz \
  --download-slepc=$(CURDIR)/slepc-$(SLEPC_VERSION).tar.gz \
  --download-hpddm=$(CURDIR)/hpddm-$(HPDDM_VERSION).tar.gz \
  --download-hypre=$(CURDIR)/hypre-$(HYPRE_VERSION).tar.gz \
  --download-scalapack=$(CURDIR)/scalapack-$(SCALAPACK_VERSION).tar.gz \
  --download-parmmg=$(CURDIR)/parmmg-$(PARMMG_VERSION).tar.gz \
  --download-mmg=$(CURDIR)/mmg-$(MMG_VERSION).tar.gz \
  --download-ptscotch=$(CURDIR)/ptscotch-$(PTSCOTCH_VERSION).tar.gz \
  --download-f2cblaslapack=$(CURDIR)/f2cblaslapack-$(F2CBLASLAPACK_VERSION).tar.gz \
  --with-cc=$(MPICC) COPTFLAGS='$(CXXFLAGS)' \
  --with-cxx=$(MPICXX) CXXOPTFLAGS='$(CXXFLAGS)' \
  --with-cxx-dialect=C++11 \
  --with-mpiexec=$(MPIRUN) \
  --with-fc=$(MPIFC) FOPTFLAGS='$(FCFLAGS)'
endif



petsc-build: petsc-$(PETSC_VERSION)/$(PETSC_ARCH_PSD)/lib/libpetsc.$(SO_SUFFIX)

petsc-$(PETSC_VERSION)/$(PETSC_ARCH_PSD)/lib/libpetsc.$(SO_SUFFIX): petsc-cmake-seq.patch petsc-$(PETSC_VERSION).tar.gz
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
	--with-cudac=0 --with-ssl=0 --with-x=0 \
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
#  - User can override download by providing ext/freefem-$(FREEFEM_VERSION).tar.gz
#--------------------------------------------------------------------------------

if MAC
MAKE_AND_INSTALL_FREEFEM = make -j4 && make MacOsX && sudo make install
FREEFEM_DEP = \
	--without-petsc_complex \
	--disable-superlu \
	--enable-download_mshmet \
	--with-hdf5=no
else !MAC
MAKE_AND_INSTALL_FREEFEM = make -j4 && make install
FREEFEM_DEP = \
	--without-petsc_complex \
	--disable-superlu \
	--enable-download_mshmet \
	--enable-download_ipopt \
	--enable-download_pipe \
	--enable-download_mumps_seq \
	--with-hdf5=no
endif

freefem-build: freefem-$(FREEFEM_VERSION)/plugin/mpi/PETSc.$(SO_SUFFIX)

freefem-$(FREEFEM_VERSION)/plugin/mpi/PETSc.$(SO_SUFFIX): freefem-$(FREEFEM_VERSION).tar.gz
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
	mkdir ./3rdparty/pkg             && \
	cp ../mshmet.$(MSHMET_VERSION).tgz ./3rdparty/pkg/. && \
	cp ../Ipopt-$(IPOPT_VERSION).tgz ./3rdparty/pkg/. && \
	cp ../mumps-seq-$(MUMPS_SEQ_VERSION).tar.gz ./3rdparty/pkg/MUMPS_$(MUMPS_SEQ_VERSION).tar.gz && \
	patch -p1 < ../FreeFEM.patch     && \
	autoreconf -i                    && \
	./configure \
	--prefix=${prefix} \
	CXX=$(MPICXX) CXXOPTFLAGS='$(CXXFLAGS)'  \
	FC=$(MPIFC) FCOPTFLAGS='$(FCFLAGS)'  \
	FFLAGS='-std=legacy' \
	CC=$(MPICC) CCOPTFLAGS='$(CXXFLAGS)' \
	F77=$(F77) F77OPTFLAGS='$(FCFLAGS)' \
	MPICXX=$(MPICXX) MPICXXOPTFLAGS='$(CXXFLAGS)' \
	MPIRUN=$(MPIRUN) \
	$(FREEFEM_DEP) &&  \
	$(MAKE_AND_INSTALL_FREEFEM)

freefem-$(FREEFEM_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(FREEFEM_DOWNLOAD)
endif

#--------------------------------------------------------------------------------
# MEDCOUPLING installation
#  - Build MEDCoupling from the tagged GitHub source archive
#  - Build matching HDF5 and MEDFile prerequisites instead of using a SALOME binary bundle
#  - Users can override downloads by providing the four source archives in ext/
#--------------------------------------------------------------------------------

MEDCOUPLING_ROOT=$(prefix)/MEDCOUPLING-$(MEDCOUPLING_VERSION)
HDF5_MED_INSTALL=$(MEDCOUPLING_ROOT)/INSTALL/hdf5
MEDFILE_INSTALL=$(MEDCOUPLING_ROOT)/INSTALL/medfile
MEDCOUPLING_INSTALL=$(MEDCOUPLING_ROOT)/INSTALL/MEDCOUPLING

medcoupling-$(MEDCOUPLING_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(MEDCOUPLING_DOWNLOAD)
endif

medcoupling-configuration-$(MEDCOUPLING_CONFIGURATION_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(MEDCOUPLING_CONFIGURATION_DOWNLOAD)
endif

hdf5-med-$(HDF5_MED_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(HDF5_MED_DOWNLOAD)
endif

med-$(MEDFILE_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(MEDFILE_DOWNLOAD)
endif

# Cmake flags for MEDCOUPLING build
CMAKE_FLAGS_MEDCOUPLING = \
-DCMAKE_BUILD_TYPE=Release \
-DMEDCOUPLING_ENABLE_PYTHON=OFF \
-DMEDCOUPLING_ENABLE_PARTITIONER=OFF \
-DMEDCOUPLING_ENABLE_RENUMBER=OFF \
-DMEDCOUPLING_PARTITIONER_METIS=OFF \
-DMEDCOUPLING_PARTITIONER_PARMETIS=OFF \
-DMEDCOUPLING_PARTITIONER_SCOTCH=OFF \
-DMEDCOUPLING_PARTITIONER_PTSCOTCH=OFF \
-DMEDCOUPLING_MICROMED=OFF \
-DMEDCOUPLING_BUILD_DOC=OFF \
-DMEDCOUPLING_WITH_FILE_EXAMPLES=OFF \
-DCMAKE_EXE_LINKER_FLAGS="-D_GLIBCXX_USE_CXX11_ABI=1" \
-DMEDCOUPLING_BUILD_TESTS=OFF \
-DMEDCOUPLING_BUILD_PY_TESTS=OFF \
-DMEDCOUPLING_USE_MPI=OFF \
-DMEDCOUPLING_USE_64BIT_IDS=ON \
-DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
-DCONFIGURATION_ROOT_DIR=$(CURDIR)/configuration-$(MEDCOUPLING_CONFIGURATION_VERSION) \
-DHDF5_ROOT_DIR=$(HDF5_MED_INSTALL) \
-DMEDFILE_ROOT_DIR=$(MEDFILE_INSTALL) \
-DCMAKE_INSTALL_RPATH="$(MEDCOUPLING_INSTALL)/lib;$(MEDFILE_INSTALL)/lib;$(HDF5_MED_INSTALL)/lib" \
-DCMAKE_INSTALL_PREFIX=$(MEDCOUPLING_INSTALL)

medcoupling-build: $(MEDCOUPLING_INSTALL)/lib/libmedcoupling.$(SO_SUFFIX)

$(HDF5_MED_INSTALL)/lib/libhdf5.$(SO_SUFFIX): hdf5-med-$(HDF5_MED_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling HDF5 v$(HDF5_MED_VERSION) for MEDCoupling"
	@echo "*============================================================*"
	rm -rf hdf5-med-$(HDF5_MED_VERSION) hdf5-$(HDF5_MED_TAG)
	tar -xzf hdf5-med-$(HDF5_MED_VERSION).tar.gz
	mv hdf5-$(HDF5_MED_TAG) hdf5-med-$(HDF5_MED_VERSION)
	cd hdf5-med-$(HDF5_MED_VERSION) && \
	./configure \
		--prefix=$(HDF5_MED_INSTALL) \
		--enable-shared \
		--disable-static \
		--disable-fortran \
		--disable-cxx \
		--disable-tests \
		--enable-hl && \
	$(MAKE) -j8 && $(MAKE) -j8 install

$(MEDFILE_INSTALL)/lib/libmedC.$(SO_SUFFIX): med-$(MEDFILE_VERSION).tar.gz $(HDF5_MED_INSTALL)/lib/libhdf5.$(SO_SUFFIX)
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling MEDFile v$(MEDFILE_VERSION) for MEDCoupling"
	@echo "*============================================================*"
	rm -rf med-$(MEDFILE_VERSION)
	tar -xzf med-$(MEDFILE_VERSION).tar.gz
	cd med-$(MEDFILE_VERSION) && \
	rm -rf build && mkdir -p build
	cd med-$(MEDFILE_VERSION)/build && \
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_C_FLAGS=-std=gnu17 \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		-DCMAKE_Fortran_COMPILER=NOTFOUND \
		-DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
		-DHDF5_ROOT_DIR=$(HDF5_MED_INSTALL) \
		-DMED_MEDINT_TYPE=long \
		-DMEDFILE_BUILD_TESTS=OFF \
		-DMEDFILE_BUILD_SHARED_LIBS=ON \
		-DMEDFILE_BUILD_STATIC_LIBS=OFF \
		-DMEDFILE_BUILD_PYTHON=OFF \
		-DMEDFILE_BUILD_DOC=OFF \
		-DMEDFILE_INSTALL_DOC=OFF \
		-DMEDFILE_USE_MPI=OFF \
		-DCMAKE_INSTALL_RPATH=$(HDF5_MED_INSTALL)/lib \
		-DCMAKE_INSTALL_PREFIX=$(MEDFILE_INSTALL) \
		.. && \
	$(MAKE) -j8 && $(MAKE) -j8 install

$(MEDCOUPLING_INSTALL)/lib/libmedcoupling.$(SO_SUFFIX): \
		medcoupling-$(MEDCOUPLING_VERSION).tar.gz \
		medcoupling-configuration-$(MEDCOUPLING_CONFIGURATION_VERSION).tar.gz \
		$(MEDFILE_INSTALL)/lib/libmedC.$(SO_SUFFIX)
	@echo ""
	@echo "*============================================================*"
	@echo " MEDCOUPLING installation began for you be patient:   "
	@echo "   - Building GitHub tag $(MEDCOUPLING_TAG)"
	@echo "   - to override, provide the MEDCoupling source archives in ext/"
	@echo "*============================================================*"
	@echo ""
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring MEDCoupling and configuration source archives"
	@echo "*---------------------------------*"
	@echo ""
	rm -rf medcoupling-$(MEDCOUPLING_VERSION) medcoupling-$(MEDCOUPLING_ARCHIVE_VERSION)
	rm -rf configuration-$(MEDCOUPLING_CONFIGURATION_VERSION) configuration-$(MEDCOUPLING_ARCHIVE_VERSION)
	tar -xzf medcoupling-$(MEDCOUPLING_VERSION).tar.gz
	mv medcoupling-$(MEDCOUPLING_ARCHIVE_VERSION) medcoupling-$(MEDCOUPLING_VERSION)
	tar -xzf medcoupling-configuration-$(MEDCOUPLING_CONFIGURATION_VERSION).tar.gz
	mv configuration-$(MEDCOUPLING_ARCHIVE_VERSION) configuration-$(MEDCOUPLING_CONFIGURATION_VERSION)
	@echo ""
	@echo "*---------------------------------*"
	@echo "   creating the MEDCoupling build directory"
	@echo "*---------------------------------*"
	@echo ""
	cd medcoupling-$(MEDCOUPLING_VERSION) && \
	rm -rf build && mkdir -p build
	@echo ""
	@echo "*---------------------------------*"
	@echo "   compiling medcoupling"
	@echo "*---------------------------------*"
	@echo ""
	cd medcoupling-$(MEDCOUPLING_VERSION)/build && \
	cmake $(CMAKE_FLAGS_MEDCOUPLING) \
		-DCMAKE_C_COMPILER=$(CC) \
		-DCMAKE_CXX_COMPILER=$(CXX) \
		.. && \
	$(MAKE) -j8 && $(MAKE) -j8 install
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing MEDCoupling v$(MEDCOUPLING_VERSION)"
	@echo "*---------------------------------*"
	@echo ""


#--------------------------------------------------------------------------------
# This section in Makefile.am defines two targets: "clean-local" and
# "distclean-local" used for cleaning files generated during the build process.
#--------------------------------------------------------------------------------

# Target clean-local: Clean generated files in the current directory
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""
	rm  -f *~ *.mesh *.pvd *.vtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log


# Target distclean-local: Clean automake generated files and dependencies
distclean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning all generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in petsc-cmake-seq.patch
	rm  -rf petsc-cmake-seq.patch
	rm  -rf petsc-$(PETSC_VERSION) freefem-$(FREEFEM_VERSION) mfront-$(MFRONT_VERSION) MEDCOUPLING-$(MEDCOUPLING_VERSION)
	rm  -rf medcoupling-$(MEDCOUPLING_VERSION) configuration-$(MEDCOUPLING_CONFIGURATION_VERSION)
	rm  -rf hdf5-med-$(HDF5_MED_VERSION) med-$(MEDFILE_VERSION)
	rm  -rf hypre-$(HYPRE_VERSION) hpddm-$(HPDDM_VERSION) f2cblaslapack-$(F2CBLASLAPACK_VERSION)
	rm  -rf mumps-$(MUMPS_VERSION) mumps-seq-$(MUMPS_SEQ_VERSION) metis-$(METIS_VERSION)
	rm  -rf parmetis-$(PARMETIS_VERSION) slepc-$(SLEPC_VERSION) scalapack-$(SCALAPACK_VERSION)
	rm  -rf parmmg-$(PARMMG_VERSION) mmg-$(MMG_VERSION) ptscotch-$(PTSCOTCH_VERSION)
	rm  -rf mgis-$(MGIS_VERSION) gmsh-$(GMSH_VERSION) Ipopt-$(IPOPT_VERSION).tgz mshmet.$(MSHMET_VERSION).tgz
	rm  -rf *.tar.gz

#--------------------------------------------------------------------------------
# This section in Makefile.am defines a target "install-exec-local" that is used to
# install executable files. However, in this case, it does not perform any installation
# and only displays a message indicating that there is nothing to install.
#--------------------------------------------------------------------------------

# Target install-exec-local: Nothing to install, just display a message
install-exec-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Nothing to install here:"
	@echo "*============================================================*"
	@echo ""
