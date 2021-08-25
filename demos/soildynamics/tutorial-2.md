---
title: Soildynamics Tutorials for PSD - Soildynamics in 3D with PSD 
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



The problem of interest is a single Dirichlet condition problem of soildynamics in 3D. For this problem we use Newmark-$\beta$ time discretization. Additionally postrocessing is demanded for displacement, acceleration, and velocity ($u,a,v$).

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem soildynamics -dirichletconditions 1 -timediscretization newmark_beta \
-postprocess uav
\end{lstlisting}

Once the step above has been performed, we solve the problem using three MPI processes, with the given mesh file \psd{soil.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/soil.msh -v 0
\end{lstlisting}

\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/sd-3du0.png}
\includegraphics[width=0.4\textwidth]{./Images/sd-3du1.png}\\
\includegraphics[width=0.4\textwidth]{./Images/sd-3du2.png}
\includegraphics[width=0.4\textwidth]{./Images/sd-3du3.png}\\
\includegraphics[width=0.4\textwidth]{./Images/sd-3du4.png}
\caption{Finite element displacement and velocity fields visualized for the 3D problem with ParaView at different timesteps. \label{bar3d-sd}}
\end{figure}

Using ParaView for postprocessing the results that are provided in the \psd{VTUs...} folder, results such as those shown in figure~\ref{bar3d-sd} can be extracted.

