---
title: Fracture mechanics Tutorials
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
abstract: This document details some tutorials of 'fracture mechanics' module of PSD. These tutorials are not verbose, but does instead give a kick start to users/developers for using PSD's 'fracture mechanics' module. 
---

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}



\subsection{Tensile cracking of a pre-cracked plate: A 2D example of PSD parallel solver}

A two dimensional test is introduced. The problem of interest is the typical single notch square plate cracking test under tensile loading. A unit square with a pre existing crack  is clamped at the bottom $u_1=u_2=0$ (first boundary condition) and is loaded quasi-statically $u_2=u_2 + \Delta u_2$ on its top surface till the crack propagates through its walls. So there are two Dirichlet conditions one on the top border and one on the bottom one.

\begin{figure}[h!]
\centering
\includegraphics[width=0.3\textwidth]{./Images/square-notch.png}
\caption{Domain of the single notch square cracking problem under tensile loading. \label{bar-sd}}
\end{figure}

To model this test PSD provides hybrid phase-field modelling  technique. We use ParaView post-processing of displacement $u$ and phase-field $d$ to visualise the cracking process. A PSD simulation is a two step process, with step one being the  \psd{ PSD\_PreProcess }:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field \
-dirichletconditions 2 -postprocess ud
\end{lstlisting}

A note on flags. 

- This is a two-dimensional problem, so we use the flag  \psd{-dimension 2}.
- This problem indeed falls under the category of damage-mechanics, hence the flag \psd{ -problem damage}.
- We wish to solve this problem by invoking the hybrid phase-field problem, which is signified by the flag  \psd{ -model hybrid\_phase\_field}.
- Versed in the description above the problem contains two Dirichlet conditions, we signal this via the flag \psd{-dirichletconditions 2}. 
- Finally for this problem we use the flag  \psd{-postprocess ud}  which enables post-processing of displacement $u$ and damage (phase-field)  $d$ fields.

Once the step above has been performed, we solve the problem using four MPI processes, with the given mesh file \psd{tensile-crack.msh}. This is step two of the PSD simulation   \psd{ PSD\_Solve}.

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/tensile-crack.msh -v 0
\end{lstlisting}

\begin{figure}[h!]
\centering

\includegraphics[width=0.24\textwidth]{./Images/u0.png}
\includegraphics[width=0.24\textwidth]{./Images/u1.png} 
\includegraphics[width=0.24\textwidth]{./Images/u2.png}
\includegraphics[width=0.24\textwidth]{./Images/u3.png}\\
\includegraphics[width=0.24\textwidth]{./Images/u4.png}
\includegraphics[width=0.24\textwidth]{./Images/u5.png}
\includegraphics[width=0.24\textwidth]{./Images/u6.png}
\includegraphics[width=0.24\textwidth]{./Images/u7.png}
\caption{Finite element displacement visualised for the 2D problem with ParaView at different timesteps (quasi-statics). Time progresses from left to right in a row and top to bottom when comparing rows. \label{u-fem}}
\end{figure}



\begin{figure}[h!]
\centering

\includegraphics[width=0.24\textwidth]{./Images/d0000.png}
\includegraphics[width=0.24\textwidth]{./Images/d0010.png} 
\includegraphics[width=0.24\textwidth]{./Images/d0020.png}
\includegraphics[width=0.24\textwidth]{./Images/d0030.png}\\
\includegraphics[width=0.24\textwidth]{./Images/d0040.png}
\includegraphics[width=0.24\textwidth]{./Images/d0050.png}
\includegraphics[width=0.24\textwidth]{./Images/d0060.png}
\includegraphics[width=0.24\textwidth]{./Images/d0069.png}
\caption{Finite element damage visualised for the 2D problem with ParaView at different timesteps (quasi-statics). Time progresses from left to right in a row and top to bottom when comparing rows. \label{d-fem}}
\end{figure}

Figures \ref{u-fem} and \ref{d-fem} present the finite element displacement and damage field, which enable us to visualise the cracking of the square plate.



\begin{figure}[h!]
\centering

\includegraphics[width=0.6\textwidth]{./Images/terminal1.png}
\caption{Applied traction, non-linear iterations to convergence, and residual being casted onto the terminal shell. \label{term}}
\end{figure}

While this test runs, you will see on your screen the amount of traction updated, non-linear iterations taken to converge per-quasi-time-step and residue of $u$ and $d$. See figure \ref{term} that shows the screenshot of the terminal while the test was running.  In order to construct your own test case try editing the  \psd{ControlParameters.edp} file   







\subsection{Tensile cracking of a pre-cracked cube: A 3D example of PSD parallel solver}

A three-dimensional test synonymous to its two-dimensional counterpart introduced above is used here as an tutorial example.   The problem of interest is now a unit extrusion (along $z$-axis) of the 2D case above. Cracking is initiated and propagated under tensile loading. The unit cube with its  pre existing crack  is clamped at the bottom $u_1=u_2=u_3=0$ (first boundary condition) and is loaded quasi-statically $u_2=u_2 + \Delta u_2$ on its top surface till the crack propagates through its walls. So there are two Dirichlet conditions one on the top border and one on the bottom one.

Just like in the 2D case, to model this test PSD's' hybrid phase-field modelling  technique is used. We will again use ParaView post-processing of displacement $u$ and phase-field $d$ to visualise the cracking process. A PSD simulation is a two step process, with step one being the  \psd{ PSD\_PreProcess }:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field  \
-dirichletconditions 2 -postprocess ud 
\end{lstlisting}

Notice that the flags used here are almost similar except for the   \psd{ -dimension 3 } flag, which indeed specifies three-dimensional problem.

Once the step above has been performed, we solve the problem using four MPI processes, with the given mesh file \psd{tensile-crack.msh}. This is step two of the PSD simulation   \psd{ PSD\_Solve}.

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/tensile-crack.msh -v 0
\end{lstlisting}

\begin{figure}[h!]
\centering

\includegraphics[width=0.24\textwidth]{./Images/u3d0.png}
\includegraphics[width=0.24\textwidth]{./Images/u3d1.png} 
\includegraphics[width=0.24\textwidth]{./Images/u3d2.png}
\includegraphics[width=0.24\textwidth]{./Images/u3d3.png}
\caption{Finite element displacement visualised for the 3D problem with ParaView at different timesteps (quasi-statics). Time progresses from left to right in a row and top to bottom when comparing rows. \label{u3d-fem}}
\end{figure}



\begin{figure}[h!]
\centering

\includegraphics[width=0.24\textwidth]{./Images/d3d0.png}
\includegraphics[width=0.24\textwidth]{./Images/d3d1.png} 
\includegraphics[width=0.24\textwidth]{./Images/d3d2.png}
\includegraphics[width=0.24\textwidth]{./Images/d3d3.png}
\caption{Finite element damage visualised for the 3D problem with ParaView at different timesteps (quasi-statics). Time progresses from left to right in a row and top to bottom when comparing rows. \label{d3d-fem}}
\end{figure}

Figures \ref{u3d-fem} and \ref{d3d-fem} present the finite element displacement and damage field of the 3D problem, which enable us to visualise the cracking of the cubic specimen.

\subsection{Parallel 2D tensile cracking and calculate-ploting reaction-force}

In solid mechanics often the quantities of interest includes plots such as reaction-force on a surface vs. the applied force. Often times these are experimental outputs and are used for validation. 

PSD provides routines to calculate the reaction force on a surface and also provides means of live plotting (run-time)  of these results. Imagine the test case of tensile cracking of plate (2D) as discussed above. Considering we are now interested in seeing the plot of reaction force at surface vs. the applied tensile displacement, we would need to use two extra flags in the   \psd{ PSD\_PreProcess} step. These flags are \psd{-getreactionforce} and \psd{ -reactionforce  stress\_based } as read below:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field \
-dirichletconditions 2 -getreactionforce -reactionforce stress_based
\end{lstlisting}

The flag  \psd{-getreactionforce} directs PSD to include the routines to get the reaction force and  \psd{ -reactionforce  stress\_based } is the method by which we get reaction force, in this case reaction force is calculated using integral of stress in $y$ direction $F_y=\int_{\partial\Omega_{top}} \sigma_y$. Other method \psd{ -reactionforce variational\_based} also exists within PSD, which is more accurate but slower, this method calculates reaction force based on matrix vector multiplication ${F_x,F_y}=\mathbf{A}{u_1,u_2}$ .

Run the problem in the usual way bu using \psd{ PSD\_Solve} and appropriate number of processes and mesh.  While the PSD solver runs it will create a file \psd{ force.data} that contains the reaction force and the applied traction. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/tensile-crack.msh -v 0
\end{lstlisting}

 You can then go ahead and plot \psd{ force.data} to see how $F_y$ and $F_x$  evolve  with $\Delta u_2$. Within the file the first column is the loading $\Delta u_2$, the second and the third columns are the forces $F_x$ and $F_y$.



\begin{figure}[h!]
\centering

\includegraphics[width=0.4\textwidth]{./Images/plot-fd.png}
\caption{Applied traction vs. force in y direction. \label{fd-plot}}
\end{figure}

Optionally if you have GnuPlot configured with PSD you can see live ploting of this curve if you use option  \psd{-plotreactionforce} during the  \psd{ PSD\_PreProcess}. 

\begin{figure}[h!]
\centering

\includegraphics[width=0.3\textwidth]{./Images/gp0.png}\includegraphics[width=0.3\textwidth]{./Images/gp1.png}\includegraphics[width=0.3\textwidth]{./Images/gp2.png}
\caption{Applied traction vs. force in y direction plotted live using PSD. \label{gnuplot-plot}}
\end{figure}



\subsection{Parallel 3D and calculate reactionforce}


\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field \
-dirichletconditions 2 -getreactionforce -reactionforce stress_based
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/tensile-crack.msh -v 0
\end{lstlisting}


