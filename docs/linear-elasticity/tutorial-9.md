# Using Mfront-PSD interface

This tutorial details one to use PSD-MFront interface for linear elasticity problem. The same problem from tutorial 1 is repeated, however now MFront is used for building certain finite element essentials. It is advised to follow this tutorial after tutorial 1. Note that, linear elasticity merely provides means of getting started with Mfornt, the real potential lies in using nonlinear materials and laws which Mfront provides. So this tutorial should be considered as baptism to the world of PSD-MFront which we believe has a lot of potential to solve some non trivial problems.

We reintroduce the problem from tutorial 1, an example of a 2D bar which bends under its own load -- typical case of linear elasticity.   A bar 5 m in length and 1 m in width, and is supposed to be made up of a material with density $\rho=8\times 10^3$, Youngs modulus $E=200\times 10^9$, and Poissons ratio $\nu=0.3$.


![The 2D clamped bar problem.](./Images/3d-mechanical.png)
*Figure: The 2D clamped bar problem.*

## Step 1: Preprocessing

First step in a PSD simulation is PSD preprocessing, at this step you tell PSD what kind of physics, boundary conditions, approximations, mesh, etc are you expecting to solve. More importantly for this tutorial we will signify to PSD that MFront has to be used.

In the terminal `cd` to the folder `/home/PSD-tutorials/linear-elasticity`. Launch `PSD\_PreProcess` from the terminal, to do so run the following command.

<pre><code>PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -useMfront
</code></pre>

After the `PSD\_PreProcess` runs successfully you should see many `.edp` files in your current folder.

**What do the arguments mean?**

- `-problem linear_elasticity` → solving linear elasticity
- `-dimension 2` → 2D simulation
- `-bodyforceconditions 1` → apply a body force on the domain
- `-dirichletconditions 1` → one Dirichlet borders
- `-postprocess u` → enable ParaView output
- `-useMfront` → activates MFront interface for PSD


At this stage the input properties $E,\nu$ can be mentioned in `ControlParameters.edp`, use `E = 200.e9`, and `nu = 0.3`. In contrast to tutorial 1, notice that these values of `E` and `nu` are fed to a vector `PropertyValues = [E, nu];`  verbosed by `PropertyNames   = "YoungModulus PoissonRatio";`. We also signify that we will be solving linear elasticity via `MforntMaterialBehaviour   = "Elasticity";` and also `MaterialHypothesis = "GENERALISEDPLANESTRAIN";` which signifies the hypothesis to be used for the Linear elasticity. The `MaterialHypothesis` accepts `"GENERALISEDPLANESTRAIN"`,  `"PLANESTRAIN"`, `"PLANESTRESS"`,  and  `"TRIDIMENSIONAL"` as arguments. `PropertyValues`, `PropertyNames`, and `MaterialHypothesis`  will eventually be provided to MFront in `FemParameters.edp` file via `PsdMfrontHandler(...)` function *User is encouraged to have a look at `FemParameters.edp` file.   The volumetric body force condition is mentioned in the same file via variable `Fbc0Fy -78480.0`, i.e ($\rho*g=8.e3*(-9.81)=-78480.0$). One can also provide the mesh to be used in `ControlParameters.edp`, via `ThName = "../Meshes/2D/bar.msh"` (*note that mesh can also be provided in the next step*) .In addition variable `Fbc0On 1` has to be provided in order to indicate the volume (region) for which the body force is acting, here `1` is the integer volume tag of the mesh. Dirichlet boundary conditions are also provided in `ControlParameters.edp`. To provide the clamped boundary condition the variables `Dbc0On 2`, `Dbc0Ux 0.`, and `Dbc0Uy 0.` are used, which means for Dirichlet border `2` (`Dbc0On 2`) where `2` is the clamped border label of the mesh Dirichlet constrain is applied and `Dbc0Ux 0.`, `Dbc0Uy 0` i.e., the clamped end condition ($u_x=u_y=0$).


## Step 2: Solving

Use 2 cores:

As PSD is a parallel solver, let us use 4 cores to solve the 2D bar case. To do so enter the following command:

<pre><code>PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
</code></pre>

## Step 3: Postprocessing

Launch ParaView and open the `.pvd` file in `PSD/Solver/VTUs_DATE_TIME`.

![Partitioned mesh](./Images/3d-mechanical-part.png)
![Warped displacement field](./Images/3d-mechanical-result.png)

*Figure: Mechanical piece test results. Partitioned mesh (left) and warped displacement field (right).*

You are all done with your 2D linear-elasticty simulation with Mfront interface.

## How and what is being done in PSD-MFront interface? 

To explain how PSD-MFront interface works we will compare how a PSD solver acts when using MFront or without. In other words what is different when `-useMfront` is used at preprocessing. Note that ultimately the problem results (displacement fields, stresses, strains) will be the same.

To put it briefly, what MFront does for linear elasticity problem here is build the Material tensor (stiffness matrix) at each quadrature point. So, there are two points

- We need to communicate to Mfront the nature of the problem and the material involved.
- We need to provide Mfornt the stiffness matrix at each quadrature point so that it can fill it up.

The two raised points are handled using `PsdMfrontHandler(...)` in `FemParameters.edp` file.

Firstly, the arguments `E = 200.e9`,  `nu = 0.3`, `MforntMaterialBehaviour   = "Elasticity";`, `PropertyValues = [E, nu];`, `PropertyNames   = "YoungModulus PoissonRatio";`, `PropertyValues = [E, nu];` and   `MaterialHypothesis = "GENERALISEDPLANESTRAIN";` form `ControlParameters.edp` takes care of the first point (the nature of the problem and the material involved). The latter three arguments well define that we have a 2D problem, with given values of properties ($E, \nu$). The snippet from `ControlParameters.edp` (produced after using `-useMfront` argument for `PSD\_PreProcess`) file shows these variables which define the nature of the problem and characteristics of material involved

<pre><code>
//============================================================================
//                   ------- Material parameters -------
// -------------------------------------------------------------------
//  E, nu : Modulus of Elasticity and Poisson ratio of the material
//  PropertyNames : String of material property names (space seperated)
//                  that are provided to Mfront.
//  PropertyValues : Values of material properties provided to Mfront
//
// -------------------------------------------------------------------
//  NOTE:     Please note that PropertyNames should be the same as
//            as in the Elasticity.mfront file
// -------------------------------------------------------------------
//============================================================================

  macro E()  200.e9  //
  macro nu() 0.3     //

  string    MaterialBehaviour  = "Elasticity";
  string    MaterialHypothesis = "GENERALISEDPLANESTRAIN";
  string    PropertyNames      = "YoungModulus PoissonRatio";
  real[int] PropertyValues     = [ E, nu ];
</code></pre>


Secondly, the to get the stiffness matrix from Mfornt we use a quadrature finite element space with vector finite elements built on it (6 components) that represent the 6 components of symmetric material tensor ($\mathbb R^{3 \times 3}$). The snippet from `MeshAndFeSpace.edp` file shows the 6 component Quadrature finite element space for building material tensor.

<pre><code>
//==============================================================================
// ------- The finite element space  -------
// ----------------------------------------------------------------------------
//  Qh       : Quadratur finite element space  for material tensor
//             FEQF2 implies 3 dof for a triangular cell in the mesh
//             A vectorial FEM space is built with 6 components
//==============================================================================

 fespace Qh  ( Th ,[ FEQF2, FEQF2, FEQF2,
                           FEQF2, FEQF2,
                                  FEQF2] );
</code></pre>


Finally in file `FemParameters.edp` the `PsdMfrontHandler()` is called to build the material tensor `Mt` provided with the previously built material properties and nature of problem. Please see the snippet below

<pre><code>
//============================================================================
// ------- Material Tensor using Quadrature FE space -------
// -------------------------------------------------------------------
// Mt[int]  : is an array of finite element variable belonging to quadratu
//            re space Qh. This array is used  to define components of the
//            material tensor. 3X3 in 2D and 6X6 in 3D
//            In 2D the material tensor looks like
//
//         [ 2*mu+lambda ,  lambda      , 0 ]    [ Mt11 , Mt12 , Mt13 ]
//   Mt =  [ lambda      ,  2*mu+lambda , 0 ] =  [ Mt12 , Mt22 , Mt23 ]
//         [   0         ,     0        , mu]    [ Mt13 , Mt23 , Mt33 ]
//
// PsdMfrontHandler : is a function in mfront interface that helps
//                    building the material tensor  Mt  given with
//                    material prpts.  from  ControlParameters.edp
//============================================================================
  Qh [ Mt11 ,  Mt12 , Mt13 ,
              Mt22 , Mt23 ,
                     Mt33 ];

  PsdMfrontHandler( MaterialBehaviour                                   ,
                    mfrontBehaviourHypothesis = MaterialHypothesis      ,
                    mfrontPropertyNames       = PropertyNames           ,
                    mfrontPropertyValues      = PropertyValues          ,
                    mfrontMaterialTensor      = Mt11[]
                         );
</code></pre>

Note that in the snippet above you might be seeing `Mt11[]` being provided as `mfrontMaterialTensor`, in fact the `Mt11[]` calls the full matrial tensor not just the first component, so user should not get confused. This is more technical note, `Mt11[]` is the cast of `Mt` vector to a single array for memory optimization. One can also simply use `Mt12[]`, `Mt13[]`, `Mt22[]`, ... all these are acceptable and are simply aliases to material tensor.

The material tensor `Mt` built is used in the finite element variational formulation to build the bilinear $a(\mathbf{u},\mathbf{v})$ which is used to assemble the finite element matrix $\mathbf{A}$ for the linear system $\mathbf{Ax} = \mathbf{b}$


$$
a(\mathbf{u},\mathbf{v}) = \int_{\Omega}(
                 \varepsilon \left(\mathbf{u}):\mathbf{Mt}:\varepsilon(\mathbf{v}\right)
               )
$$

Here, $\varepsilon(\mathbf{u}):\mathbf{Mt}$ is nothing but the stress $\sigma(\mathbf{u})$ operator. User is encourage to have a look at the `VariationalFormulation.edp` file that contains the variational formulation (weak form) of the problem described.