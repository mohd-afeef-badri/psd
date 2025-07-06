#----------------------------------------------------------------------------------------
# This section in Makefile.am defines version variables for various libraries used in the
# project. These variables specify the versions of external dependencies used during the
# build process.
#----------------------------------------------------------------------------------------

# Define the version of MEDCOUPLLING library
MEDCOUPLING_VERSION=9.14.0

# Define the version of Ipopt library
IPOPT_VERSION=3.12.4

# Define the version of parmmg
PARMMG_VERSION=beb4147b7b29a2891e1a55745ff95863e93bcc0d

# Define the version of mmg
MMG_VERSION=2263f92c032a26672c2625230a0689e29e8d96c6

# Define the version of mshmet
MSHMET_VERSION=2012.04.25

# Define the version of ptscotch
PTSCOTCH_VERSION=7.0.5

# Define the version of MFront library
MFRONT_VERSION=5.0.0

# Define the version of MGIS library
MGIS_VERSION=3.0

# Define the version of PETSc library
PETSC_VERSION=3.22.2

# Define the version of FreeFEM library
FREEFEM_VERSION=4.15

# Define the version of Gmsh library
GMSH_VERSION=4.11.1

# Define the version of MUMPS Seq library
MUMPS_SEQ_VERSION=5.0.2

# Define the version of MUMPS library
MUMPS_VERSION=5.7.3

# Define the version of METIS library
METIS_VERSION=5.1.0

# Define the version of ParMETIS library
PARMETIS_VERSION=4.0.3

# Define the version of SLEPc library
SLEPC_VERSION=3.22.0

# Define the version of SCALAPACK library
SCALAPACK_VERSION=5bad7487f496c811192334640ce4d3fc5f88144b

# Define the version of HPDDM library
HPDDM_VERSION=2.3.1

# Define the version of HYPRE library
HYPRE_VERSION=2.31.0

# Define the version of BLAS/LAPACK library
F2CBLASLAPACK_VERSION=3.8.0

#----------------------------------------------------------------------------------------
# Check if BUILDDEPENDENCIES flag is set to determine the build execution list
#----------------------------------------------------------------------------------------

if BUILDDEPENDENCIES
# Check if BUILDDEPENDENCIES flag is set to determine the build execution list
LIST_MAKE_EXECUTE = download-dependencies \
gmsh-build \
mfront-build \
mgis-build \
petsc-build \
freefem-build \
medcoupling-build
else
# If BUILDDEPENDENCIES is not set, leave the list empty
LIST_MAKE_EXECUTE =
endif


#----------------------------------------------------------------------------------------
# This section in Makefile.am contains various download commands to fetch the source code
# for different libraries and dependencies used in the project. The download URLs are
# specified based on the library versions and the target operating system.
#----------------------------------------------------------------------------------------

# Check if MAC flag is set to determine the Gmsh download URL
# If MAC flag is set, download Gmsh for macOS with ARM architecture
# If MAC flag is not set, download Gmsh for Linux

if MAC
GMSH_DOWNLOAD    = wget -c https://gmsh.info/bin/macOS/gmsh-$(GMSH_VERSION)-MacOSARM.dmg \
			-O gmsh-$(GMSH_VERSION).dmg
else !MAC
GMSH_DOWNLOAD    = wget -c https://gmsh.info/bin/Linux/gmsh-$(GMSH_VERSION)-Linux64.tgz \
			-O gmsh-$(GMSH_VERSION).tar.gz
endif

# Define download commands for different libraries and dependencies

# Download FreeFEM source code
FREEFEM_DOWNLOAD = wget -c https://github.com/FreeFem/FreeFem-sources/archive/refs/tags/v$(FREEFEM_VERSION).tar.gz \
			-O freefem-$(FREEFEM_VERSION).tar.gz
# Download HPDDM source code
HPDDM_DOWNLOAD = wget -c https://github.com/hpddm/hpddm/archive/v$(HPDDM_VERSION).tar.gz \
			-O hpddm-$(HPDDM_VERSION).tar.gz
# Download HYPRE source code
HYPRE_DOWNLOAD = wget -c https://github.com/hypre-space/hypre/archive/v$(HYPRE_VERSION).tar.gz \
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
METIS_DOWNLOAD = wget -c https://bitbucket.org/petsc/pkg-metis/get/v$(METIS_VERSION)-p11.tar.gz \
			-O metis-$(METIS_VERSION).tar.gz
# Download SLEPc source code
SLEPC_DOWNLOAD = wget -c https://gitlab.com/slepc/slepc/-/archive/v$(SLEPC_VERSION)/slepc-v$(SLEPC_VERSION).tar.gz \
			-O slepc-$(SLEPC_VERSION).tar.gz
# Download ParMETIS source code
PARMETIS_DOWNLOAD = wget -c https://bitbucket.org/petsc/pkg-parmetis/get/v$(PARMETIS_VERSION)-p9.tar.gz \
			-O parmetis-$(PARMETIS_VERSION).tar.gz
# Download SCALAPACK source code
SCALAPACK_DOWNLOAD = wget -c https://github.com/Reference-ScaLAPACK/scalapack/archive/$(SCALAPACK_VERSION).tar.gz \
			-O scalapack-$(SCALAPACK_VERSION).tar.gz
# Download SCALAPACK source code
F2CBLASLAPACK_DOWNLOAD = wget -c https://web.cels.anl.gov/projects/petsc/download/externalpackages/f2cblaslapack-$(F2CBLASLAPACK_VERSION).q2.tar.gz \
			-O f2cblaslapack-$(F2CBLASLAPACK_VERSION).tar.gz
# Download parmmg source code
PARMMG_DOWNLOAD = wget https://github.com/MmgTools/ParMmg/archive/$(PARMMG_VERSION).tar.gz \
			-O parmmg-$(PARMMG_VERSION).tar.gz
# Download mmg source code
MMG_DOWNLOAD = wget https://github.com/MmgTools/mmg/archive/$(MMG_VERSION).tar.gz \
			-O mmg-$(MMG_VERSION).tar.gz
# Download ptscotch source code
PTSCOTCH_DOWNLOAD = wget https://gitlab.inria.fr/scotch/scotch/-/archive/v$(PTSCOTCH_VERSION)/scotch-v$(PTSCOTCH_VERSION).tar.gz \
			-O ptscotch-$(PTSCOTCH_VERSION).tar.gz
# Download mshmet source code
MSHMET_DOWNLOAD = wget https://raw.githubusercontent.com/FreeFem/FreeFEM-3rdparties/refs/heads/main/mshmet.$(MSHMET_VERSION).tgz \
			-O mshmet.$(MSHMET_VERSION).tgz
# Download PETSc patch for cmake
PETSC_PATCH_DOWNLOAD = wget https://raw.githubusercontent.com/FreeFem/FreeFem-sources/refs/tags/v$(FREEFEM_VERSION)/3rdparty/ff-petsc/petsc-cmake-seq.patch
# Download Ipopt source code
IPOPT_DOWNLOAD = wget -c http://www.coin-or.org/download/source/Ipopt/Ipopt-$(IPOPT_VERSION).tgz \
			-O Ipopt-$(IPOPT_VERSION).tgz
# Download MEDCoupling source code
MEDCOUPLING_DOWNLOAD =	wget -c \
  			--header="User-Agent: Mozilla/5.0 (X11; Linux x86_64)" \
  			--header="Referer: https://www.salome-platform.org/" \
  			https://files.salome-platform.org/Salome/Salome$(MEDCOUPLING_VERSION)/MEDCOUPLING-$(MEDCOUPLING_VERSION).tar.gz \
  			-O MEDCOUPLING-$(MEDCOUPLING_VERSION).tar.gz

#----------------------------------------------------------------------------------------
# This section in Makefile.am defines a target "all-local" that is executed during the
# build process. It depends on the targets "make-directories" and the list of make commands
# in the variable "LIST_MAKE_EXECUTE". It is used to build the required directories and
# execute the specified make commands.
#----------------------------------------------------------------------------------------

# Target to build the necessary directories and execute the specified make commands
all-local: make-directories $(LIST_MAKE_EXECUTE)
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
download-dependencies:
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
	@if [ ! -f MEDCOUPLING-$(MEDCOUPLING_VERSION).tar.gz ]; then \
		$(MEDCOUPLING_DOWNLOAD); \
	fi
if MAC
	@if [ ! -f gmsh-$(GMSH_VERSION).dmg ]; then \
		$(GMSH_DOWNLOAD); \
    fi
else !MAC
	@if [ ! -f gmsh-$(GMSH_VERSION).tar.gz ]; then \
		$(GMSH_DOWNLOAD); \
	fi
endif

#--------------------------------------------------------------------------------
# Gmsh installation
# This section in Makefile.am deals with the Gmsh installation process.
# - It specifies that Gmsh is not working for MAC OS.
# - It downloads Gmsh from the specified version GMSH_VERSION unless the user provides
#   an override by providing the ext/gmsh-$(GMSH_VERSION).tar.gz file.
#--------------------------------------------------------------------------------


if MAC
GMSHZIP=dmg
else !MAC
GMSHZIP=tar.gz
endif

# Target gmsh-build: This target is used to build Gmsh using the downloaded source code.
gmsh-build: gmsh-$(GMSH_VERSION)/gmsh-$(GMSH_VERSION).$(SO_SUFFIX)


# Check if MAC flag is set to determine the installation procedure for macOS
# If not on MAC, install Gmsh for Linux
gmsh-$(GMSH_VERSION)/gmsh-$(GMSH_VERSION).$(SO_SUFFIX): gmsh-$(GMSH_VERSION).$(GMSHZIP)
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling gmsh for you be patient:   "
	@echo "*============================================================*"
	@echo ""
if MAC
	@echo ""
	@echo "*---------------------------------*"
	@echo "   using hdiutil for gmsh-$(GMSH_VERSION).dmg"
	@echo "*---------------------------------*"
	@echo ""
	yes | hdiutil attach ./gmsh-$(GMSH_VERSION).dmg	 && \
	cp -r /Volumes/gmsh-$(GMSH_VERSION)-MACOSARM/Gmsh.app ${prefix}/gmsh-$(GMSH_VERSION) && \
	hdiutil detach /Volumes/gmsh-$(GMSH_VERSION)-MACOSARM
	rm -f ${prefix}/bin/gmsh
	ln -s ${prefix}/gmsh-$(GMSH_VERSION)/Contents/MacOS/gmsh ${prefix}/bin/gmsh
	mkdir -p gmsh-$(GMSH_VERSION)
	touch gmsh-$(GMSH_VERSION)/gmsh-$(GMSH_VERSION).$(SO_SUFFIX)
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
	touch gmsh-$(GMSH_VERSION).$(SO_SUFFIX)
	@echo ""
	@echo "*---------------------------------*"
	@echo " finished installing Gmsh v$(GMSH_VERSION)   "
	@echo "*---------------------------------*"
	@echo ""
endif


# Target gmsh-$(GMSH_VERSION).$(GMSHZIP): Downloads Gmsh unless BUILDZIPPEDDEPENDENCIES flag is set
gmsh-$(GMSH_VERSION).$(GMSHZIP):
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

PETSC_ARCH_PSD  =fr

PETSC_DEP = --download-mumps=$(CURDIR)/mumps-$(MUMPS_VERSION).tar.gz         \
	--download-metis=$(CURDIR)/metis-$(METIS_VERSION).tar.gz             \
	--download-parmetis=$(CURDIR)/parmetis-$(PARMETIS_VERSION).tar.gz    \
	--download-slepc=$(CURDIR)/slepc-$(SLEPC_VERSION).tar.gz             \
	--download-hpddm=$(CURDIR)/hpddm-$(HPDDM_VERSION).tar.gz             \
	--download-hypre=$(CURDIR)/hypre-$(HYPRE_VERSION).tar.gz             \
	--download-scalapack=$(CURDIR)/scalapack-$(SCALAPACK_VERSION).tar.gz \
	--download-parmmg=$(CURDIR)/parmmg-$(PARMMG_VERSION).tar.gz          \
	--download-mmg=$(CURDIR)/mmg-$(MMG_VERSION).tar.gz                   \
	--download-ptscotch=$(CURDIR)/ptscotch-$(PTSCOTCH_VERSION).tar.gz    \
	--download-f2cblaslapack=$(CURDIR)/f2cblaslapack-$(F2CBLASLAPACK_VERSION).tar.gz

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
	--with-cc=$(MPICC) COPTFLAGS='$(CXXFLAGS)' \
	--with-cxx=$(MPICXX) CXXOPTFLAGS='$(CXXFLAGS)' --with-cxx-dialect=C++11 \
	--with-mpiexec=$(MPIRUN) \
	--with-fc=$(MPIFC) FOPTFLAGS='$(FCFLAGS)' \
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
MAKEANDINSTALL = make -j4 && make MacOsX && sudo make install
else !MAC
MAKEANDINSTALL = make -j4 && make install
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
	--without-petsc_complex \
	--disable-superlu \
	--enable-download_mshmet \
	--enable-download_ipopt \
	--enable-download_pipe \
	--enable-download_mumps_seq \
	--with-hdf5=no &&  \
	$(MAKEANDINSTALL)

freefem-$(FREEFEM_VERSION).tar.gz:
if !BUILDZIPPEDDEPENDENCIES
	$(FREEFEM_DOWNLOAD)
endif

#--------------------------------------------------------------------------------
# MEDCOUPLING installation
#  - Download from wget version MEDCOUPLING_VERSION
#  - User can override download by providing ext/freefem-$(MEDCOUPLING_VERSION).tar.gz
#--------------------------------------------------------------------------------

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
-DCMAKE_EXE_LINKER_FLAGS="-D_GLIBCXX_USE_CXX11_ABI=1" \
-DMEDCOUPLING_BUILD_TESTS=OFF \
-DSALOME_USE_MPI=ON \
-DCMAKE_INSTALL_PREFIX=./../INSTALL/MEDCOUPLING

medcoupling-build: MEDCOUPLING-$(MEDCOUPLING_VERSION)/INSTALL/MEDCOUPLING/lib/libmedcoupling.so

MEDCOUPLING-$(MEDCOUPLING_VERSION)/INSTALL/MEDCOUPLING/lib/libmedcoupling.so: MEDCOUPLING-$(MEDCOUPLING_VERSION).tar.gz
	@echo ""
	@echo "*============================================================*"
	@echo " MEDCOUPLING installation began for you be patient:   "
	@echo "   - Download using wget version $(MEDCOUPLING_VERSION)"
	@echo "   - to overide provide ext/MEDCOUPLING-$(MEDCOUPLING_VERSION).tar.gz"
	@echo "*============================================================*"
	@echo ""
	@echo ""
	@echo "*---------------------------------*"
	@echo "   untaring MEDCOUPLING-$(MEDCOUPLING_VERSION).tar.gz"
	@echo "*---------------------------------*"
	@echo ""
	tar -xzf MEDCOUPLING-$(MEDCOUPLING_VERSION).tar.gz
	@echo ""
	@echo "*---------------------------------*"
	@echo "   creating BUILD and INSTALL directories"
	@echo "*---------------------------------*"
	@echo ""
	cd MEDCOUPLING-$(MEDCOUPLING_VERSION)   && \
	mkdir -p BUILD   && \
	mkdir -p INSTALL
	@echo ""
	@echo "*---------------------------------*"
	@echo "   installing medcoupling"
	@echo "*---------------------------------*"
	@echo ""
	cd MEDCOUPLING-$(MEDCOUPLING_VERSION)/SOURCES       && \
	tar -xzf ./../ARCHIVES/MEDCOUPLING.tgz && \
	cd ./../BUILD && \
	source ./../env_launch.sh && \
	cmake  $(CMAKE_FLAGS_MEDCOUPLING) ./../SOURCES/MEDCOUPLING && \
	make -j all && \
	source ./../env_launch.sh && make install -j all

#--------------------------------------------------------------------------------
# This section in Makefile.am defines a target "check-local" used to perform checks
# or tests related to the build. However, in this case, it does not perform any checks
# and only displays a message indicating that there is nothing to check.
#--------------------------------------------------------------------------------

# Target check-local: Nothing to check, just display a message
check-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Nothing to check here:"
	@echo "*============================================================*"
	@echo ""


#--------------------------------------------------------------------------------
# This section in Makefile.am defines two targets: "clean-local" and
# "maintainer-clean-local" used for cleaning files generated during the build process.
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


# Target maintainer-clean-local: Clean automake generated files and dependencies
maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""
	rm  -rf Makefile Makefile.in petsc-cmake-seq.patch
	rm  -rf petsc-cmake-seq.patch
	rm  -rf petsc-$(PETSC_VERSION) freefem-$(FREEFEM_VERSION) mfront-$(MFRONT_VERSION)
	rm  -rf mgis-$(MGIS_VERSION) gmsh-$(GMSH_VERSION)
	rm *.tar.gz

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
