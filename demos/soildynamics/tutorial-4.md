---
title: Soildynamics Tutorials for PSD - Parallel 3D with top-ii-vol meshing
author: Mohd Afeef Badri
geometry: margin=2cm
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
abstract: This document details some tutorials of soildynamics module of PSD. These tutorials are not verbose, but does instead give a kick start to users/developers for using PSD's soildynamics module. 
---
\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}


Single Dirichlet at the bottom and using GFP.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem soildynamics -model linear -timediscretization newmark_beta \
-useGFP -top2vol-meshing -timediscretization newmark-beta -postprocess uav
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -v 0 -ns -nw 
\end{lstlisting}

