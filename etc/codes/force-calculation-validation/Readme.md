# Computing reaction forces in PSD

The question tackled in this validation test is how to compute reaction forces on  a boundary. In many simulations, we Often compute the resulting reaction force on a part of the boundary or on the full boundary at the time of the  post-processing. 

PSD offers to calculate the reaction forces using two methods: i) using the stress-field associated with the computed displacement and iii) by using virtual work principle (weak formulation). We will see that  stress-field approach (`-getreactionforce -reactionforce stress_based`) is not an accurate way of computing reaction forces  whereas another   using the virtual work principle (`-getreactionforce -reactionforce variational_based`) is more consistent and robust approch.


## A validation test 

Let us demonstarte the two approaches with case of 2D cantilever beam problem. A linear-elasticity test of a 2D reactangular bar of dimensions $(L\times H)$ representing a cantilever-beam clamped on the left and under uniform body forces  $\boldsymbol{f}=[f_x,f_y]$. 

We are interested by computing the horizontal and vertical reaction forces $R_x$  and $R_y$on the left boundary. In the present simple case analytical  equations for $R_x$ and $R_y$ exist, they are explicitly given by:



$$ R_x = \int_{x=0}\boldsymbol{T}\cdot \boldsymbol{e}_x \partial\Omega = \int_{x=0}
(-\sigma_{xx}) \partial\Omega = -f_x \cdot L \cdot H$$


$$ R_y = \int_{x=0}\boldsymbol{T}\cdot \boldsymbol{e}_y \partial\Omega = \int_{x=0}
(-\sigma_{xy}) \partial\Omega = -f_y \cdot L \cdot H$$




###  First method: using the post-processed stress `-reactionforce stress_based`

The first, and most widely used, method for computing the above reactions relies on the stress-field computed from the obtained displacement $\sigma(\boldsymbol{u})$ and perform integration over the left boundary. Unfortunately, this procedure does not ensure an exact computation as seen below. Indeed, the stress-field, implicitly known only at the quadrature points only is extended to the structure boundary and does not satisfy global equilibrium anymore. See below, the test results:

```bash
PSD vertical reaction Ry          :: 3.8184
PSD horizontal reaction Rx        :: -0.586969
 ----------------------------------
Analytic vertical reaction Ry      :: 5
Analytic horizontal reaction Rx    :: -0.5
 ----------------------------------
Error vertical reaction Ry         :: 23.632  %
Error horizontal reaction Rx       :: 17.3937 %
```
###   Second method: using the work of internal forces `-reactionforce varf_based`


The second approach relies on the virtual work principle (or weak formulation) which writes in the present case:


$$\int_\Omega \sigma(\boldsymbol{u}):\varepsilon (\boldsymbol{v})
 =\int_\Omega \boldsymbol{f}\cdot\boldsymbol{v}  +
\int_{\partial \Omega_N} \boldsymbol{T}\cdot\boldsymbol{v}
\quad \forall \boldsymbol{v}\in V  $$


this is the variational formulation of linear-elasticity without Dirichlet boundary conditions.

The solution $\boldsymbol{u}$ is precisely obtained by enforcing the Dirichlet boundary conditions on $\boldsymbol{v}$ such that:

$$\int_\Omega \sigma(\boldsymbol{u}):\varepsilon (\boldsymbol{v})
 =\int_\Omega \boldsymbol{f}\cdot\boldsymbol{v}  +
\int_{\partial \Omega_N} \boldsymbol{T}\cdot\boldsymbol{v}
\quad \forall \boldsymbol{v}\in V \text{ and } \boldsymbol{v}=0
\text{ on }\partial \Omega_D$$

Defining the **residual**:

$$Res(v) = \int_\Omega \sigma(\boldsymbol{u}):\varepsilon
(\boldsymbol{v})  - \int_\Omega
\boldsymbol{f}\cdot\boldsymbol{v}  - \int_{\partial
\Omega_N} \boldsymbol{T}\cdot\boldsymbol{v} =
a(\boldsymbol{u}, \boldsymbol{v}) -\ell(\boldsymbol{v})$$


we have that $Res(v)= 0$ if $\boldsymbol{v}=0$ on $\partial \Omega_D$.

Now, if $\boldsymbol{v}\neq0$ on $\partial \Omega_D$, say, for instance, $\boldsymbol{v}=(1,0)$ on $\partial \Omega_D$, we have that:


$$Res(v) = \int_{\partial \Omega_D}
\boldsymbol{T}\cdot\boldsymbol{v} = \int_{\partial \Omega_D}
\boldsymbol{T}_x = \int_{\partial \Omega_D}
-\sigma_{xx} = R_x$$


Similarly, we obtain the vertical reaction $R_y$ by considering $\boldsymbol{v}=(0,1)$.

As regards implementation, the residual is defined using the action of the bilinear form on the displacement solution $Res = Ax$. We then define boundary conditions on the left boundary and apply them to an empty Function to define the required test field $v$. We observe that the computed reactions are now robust.

```bash
PSD vertical reaction Ry        :: 4.97902
PSD horizontal reaction Rx      :: -0.497902
 ----------------------------------
Analytic vertical reaction Ry   :: 5
Analytic horizontal reaction Rx :: -0.5
 ----------------------------------
Error vertical reaction Ry      :: 0.419618 %
Error horizontal reaction Rx    :: 0.419618 %
```
