//=====================================================================================   
// ------ Help message on the screen ------ 
//=====================================================================================

if(help){cout
<<"										   \n"
<<"================================================================================\n"
<<"                       ----YOU ACTIVATED THE HELP OPTION----			   \n"
<<"                      Please read the messages below carefully		   \n"
<<"================================================================================\n"
<<"										   \n"
<<"										   \n"
<<" According to the flags provided You are solving A "<<spc<<"D problem.	   \n"
<<"										   \n"
<<"										   \n"
<<"  # With"<<(bodyforce   ? "" : "out")<<" bodyforce acting on the volume.	   \n"
<<"  # With"<<(tractionbc  ? "" : "out")<<" traction boundary condition.   	   \n"
<<"  # With"<<(dirichletbc ? "" : "out")<<" Dirichlet surface boundary condition.  \n"
<<"  # With"<<(pointbc     ? "" : "out")<<" Dirichlet point boundary condition.    \n"
<<"  # Paraview plotting is "<<(plotAll ? "en" : "dis")<<"abled.		   \n"
<<"										   \n"
<<"										   \n"
<<" WARNING: If something doesn't look right consider rerunning with correct flags.\n"
<<"          Have a look at README.html and TestinTheSolver.html to know about the \n"
<<"          usage of the flags.                                                   \n"
<<"										   \n" 
<<"										   \n"
<<"/***********************************IMPORTANT***********************************\n"
<<"*                                                                              *\n"
<<"* To change the mesh and the material parameters edit 'ControlParameters.edp'  *\n"
<<"*                                                                              *\n"
<<"* 1. Edit  <<ThName>> the [string] name of your mesh  file  with  location.    *\n"
<<"*                                                                              *\n"
<<"* 2. Edit << E,nu,f1,f2,f3,... >> of [real]  type  representing the materials  *\n"
<<"*    modulus of elasticity, Poisson's ratio, body  forces  f1,f2,f3 in x,y,z.  *\n"
<<"*                                                                              *\n"
<<"*******************************************************************************/\n"
<<"										   \n";

if(dirichletbc)cout 
<<"										   \n"
<<"/***********************************IMPORTANT***********************************\n"
<<"*                                                                              *\n"
<<"* Using Dirichlet BC  please edit the file 'ControlParameters.edp'   	  *\n"
<<"*                                                                              *\n"
<<"* 1. Edit  <<Dlabel>> i.e. the  [int]   vector   of  labels  that contain your *\n"
<<"*    Dirichlet border. So  if your border is labeled 1 Dlabel=[1], if you have *\n"
<<"*    two Dirichlet borders 4 & 5 then  Dlabel = [4,5].                         *\n"
<<"*                                                                              *\n"
<<"* 2. Edit <<Dvalue>> i.e the [real] vector defined by Dirichlet  values.  Each *\n"
<<"*    Dirichlet borders  will need  Dirichlet field values. So e.g.  Dlabel=[1] *\n"
<<"*    you can use Dvalue=[1.,0.], meaning u1=1, and u2=0                        *\n"
<<"*                                                                              *\n"
<<"*******************************************************************************/\n"
<<"										   \n";

if(bodyforce)cout
<<"										   \n"
<<"/***********************************IMPORTANT***********************************\n"
<<"*                                                                              *\n"
<<"* Using bodyforce within the problem edit  'ControlParameters.edp'  		  *\n"
<<"*                                                                              *\n"
<<"* 1. Edit macro <<BF>> and  provide three components of  bodyforce. Note  that *\n"
<<"*    the macro accepts real or functional values.                              *\n" 
<<"*                                                                              *\n"
<<"*******************************************************************************/\n"
<<"										   \n";

if(pointbc)cout
<<"										   \n"
<<"/***********************************IMPORTANT***********************************\n"
<<"*                                                                              *\n"
<<"* Using Dirichlet BC on  point please edit  'ControlParameters.edp'  	  *\n"
<<"*                                                                              *\n"
<<"* 1. Edit <<Dpointlab>> i.e. the  [int]   vector of  labels  that contain your *\n"
<<"*    Dirichlet Point. So if your point is on line 4 Dpointlab = [4].           *\n"
<<"*                                                                              *\n"
<<"* 2. Edit <<PnV>> i.e  the [real] vector defined by  [x,y,u1,u2]. Here (x,y) & *\n"
<<"*    (u1,u2) are coordinates and deformation values of the Dirichlet point.    *\n"
<<"*                                                                              *\n"
<<"*******************************************************************************/\n"
<<"										   \n";

if(tractionbc)
cout 
<<"										   \n"
<<"/***********************************IMPORTANT***********************************\n"
<<"*                                                                              *\n"
<<"* Using Neumann BC  please edit the file 'ControlParameters.edp'     	  *\n"
<<"*                                                                              *\n"
<<"* 1. Edit <<Tlabel>>  i.e. the  [int]   vector   of  labels  that contain your *\n"
<<"*    traction border. So  if your borders is labeled 1 Tlabel=[1], if you have *\n"
<<"*    two traction borders 4 & 5 then  Tlabel = [4,5].                          *\n"
<<"*                                                                              *\n"
<<"* 1. Edit macro <<T>> & provide three components of  traction on the boundary. *\n"
<<"*                                                                              *\n"
<<"*******************************************************************************/\n"
<<"										   \n";

} //-- [if loop terminator] help ended --//
