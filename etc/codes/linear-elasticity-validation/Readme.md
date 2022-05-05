
## Linear-elasticity validation test

### Introduction

Linear-elasticity module of PSD will be validated. More verbosely, small strain for a 2D isotropic linear-elastic medium is targeted here. We intend to test the plane-stess and plain-strain approximation. 


Let us consider the case of a cantilever beam modeled as a 2D medium of dimensions $[L\times H]$.  This is simply represented by the mesh `bar.mesh` which is rectangular domain triangular  mesh. We intend to calculate the FEM deformation of this beam and compare it againt the Euler-Bernoulli beam theory displacement. 

### Modeling the problem


For this problem two material parameters are defined:
- Young’s modulus $E$ and 
- Poisson ratio $\nu$. 

these are used to express the Lamé coefficients ($\lambda, \mu$) for the natural (no prestress)  state of the medium: 

$$\lambda
= \dfrac{E\nu}{(1+\nu)(1-2\nu)}, \quad \mu =
\dfrac{E}{2(1+\nu)}.$$

Mathematically,  the linear elastic isotropic medium the constitutive relation between the stress tensor $\boldsymbol{\sigma}$ and the strain tensor $\boldsymbol{\varepsilon}$ for the plain-strain case is given by:


$$\boldsymbol{\sigma}
= \lambda \text{tr}(\boldsymbol{\varepsilon})\mathbf{1} +
2\mu\boldsymbol{\varepsilon}$$




As explained above we work either in plane strain or in plane stress conditions. Irrespective of the choice, we will work only with a 2D displacement vector $\boldsymbol{u}=(u_x,u_y)$. We subsequently define the symmetric strain tensor $\boldsymbol{\varepsilon}$ as follows:

$$\begin{split}\boldsymbol{\varepsilon} = \begin{bmatrix}
\varepsilon_{xx} & \varepsilon_{xy} \\ \varepsilon_{xy} &
\varepsilon_{yy} \end{bmatrix}\end{split}$$

This is sufficent for the plain-strain case. However, for the plain-stress case  the out-of-plane stress and strain components $\sigma_{zz}$ and $\varepsilon_{zz}$ are considered,these given by
$$\sigma_{zz}=\lambda(\varepsilon_{xx}+\varepsilon_{yy}) \quad\text{and}\quad  \varepsilon_{zz}=-\dfrac{\lambda}{\lambda+2\mu}(\varepsilon_{xx}+\varepsilon_{yy}) $$.


Using these $\sigma_{zz}$  and $\varepsilon_{zz}$ we  construct the constitutive-relation for 2D plane stress case:

$$\boldsymbol{\sigma} = \lambda^\prime
\text{tr}(\boldsymbol{\varepsilon})\mathbf{1} +
2\mu\boldsymbol{\varepsilon}$$


where $\boldsymbol{\sigma}, \boldsymbol{\varepsilon}, \mathbf{1}$ are 2D tensors and with $\lambda^\prime = \dfrac{2\lambda\mu}{\lambda+2\mu}$. Hence, the 2D constitutive relation is identical to the plane strain case by changing only the value of the Lamé coefficient $\lambda$.


## FEM variational formulation

The continuum mechanics variational formulation (obtained from the virtual work principle) is given by:


$$\text{Find } \boldsymbol{u}\in \mathcal{V}(\Omega) \text{:}$$
$$ \int_{\Omega}
\boldsymbol{\sigma}(\boldsymbol{u}):\boldsymbol{\varepsilon}(\boldsymbol{v})
d\Omega = \int_{\Omega} \boldsymbol{f}\cdot\boldsymbol{v}
d\Omega \quad \forall\boldsymbol{v} \in \mathcal{V}(\Omega)$$.

using the constitutive-relation we can write this as 

$$ \int_{\Omega} 2\mu \varepsilon_{ij}(\boldsymbol{u})\varepsilon_{ij}(\boldsymbol{v})  + \int_{\Omega} \lambda \varepsilon_{ii}(\boldsymbol{u})  \varepsilon_{jj}(\boldsymbol{v}) = \int_{\Omega} \boldsymbol{f}\cdot\boldsymbol{v}
d\Omega \quad \forall\boldsymbol{v} \in \mathcal{V}(\Omega) $$


here, $\mathcal{V}(\Omega)$ represented the second order closed finite element subspace of $H^1(\Omega)^2$.

In this problem we have add the source condition - a uniformly distributed loading -
$$\boldsymbol{f}=(0,-\rho\times g)$$
corresponding to the beam self-weight.

Additionally we supply Dirichlet boundary condition, i.e., a fixed displacements are imposed on the left part of the rectangular mesh.

## Expected solution: the validation process

For this simple case, the maximal deflection (at the free end of the bar) is compared against the analytical solution  from Euler-Bernoulli beam theory which is given by:

$$u_y^{\text{EB}} = \dfrac{\rho g L^4}{8EI}$$


Running the code we compare the $u_y^{\text{PSD}} $ obtained from PSD and the one given by the Euler-Bernoulli beam theory above:

- for plain-stress case we get

```bash
Max deflection Uy 0.00582129
Analytical Max deflection Uy 0.00585938
```

- for plain-strain case we get

```bash
Max deflection Uy 0.00529665
Analytical Max deflection Uy 0.00585938
```
