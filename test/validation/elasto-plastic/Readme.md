# Validation test for  elasto-plastic problems with PSD

## Introducetion 
We use a non-linear problem of the incremental analysis of an elasto-plastic Von-Mises material for validation. More verbosely, s 2D test (in $x-y$) will be considered. The problem of interest is a quarter of a cylinder (with external radius $R_e$ and internal radius $R_i$). Boundary conditions correspond to symmetry conditions on the bottom horizontal $y=0$ and left vertical borders $x=0$. Loading consists of a uniform pressure (traction boundary) on the internal boundary.  Load (pressure) $q$ will be progressively increased from 0 to $q_{\text{lim}}=\frac{2}{\sqrt3}\sigma_0\text{log}(\frac{R_e}{R_i})$ which is the analytical collapse load for a perfectly-plastic material (no hardening).

## Mathematical model 

The material is represented by an isotropic elasto-plastic von Mises yield condition of uniaxial strength $\sigma_0$ and with isotropic hardening of modulus $H$. The yield condition is thus given by:

$$f(\sigma)=\sqrt{\frac{3}{2}s:s}-\sigma_0-Hp\le0$$

where $p$ is the cumulated equivalent plastic strain and $s$ denoting the deviatoric elastic stress $s = \text{dev} \sigma_{\text{elas}}$. The hardening modulus can also be related to a tangent elastic modulus $E_t=\frac{EH}{E+H}$.

Due to the simple expression of the von Mises criterion, the return mapping procedure is completely analytical (with linear isotropic hardening). We point out that the two-dimensional nature of the problem will be impose keeping track of the out-of-plane $\varepsilon^p_{zz}$ plastic strain and dealing with representations of stress/strain states including the $zz$ component.

## Results 

The load-displacement curve is plotted and compared to the one available in literature.
