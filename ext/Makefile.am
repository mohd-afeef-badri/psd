
MFRONT_VERSION=3.4.0
MGIS_VERSION=1.2
PETSC_VERSION=3.16.1
FREEFEM_VERSION=4.10
GMSH_VERSION=4.8.4

ENVFILE=envvar.tmp


if BUILDDEPENDENCIES
LIST_MAKE_EXECUTE = petsc-build \
FreeFEM-build \
mfront-build \
mgis-build \
gmsh-build
else
LIST_MAKE_EXECUTE = \
mfront-build \
mgis-build
endif

if MAC
MAKEANDINSTALL = make -j4 && make MacOsX && cp -r ./idp ${prefix}/lib/ff++/$(FREEFEM_VERSION)/.
else !MAC
MAKEANDINSTALL = make -j4 && make install
endif

define mfrontenv
export PATH=${prefix}/bin:\$$PATH \nexport LD_LIBRARY_PATH=${prefix}/lib:\$$LD_LIBRARY_PATH
endef

all-local: $(LIST_MAKE_EXECUTE)
	@echo ""

gmsh-build:
if MAC
	@echo ""
	@echo "*============================================================*"
	@echo " IMPORTANT NOTE:   "
	@echo "*============================================================*"
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
else
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is installing gmsh for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	tar -xf gmsh-sources.tar.xz
	cd gmsh-$(GMSH_VERSION) && cp -rf ./bin/* ${prefix}/bin/. && cp -rf ./share/doc/*  ${prefix}/share/doc/.  && cp -rf ./share/man  ${prefix}/share/man
endif

mfront-build: Mfront-sources-$(MFRONT_VERSION)/build/mfront/src/libTFELMFront.so


Mfront-sources-$(MFRONT_VERSION)/build/mfront/src/libTFELMFront.so: Mfront-sources.tar.xz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling mfront for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	tar -xf Mfront-sources.tar.xz
	cd Mfront-sources-$(MFRONT_VERSION) &&  rm -rf build && mkdir -p build && cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-cxx-17=ON -DCMAKE_INSTALL_PREFIX=${prefix} -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)  && \
	make -j8 && make install
	@echo -e "$(mfrontenv)" > ${prefix}/mfront-env.sh
	@echo ""

mgis-build: Mgis-sources-$(MGIS_VERSION)/build/src/libMFrontGenericInterface.so

Mgis-sources-$(MGIS_VERSION)/build/src/libMFrontGenericInterface.so: Mgis-sources.tar.xz
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling Mgis for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	tar -xf Mgis-sources.tar.xz
	cd Mgis-sources-$(MGIS_VERSION) && rm -rf build && mkdir -p build && cd build && \
	echo "PATH=${prefix}/bin:$$PATH" > $(ENVFILE)   && echo "LD_LIBRARY_PATH=${prefix}/lib:$$LD_LIBRARY_PATH"  >> $(ENVFILE) && \
	eval `cat $(ENVFILE)` && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-cxx-17=ON -DCMAKE_INSTALL_PREFIX=${prefix}  -DCMAKE_C_COMPILER=$(CC)  -DCMAKE_CXX_COMPILER=$(CXX)  && \
	make -j8 && make install
	@echo ""


petsc-build:
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling PETSc, HPDDM, METIS, PARMETIS, SCALAPACK,   "
	@echo " MUMPS, SLEPC, SUITSPAR for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	export PETSCPKG=$(CURDIR)
	tar -xf Petsc-sources.tar.xz
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
	PETSC_ARCH=fr
	cd petsc-$(PETSC_VERSION) &&  \
	make PETSC_DIR=$(CURDIR)/petsc-$(PETSC_VERSION) PETSC_ARCH=fr all &&  \
	make PETSC_DIR=$(CURDIR)/petsc-$(PETSC_VERSION) PETSC_ARCH=fr install


FreeFEM-build:
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling FreeFEM for you be patient:"
	@echo "*============================================================*"
	@echo ""
	tar -xf FreeFem-sources.tar.xz
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
