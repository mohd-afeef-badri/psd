---
title: Linear Elasticity Tutorial 2D bar problem clamped at one end wile being pulled at the other end (Dirichlet--Neumann case)
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

Similar simulation, as in the previous tutorial is presented in this section. We showcase the 2D bar problem simulation with one end clamped wile being pulled at the other end. Just like the previous simulation  the body force is neglected. However, now  the non clamped ends pull is approximated with Neumann force (aka. traction force)
$\int_{\partial\Omega^h_{\text N}}(\mathbf t \cdot \mathbf{v}^h)$.
To simulate the pull we assume traction vector $\mathbf t=[t_x,t_y]=[10^9.,0]$ acting on the non clamped right end of the bar, i.e., force in $x$ direction is 10$^9$ units. Here is how PSD simulation of this case can be performed. The same problem from previous tutorials 1 and 2 is used here, a bar 5 m in length and 1 m in width, and is supposed to be made up of a material with density $\rho=8\times 10^3$, Youngs modulus $E=200\times 10^9$, and Poissons ratio $\nu=0.3$. 


\textbf{Step 1: Preprocessing}

First step in a PSD simulation is PSD preprocessing, at this step you tell PSD what kind of physics, boundary conditions, approximations, mesh, etc are you expecting to solve.

In the terminal \psd{cd} to the folder \psd{/home/PSD-tutorials/linear-elasticity}. Launch \psd{PSD\_PreProcess} from the terminal, to do so run the following command.


\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear-elasticity -dimension 2 -dirichletconditions 1 -tractionconditions 1 -postprocess u
\end{lstlisting}

the comandline flag \psd{ -dirichletconditions 1}, notifies to PSD that there is one Dirichlet border ---the clamped end of the bar--- in this simulation. And the flag \psd{ -tractionconditions 1} notifies to PSD that there is one traction border ---the right end of the bar--- in this simulation.

To provide the clamped boundary condition ($u_1=0,u_2=0$) set the variables  \psd{ Dbc0On 2}, \psd{ Dbc0Ux 0.}, and \psd{ Dbc0Uy 0.} in \psd{ ControlParameters.edp}. In the same file traction boundary conditions are provided via the variables \psd{ Tbc0On 4} and \psd{ Tbc0Tx 1.e9}, which mean apply traction force $\mathbf t=[t_x,t_y]=[10^9.,0]$ on label number 4 (right) of the mesh. If user wishes to add traction force ,for instance $t_y=100.$, simply add the missing macro \psd{ macro Tbc0Tx 1.e9 //}.


\textbf{Step 2: Solving}

Let us now use 5 cores to solve this problem. To do so enter the following command:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 5 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

Notice, that this is the exact same command used in solving the previous bar problems from other sections, with only difference that we now use \psd{ -np 5}.

Note that for this simple problem, the bar mesh (\psd{bar.msh}) has been provided in \psd{../Meshes/2D/"} folder, this mesh is a triangular mesh produced with Gmsh. Moreover detailing meshing procedure is not the propose of PSD tutorials. A user has the choice of performing their own meshing step and providing them to PSD in \psd{.msh}\footnote{Please use version 2} or \psd{.mesh} format, we recommend using Salome or Gmsh meshers for creating your own geometry and meshing them. 


\textbf{Step 3: Postprocessing}

Launch ParaView and have a look at the  \psd{ .pvd} file in the  \psd{ PSD/Solver/VTUs\_DATE\_TIME} folder.

\begin{figure}[htbp]
    \centering
    \begin{minipage}[t][2cm][t]{0.36\textwidth}
    \includegraphics[align=b,width=1\textwidth]{./Images/2d-bar-partitioned5.png}
    \end{minipage}\hspace{.1\textwidth}
    \begin{minipage}[t][2cm][t]{0.5\textwidth}
    \includegraphics[align=b,width=1\textwidth]{./Images/2d-bar-clamped-traction.png}
    \end{minipage}
    \caption{2D bar results. Partitioned mesh (left) and 100X warped displacement field (right).}
    \label{fig:5part}
\end{figure}

Note now in \cref{fig:5part} there are five subdomains in the partitioned mesh since five cores were used. Contrary to previous tutorial, as expected, we see that the right end of the bar which is being pulled now contract in $y$ direction. This is due to the fact that there is no Dirichlet condition at this end now.
