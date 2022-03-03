/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI, Reine Fares                                              *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 02/03/2022                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support file is  responsible for generating iwan-validation.edp       *
*                                                                                     *
**************************************************************************************/

cout << " building PSD-validation-iwan.edp";


ofstream  write("PSD-validation-iwan.edp");

codeSnippet R""""(

/*****************************************************************************

         This file is a part of PSD (Parallel Structural Dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri, Reine Fares
     Email    : mohd-afeef.badri@cea.fr
     Date     : 02-March-2022
     Comment  : This test checks the MFront-PSD coupling for Iwan law.
                This code expects the following INPUTS from user:
                  i) 'in.data' this file contains 2  columns  the time 
                     and input Exy value (loading).
                 ii) 'steps' this is an integer value giving the total
                     number of time steps in your file 'in.data'
                The output of this code is 'out.data' file, an  ASCII 
                file that contains 3 columns, time, Sigma_xy, Exy.

     -------------------------------------------------------------------

     PSD a parallel  finite  element framework  provides tools to  solve
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE.

*******************************************************************************/
load "mfront"
load "Element_QF"
load "msh3"

mesh3 Th = cube(1, 1, 1);

// Quadrature space with 3 elements for stress and strain tensor
fespace Sh(Th, [FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d]);
Sh[Eps11, Eps22, Eps33, Eps12, Eps13, Eps23];
Sh[EpsOld11, EpsOld22, EpsOld33, EpsOld12, EpsOld13, EpsOld23];
Sh[Sig11, Sig22, Sig33, Sig12, Sig13, Sig23];

fespace Ih(Th, [FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d
]);

Ih[Isv0, Isv1, Isv2, Isv3, Isv4, Isv5, Isv6, Isv7, Isv8, Isv9, Isv10, Isv11, Isv12, Isv13, Isv14, Isv15, Isv16, Isv17, Isv18, Isv19, Isv20, Isv21, Isv22, Isv23, Isv24, Isv25, Isv26, Isv27, Isv28, Isv29, Isv30, Isv31, Isv32, Isv33, Isv34, Isv35, Isv36, Isv37, Isv38, Isv39, Isv40, Isv41, Isv42, Isv43, Isv44, Isv45, Isv46, Isv47, Isv48, Isv49, Isv50, Isv51, Isv52, Isv53, Isv54, Isv55, Isv56, Isv57, Isv58, Isv59, Isv60, Isv61, Isv62, Isv63, Isv64, Isv65, Isv66, Isv67, Isv68, Isv69, Isv70, Isv71, Isv72, Isv73, Isv74, Isv75, Isv76, Isv77, Isv78, Isv79, Isv80, Isv81, Isv82, Isv83, Isv84, Isv85, Isv86, Isv87, Isv88, Isv89, Isv90, Isv91, Isv92, Isv93, Isv94, Isv95, Isv96, Isv97, Isv98, Isv99, Isv100, Isv101, Isv102, Isv103, Isv104, Isv105, Isv106, Isv107, Isv108, Isv109, Isv110, Isv111, Isv112, Isv113, Isv114, Isv115, Isv116, Isv117];

Isv0[] = 0;

string MaterialProperty = "YoungModulus PoissonRatio NumberofSpring";

string YielsurfacestressCiNames1 = " YielsurfacestressCi[0] YielsurfacestressCi[1] YielsurfacestressCi[2] YielsurfacestressCi[3] YielsurfacestressCi[4] YielsurfacestressCi[5] YielsurfacestressCi[6] YielsurfacestressCi[7] YielsurfacestressCi[8] YielsurfacestressCi[9]";
string YielsurfacestressCiNames2 = " YielsurfacestressCi[10] YielsurfacestressCi[11] YielsurfacestressCi[12] YielsurfacestressCi[13] YielsurfacestressCi[14] YielsurfacestressCi[15]";

string YielsurfacestrainYiNames1 = " YielsurfacestrainYi[0] YielsurfacestrainYi[1] YielsurfacestrainYi[2] YielsurfacestrainYi[3] YielsurfacestrainYi[4] YielsurfacestrainYi[5] YielsurfacestrainYi[6] YielsurfacestrainYi[7] YielsurfacestrainYi[8] YielsurfacestrainYi[9]";
string YielsurfacestrainYiNames2 = " YielsurfacestrainYi[10] YielsurfacestrainYi[11] YielsurfacestrainYi[12] YielsurfacestrainYi[13] YielsurfacestrainYi[14] YielsurfacestrainYi[15]";
   

string PropertyNames = MaterialProperty + YielsurfacestressCiNames1 + YielsurfacestressCiNames2 + YielsurfacestrainYiNames1 + YielsurfacestrainYiNames2;


 
real[int] PropertyValues =[

	614930000.0, 0.371, 16,
	1438707420.0, 31390142724.0, 38213126183.0, 12058438512.0, 6415920460.0, 4779863112.0,
	6160771598.0, 9332518493.0, 1518307923.0, 900683489.3, 620762077.8, 181090675.9,
	134905475.6, 75387120.03, 39561849.73, 39229506.65,
	340005.5091, 420308.5133, 524405.5834, 653604.7237, 1647053.671, 2520327.797,
	4384366.063, 5203073.539, 8131982.302, 11264333.18, 13251691.55, 16720370.49,
	19253276.75, 20620902.16, 22768742.08, 21428992.9

];



int steps = 2001;
real timeT, GammaExy;
real[int] SigxyRef(steps);
real dummy;

ifstream inEpsilon("in.data");
ofstream outStress("out.data");
  
if (mpirank == 0)
	outStress << "#Time" << "  " << "E_xy" << "  " << "Sig_xy" << "  " << "Sig_xy_ref" << endl;

for (int i = 0; i < steps; i++)
{

	inEpsilon >> timeT >> dummy >> GammaExy >> SigxyRef(i);
	GammaExy = 1. / sqrt(2.) *GammaExy;
        [Eps11, Eps22, Eps33, Eps12, Eps13, Eps23] =[0, 0, 0, GammaExy, 0, 0];

        PsdMfrontHandler( "Iwan"                                               ,
                           mfrontBehaviourHypothesis = "TRIDIMENSIONAL"        ,
                           mfrontPropertyNames       = PropertyNames         ,
                           mfrontPropertyValues      = PropertyValues        ,
                           mfrontStrainTensor        = Eps12[]                 ,
                           mfrontStressTensor        = Sig22[]                 ,
                           mfrontStateVariable       = Isv1[],
                           mfrontPreviousStrainTensor = EpsOld12[]                 
                         );
	EpsOld12[] = Eps12 [];
	              
	int prec = outStress.precision(16);                       
	if(mpirank==0)                         
    outStress << timeT << "  " << GammaExy << "  " << Sig11[][12] / sqrt(2.) << "  " << SigxyRef(i) << endl;
}

)"""";

if(pipegnu)
{
write<< 
   "system(\"echo \\\"plot 'out.data' u 1:3 w l lw 4 t 'PSD', '' u 1:4 w l lw 2 t 'CAST3M'\\\" | gnuplot -p\");"
<< endl;
}

cout << " ............................ Done  \n";  
