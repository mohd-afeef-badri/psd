
MFRONT_VERSION=3.4.0
MGIS_VERSION=1.2
PETSC_VERSION=3.15.0
FREEFEM_VERSION=4.9

define mfrontenv
export PATH=${prefix}/bin:\$$PATH \nexport LD_LIBRARY_PATH=${prefix}/lib:\$$LD_LIBRARY_PATH
endef
  
all-local: petsc-build FreeFEM-build mgis-build mfront-build
	@echo ""

mfront-build:
if BUILDDEPENDENCIES
	@echo ""
	@echo "*============================================================*"
	@echo " PSD is compiling mfront for you be patient:   "
	@echo "*============================================================*"
	@echo ""
	tar -xf Mfront-sources-$(MFRONT_VERSION).tar.xz
	cd Mfront-sources-$(MFRONT_VERSION) && mkdir -p build && cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${prefix} -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_CXX_FLAGS=$(CXXFLAGS) && \
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
	cd Mgis-sources-$(MGIS_VERSION) && mkdir -p build && cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -Denable-c-bindings=ON -DCMAKE_INSTALL_PREFIX=${prefix} -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_CXX_FLAGS=$(CXXFLAGS) && \
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
	tar -xf Petsc-sources-$(PETSC_VERSION).tar.xz
	cd petsc-$(PETSC_VERSION) && ./configure \
--with-scalar-type=real \
--prefix=${prefix}/ff-petsc/r \
--with-cc=mpicc COPTFLAGS=$(CCFLAGS) \
--with-cxx=mpicxx CXXOPTFLAGS=$(CXXFLAGS) --with-cxx-dialect=C++11 \
-with-mpiexec=mpirun \
--with-fc=mpif90 FOPTFLAGS=$(FCFLAGS) \
--with-cudac=0 --with-ssl=0 --with-x=0 \
--with-debugging	=no \
--with-fortran-bindings=no \
--download-mumps=$(CURDIR)/mumps-sources.tar.gz \
--download-metis=$(CURDIR)/metis-sources.tar.gz \
--download-parmetis=$(CURDIR)/parmetis-sources.tar.gz  \
--download-slepc=$(CURDIR)/slepc-sources.tar.gz \
--download-hpddm=$(CURDIR)/hpddm-sources.tar.gz \
--download-scalapack=$(CURDIR)/scalapack-sources.tar.gz &&  \
	make PETSC_DIR=$(CURDIR)/petsc-$(PETSC_VERSION) PETSC_ARCH=arch-linux-c-debug all &&  \
	make PETSC_DIR=$(CURDIR)/petsc-$(PETSC_VERSION) PETSC_ARCH=arch-linux-c-debug install
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
	tar -xf FreeFem-sources-$(FREEFEM_VERSION).tar.xz
	cd FreeFem-sources-$(FREEFEM_VERSION) && autoreconf -i && \
	./configure \
--prefix=${prefix} \
CXX="mpicxx -O3 -mtune=native"  \
FC="gfortran -O3 -mtune=native" \
CC="gcc -O3 -mtune=native" \
F77="gfortran -O3 -mtune=native" \
MPICXX="mpicxx -O3 -mtune=native" \
MPIRUN=mpirun \
--enable-optim \
--with-hdf5=no &&  \
	make && make install
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
