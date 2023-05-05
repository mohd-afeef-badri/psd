

# Dependencies 

With PSD we do not intend to recreate the wheel, as such we rely on multiple dependencies. PSD has some essential prerequisites without which PSD will not function. The table below enlists the dependencies, and also provides a link from where the tarball (`.tar.gz`) file can be obtained for these. 



### Version of packaes 

```bash
MFRONT_VERSION=4.0.0

MGIS_VERSION=2.0

PETSC_VERSION=3.18.2

FREEFEM_VERSION=4.12

GMSH_VERSION=4.10.4

MUMPS_VERSION=5.5.1

METIS_VERSION=5.1.0

PARMETIS_VERSION=4.0.3

SLEPC_VERSION=d9df183c341775ffc91510ec6827e13db44a25cd

SCALAPACK_VERSION=5bad7487f496c811192334640ce4d3fc5f88144b

HPDDM_VERSION=2.2.2

HYPRE_VERSION=2.25.0
```



### Where to find the tarballs 



| Package name                                                 | Used for                                  | Version | Link (Linux)                                                 |
| ------------------------------------------------------------ | ----------------------------------------- | ------- | ------------------------------------------------------------ |
| [Gmsh](http://gmsh.info/)                                    | meshing                                   | 4.10.4  | https://gmsh.info/bin/Linux/gmsh-4.10.4-Linux64.tgz          |
| [FreeFEM](https://freefem.org/)                              | finite element kernel                     | 4.12    | https://github.com/FreeFem/FreeFem-sources/archive/refs/tags/v4.12.tar.gz |
| [hpddm](https://github.com/hpddm/hpddm)                      | parallel linear algebra                   | 2.2.2   | https://github.com/hpddm/hpddm/archive/v2.2.2.tar.gz         |
| [METIS](https://github.com/KarypisLab/METIS)                 | mesh partitioning                         | 5.1.0   | https://bitbucket.org/petsc/pkg-metis/get/v5.1.0-p10.tar.gz  |
| [MFRONT](https://github.com/thelfer/tfel)                    | non-linear law kernel                     | 3.4.0   | https://github.com/thelfer/tfel/archive/refs/tags/TFEL-4.0.0.tar.gz |
| [MGIS](https://github.com/thelfer/MFrontGenericInterfaceSupport) | non-linear law kernel                     | 2.0     | https://github.com/thelfer/MFrontGenericInterfaceSupport/archive/refs/tags/MFrontGenericInterfaceSupport-2.0.tar.gz |
| [MUMPS](http://mumps.enseeiht.fr/)                           | direct linear algebra solver              | 5.5.1   | https://graal.ens-lyon.fr/MUMPS/MUMPS_5.5.1.tar.gz           |
| [PARMETIS](https://github.com/KarypisLab/ParMETIS)           | parallel mesh partitioning                | 4.0.3   | https://bitbucket.org/petsc/pkg-parmetis/get/v4.0.3-p8.tar.gz |
| [PETSc](https://petsc.org)                                   | preconditioning and linear system solving | 3.18.2  | https://gitlab.com/petsc/petsc/-/archive/v3.18.2/petsc-v3.18.2.tar.gz |
| [SCALAPACK](http://www.netlib.org/scalapack/)                | linear algebra routines                   | 2.2.0   | https://github.com/Reference-ScaLAPACK/scalapack/archive/5bad7487f496c811192334640ce4d3fc5f88144b.tar.gz |
| [SLEPc](https://slepc.upv.es/)                               | parallel eigenvalue solver                | 3.17.0  | https://gitlab.com/slepc/slepc/-/archive/d9df183c341775ffc91510ec6827e13db44a25cd/slepc-d9df183c341775ffc91510ec6827e13db44a25cd.tar.gz |
|                                                              |                                           |         |                                                              |

** For `SLEPc` a specific git hash `d9df183c341775ffc91510ec6827e13db44a25cd` is used.

** For `SCALAPACK` a specific git hash `5bad7487f496c811192334640ce4d3fc5f88144b` is used.

### How to get packages 

```bash
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
SLEPC_DOWNLOAD   =  wget -c https://gitlab.com/slepc/slepc/-/archive/$(SLEPC_VERSION)/slepc-$(SLEPC_VERSION).tar.gz \
                       -O slepc-$(SLEPC_VERSION).tar.gz
PARMETIS_DOWNLOAD    =  wget -c https://bitbucket.org/petsc/pkg-parmetis/get/v$(PARMETIS_VERSION)-p8.tar.gz \
                       -O parmetis-$(PARMETIS_VERSION).tar.gz
SCALAPACK_DOWNLOAD   =  wget -c https://github.com/Reference-ScaLAPACK/scalapack/archive/$(SCALAPACK_VERSION).tar.gz \
                       -O scalapack-$(SCALAPACK_VERSION).tar.gz
SALOME_DOWNLOAD      =  wget -c https://files.salome-platform.org/Salome/Salome$(SALOME_VERSION)/SALOME-$(SALOME_VERSION)$(SALOME_OS_TAG)$(SALOME_TAG).tar.gz \
                       -O salome-$(SALOME_VERSION).tar.gz
PETSC_PATCH_DOWNLOAD = wget https://raw.githubusercontent.com/FreeFem/FreeFem-sources/master/3rdparty/ff-petsc/petsc-cmake-seq.patch

```

