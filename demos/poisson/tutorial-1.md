---
title: Poisson Tutorial 1 PSD simulation of nontrivial manufactured tests
geometry: margin=2cm
author: Mohd Afeef Badri
header-includes: |
    \usepackage{tikz,pgfplots}
    \usepackage{listings}
    \usepackage{textcomp}
    \usepackage{fancyhdr}
    \usepackage{graphbox}
    \usepackage{cleveref}
    \usepackage{subcaption}
    \pagestyle{fancy}
    \lstdefinestyle{BashInputStyle}{
	language=bash,
	basicstyle=\small\sffamily,
	numbers=left,
	numberstyle=\tiny,
	numbersep=3pt,
	frame=tb,
	columns=fullflexible,
	backgroundcolor=\color{yellow!20},
	linewidth=1.\linewidth,
	xleftmargin=0.05\linewidth,
	literate =
	{"}{{\uprightquote}}1
	{'}{{\textquotesingle}}1
	{-}{{-}}1
	{~}{{\centeredtilde}}1
	,
    }
abstract: This document details a single tutorials of 'linear elasticity' module of PSD in a more verbos manner.
---

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}

Poisson problem is a boundary value problem in FEM which is often used to demonstrate the solvers correctness or used to develop many fundamental tools that are later used for other complex problems. Poisson's problem itself can be used to approximate certain physcial phenomena such as, heat trasfer, electrostatics, basic aerodynamics, etc. 

The Poisson equation is a PDE which is defined by the following boundary-value problem,

$$\Delta u (x) = -f(x) \quad \forall x \in \Omega, $$

$$u (x) = u_{\text{D}}(x) \quad \forall x \in \partial\Omega, $$

here,  $u(x)$ is the unknown variable, $f(x)$ is  a known function also known as source term, $\Delta$ is the Laplace operator, $\Omega$ is  the spatial domain in space $x$ and is bounded by boundary $\partial \Omega$. The Poisson problem here, includes known value $u_{\text{D}}$ on its border $\partial \Omega$.

The starting point for FEM approximation for a   PDE is its *variational form*. The variational formulation for Poission's problem reads, find $u \in \mathcal{V}$: 


$$\int_\Omega \nabla u \cdot \nabla v~\mathrm{d} x = \int_\Omega fv~\mathrm{d} x \quad \quad \forall v \in \hat{\mathcal{V}}.$$

For this formulation, the trial function $u$ and test function $v$ are defined in functional spaces 

$$\mathcal{V}=\{v\in H^1(\Omega)|v=u_{\text{D}} \quad \text{on} \quad \partial\Omega \},$$

$$\hat{\mathcal{V}}=\{v\in H^1(\Omega)|v=0 \quad \text{on} \quad \partial\Omega \}.$$

Here, $H^1(\Omega)$ is the  Sobolev space containing functions $v$ such that these are square integrable with continuous derivatives over $\Omega$. Note that, the Sobolev space allows functions with discontinuous derivatives. This weaker continuity requirement in our weak formulation (caused by the integration by parts) is of great importance when it comes to constructing the finite element function space. In particular, it allows the use of piecewise polynomial function spaces. This means that the function spaces are constructed by stitching together polynomial functions on simple domains such as intervals, triangles, quadrilaterals, tetrahedra and hexahedra. In principal these simpler domains are  obtaining by converting our domain $\Omega$ to its meshed form $\Omega^h$, such that $h$ defines the size of the mesh. 

The variational problem is a *continuous problem*: it defines the solution  in the infinite-dimensional function space . The finite element method for the Poisson equation finds an approximate  solution $u^h$ of the variational problem by replacing the  infinite-dimensional function spaces $\mathcal{V}$  and  by *discrete* (finite dimensional) trial  and test spaces  $\mathcal{V}^h$ and $\hat{\mathcal{V}}^h$ . The discrete variational problem reads: Find  find $u^h \in \mathcal{V}^h$ such that 


$$\int_\Omega^h \nabla u^h \cdot \nabla v^h~\mathrm{d} x = \int_\Omega^h fv^h~\mathrm{d} x \quad \quad \forall v^h \in \hat{\mathcal{V}^h}.$$
