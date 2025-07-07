---
title: Elastodynamics Tutorials - Diffrent time discretizations for elastodynamic simulations
geometry: margin=2cm
author: Mohd Afeef Badri
header-includes: |
    \usepackage{tikz,pgfplots}
    \usepackage{listings}
    \usepackage{textcomp}
    \usepackage{fancyhdr}
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
abstract: This document details some tutorials of elastodynamics module of PSD. These tutorials are not verbose, but does instead give a kick start to users/developers for using PSD's elastodynamics module. 
---

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}



PSD offers different time discretization techniques for solving time dependent problems. For this example instead of using Newmark-$\beta$ time  discretization let us switch to more advanced Generalized-$\alpha$ one. This can be done by \psd{-timediscretization generalized\_alpha}, so for example for a 2D problem we use:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization generalized_alpha -postprocess uav
\end{lstlisting}

Once the step above has been performed, we solve the problem using three MPI processes, with the given mesh file \psd{bar_dynamic.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/2D/bar_dynamic.msh -v 0
\end{lstlisting}

Similarly try out the 3D problem as well.
