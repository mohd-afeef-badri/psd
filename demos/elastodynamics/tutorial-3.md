---
title: Elastodynamics Tutorials - Sequential PSD elastodynamic simulations
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




To the same problems above Add \psd{-sequential} flag to \psd{PSD\_PreProcess} for sequential solver, but remember to use \psd{PSD\_Solve\_Seq} instead of \psd{PSD\_Solve}. So the work flow for the 2D problem would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -sequential
\end{lstlisting}

Once the step above has been performed, we solve the problem using the given mesh file \psd{bar-dynamic.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0
\end{lstlisting}

Similarly try out the 3D problem as well.
