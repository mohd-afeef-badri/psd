---
title: Soildynamics Tutorials for PSD
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
\newcommand{\sh}[1]{\small\sffamily{\color{blue!60}#1}}

\subsection{Parallel 2D}

The problem of interest is a single Dirichlet condition problem of soildynamics in 2D. For this problem we use Newmark-$\beta$ time discretization. Additionally postrocessing is demanded for displacement, acceleration, and velocity ($u,a,v$).

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 -timediscretization newmark-beta \
-postprocess uav
\end{lstlisting}

Once the step above has been performed, we solve the problem using four MPI processes, with the given mesh file \sh{soil.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/soil.msh -v 0
\end{lstlisting}


\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/sd-u0.png}
\includegraphics[width=0.4\textwidth]{./Images/sd-u1.png}\\
\includegraphics[width=0.4\textwidth]{./Images/sd-u2.png}
\includegraphics[width=0.4\textwidth]{./Images/sd-u3.png}\\
\includegraphics[width=0.4\textwidth]{./Images/sd-u4.png}
\caption{Finite element displacement and velocity fields visualized for the 2D problem with ParaView at different timesteps. \label{bar-sd}}
\end{figure}

Using ParaView for postprocessing the results that are provided in the \sh{VTUs...} folder, results such as those shown in figure~\ref{bar-sd} can be extracted.


\subsection{Parallel 3D}

The problem of interest is a single Dirichlet condition problem of soildynamics in 3D. For this problem we use Newmark-$\beta$ time discretization. Additionally postrocessing is demanded for displacement, acceleration, and velocity ($u,a,v$).

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem soildynamics -dirichletconditions 1 -timediscretization newmark-beta \
-postprocess uav
\end{lstlisting}

Once the step above has been performed, we solve the problem using three MPI processes, with the given mesh file \sh{soil.msh}. 

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

Using ParaView for postprocessing the results that are provided in the \sh{VTUs...} folder, results such as those shown in figure~\ref{bar3d-sd} can be extracted.

\subsection{Parallel 2D with double couple}

In the 2D problem above seismic sources was supplied on the border, in the current one the source is more realistic and comes from a double couple (point Dirichlet condition). The double couple boundary condition is a way to impose moments caused by faults that create earthquakes, here in this problem double couple is imposed using displacement based. 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem soildynamics -model linear -timediscretization newmark-beta \
-useGFP -doublecouple displacement-based -postprocess uav
\end{lstlisting}

Once the step above has been performed, we solve the problem using two MPI processes, with the given mesh file \sh{soil-dc.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -v 1 -ns -nw -mesh ./../Meshes/2D/soil-dc.msh
\end{lstlisting}

\begin{figure}[h!]
\centering
\includegraphics[width=0.45\textwidth]{./Images/sd-2ddcu0.png}
\includegraphics[width=0.45\textwidth]{./Images/sd-2ddcu1.png}\\
\includegraphics[width=0.45\textwidth]{./Images/sd-2ddcu2.png}
\caption{Finite element displacement and acceleration fields visualized for the 2D problem with ParaView at different timesteps. \label{bar2ddc-sd}}
\end{figure}

Using ParaView for postprocessing the results that are provided in the \sh{VTUs...} folder, results such as those shown in figure~\ref{bar2ddc-sd} can be extracted.

Similarly try out the 3D problem. However take note that a the mesh \sh{./../Meshes/2D/soil-dc.msh} is not provided, so you will have to create your own mesh. 


\subsection{Parallel 3D with top-ii-vol meshing}

Single Dirichlet at the bottom and using GFP.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem soildynamics -model linear -timediscretization newmark-beta \
-useGFP -top2vol-meshing -timediscretization newmark-beta -postprocess uav
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -v 0 -ns -nw 
\end{lstlisting}


\subsection{Parallel 3D with top-ii-vol meshing and double couple source}

Single Dirichlet via double couple and using GFP. Double couple is displacement based. 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem soildynamics -model linear -timediscretization newmark-beta \
-useGFP -top2vol-meshing -doublecouple displacement-based -postprocess uav
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -v 0 -ns -nw 
\end{lstlisting}

\subsection{Exercise  1}

You are encouraged to try out sequential PSD solver, to do so used add \sh{-sequential} flag to \sh{PSD\_PreProcess} step and run the solver with \sh{PSD\_Solve\_Seq} instead of \sh{PSD\_Solve}. For example, the PSD sequential solver workflow for the first 2D example in this tutorial would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 -timediscretization newmark-beta \
-postprocess uav -sequential
\end{lstlisting}

Once the step above has been performed, we solve the problem using \sh{PSD\_Solve\_Seq}, with the given mesh file \sh{soil.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq  Main.edp -mesh ./../Meshes/2D/soil.msh -v 0
\end{lstlisting}

Try it out for other problems of this tutorial. 

\subsection{Exercise 2}

For soildynamic problems with double couple source, the double couple source can be introduced into the solver either by displacement-based operator -- providing displacements at the double couple points that will be converted to moments -- or by force-based operators -- providing forces at the double couple points that  will be converted to moments. In the tutorials above we already tried displacement-based way of introducing double couple source by using \sh{-doublecouple displacement-based}. You are encouraged to try out the force-based double couple source by using \sh{-doublecouple force-based}.

\subsection{Exercise 3}

You are encouraged to try out timelogging and find out if the code (parallel/sequential) is any faster when we use Newmark-$\beta$ or Generalized-$\alpha$. Read the documentation for other types of time discretizations that can be performed with PSD, try each one out with \sh{-timelog} and compare.

\subsection{Exercise  4}

PSD comes with additional set of plugins/functions that are highly optimized for performing certain operations during solving. These operations are handled by GoFast Plugins (GFP) kernel of PSD (optimize C++ classes/templates/structures), by default this functionality is turned off and not used. You are encouraged to try out using GFP functions in a solver by using \sh{-useGFP} flag flag to \sh{PSD\_PreProcess} For example, the PSD solver workflow for the first 2D example in this tutorial would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 -timediscretization newmark-beta \
-postprocess uav -useGFP
\end{lstlisting}

Once the step above has been performed, we solve the problem using, with the given mesh file \sh{soil.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/soil.msh -v 0
\end{lstlisting}

Try it out for other problems of this tutorial. \sh{-useGFP} should lead to a faster solver, it might be a good idea to always use this option. To go one step further, use \sh{-timelog} flag and determine if you have some speed up. 

