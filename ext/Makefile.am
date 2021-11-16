
MFRONT_VERSION=3.4.0
MGIS_VERSION=1.2
PETSC_VERSION=3.16.1
FREEFEM_VERSION=4.10

define mfrontenv
export PATH=${prefix}/bin:\$$PATH \nexport LD_LIBRARY_PATH=${prefix}/lib:\$$LD_LIBRARY_PATH
endef
  
all-local: petsc-build FreeFEM-build mfront-build mgis-build
	@echo ""

mfront-build:
if BUILDDEPENDENCIES
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling mfront for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	tar -xf Mfront-sources-$(MFRONT_VERSION).tar.xz
	cd Mfront-sources-$(MFRONT_VERSION) &&  rm -rf build && mkdir -p build && cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${prefix} -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_CXX_FLAGS='$(CXXFLAGS)' && \
	make -j4 && make install
	@echo -e "$(mfrontenv)" > ${prefix}/mfront-env.sh
else !BUILDDEPENDENCIES	
	@echo ""
endif

mgis-build:
if BUILDDEPENDENCIES
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling Mgis for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	source ${prefix}/mfront-env.sh
	tar -xf Mgis-sources-$(MGIS_VERSION).tar.xz
	cd Mgis-sources-$(MGIS_VERSION) && rm -rf build && mkdir -p build && cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-c-bindings=ON -DCMAKE_INSTALL_PREFIX=${prefix} -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_CXX_FLAGS='$(CXXFLAGS)' && \
	make -j4 && make install	
else !BUILDDEPENDENCIES	
	@echo ""
endif

petsc-build:
if BUILDDEPENDENCIES
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
	--with-mpiexec=$(MPIRUN) \
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
else !BUILDDEPENDENCIES	
	@echo ""
endif


FreeFEM-build:
if BUILDDEPENDENCIES
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
	MPIRUN=$(MPIRUN) \
	--disable-superlu \
	--with-hdf5=no &&  \
	make -j4 && make install
else !BUILDDEPENDENCIES	
	@echo ""
endif
	
check-local:
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

install-exec-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Nothing to install here:"
	@echo "*============================================================*"
	@echo ""
