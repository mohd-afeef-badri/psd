/*****************************************************************************

             This file is a part of top-ii-vol meshing tools.

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@hotmail.com
     Date     : 2019‑03‑29

     -------------------------------------------------------------------

     top-ii-vol  provides  sequential  and  parallel tools for  creating
     volumic tetrahedral meshes from a topology defined by a point cloud.
     top-ii-vol  is  distributed in the hope that it will be useful, but
     WITHOUT  ANY  WARRANTY; or  without  even  the  implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*******************************************************************************/

//-----------------------------------------------------------------------------------//
//---- Global Variables -----
//-----------------------------------------------------------------------------------//

double xx	  ;
double yy	  ;
double zz	  ;
double delz	  ;
double zznew  ;

int IJK	      ;
int Ip1JK	  ;
int IJp1K	  ;
int IJKp1	  ;
int Ip1JKp1	  ;
int IJp1Kp1	  ;
int Ip1Jp1K	  ;
int Ip1Jp1Kp1 ;


//-----------------------------------------------------------------------------------//
//---- Calculating Parameters -----
//-----------------------------------------------------------------------------------//

ifstream in;
in.open(*inputfile+"_"+std::to_string(mpirank)+".xyz");

ifstream in1;
in1.open(*inputfile+"_"+std::to_string(mpirank)+".info");

ofstream wrgmsh;
wrgmsh.open(*outputfile+"_"+std::to_string(mpirank)+".mesh");

in1 >> pnty >> pntx;
in1.close() ;


if(mpirank==(mpisize-1))pnty=pnty-1; // Last mpirank does not have comman partion

//-----------------------------------------------------------------------------------//
//---- Calculating Parameters -----
//-----------------------------------------------------------------------------------//

int PxM1 = pntx-1                                       ;
int PyM1 = pnty-1                                       ;
int PzM1 = pntz-1                                       ;
int PxPz = pntx*pntz									;
int PxPy = pntx*pnty									;

int NPnt = pntx * pnty * pntz					        ;
int NTri = 4*( PzM1*PxM1 + PyM1*PzM1 + PxM1*PyM1 )      ;
int NTet = PxM1 * PyM1 * PzM1 * 6			            ;



/*
//=============================================================================
// ------------- Commandline  output ------------------
//=============================================================================



    MPI_Barrier(MPI_COMM_WORLD);

    cout << "                                                               \n"
         << "           MPI Processs # "<<mpirank <<"                       \n"
         << "                                                               \n"
         << "  # points in the .xyz ------------- "<< PxPy << "             \n"
         << "  # points in X -------------------- "<< pntx << "             \n"
         << "  # points in Y -------------------- "<< pnty << "             \n"
         << "                                                               \n"
         << " *============================================================*\n";
*/

//-----------------------------------------------------------------------------------//
//---- Header for mesh -----
//-----------------------------------------------------------------------------------//

wrgmsh << "MeshVersionFormatted 1\n\n"
       << "Dimension 3\n\n";

//-----------------------------------------------------------------------------------//
//---- Generating points -----
//-----------------------------------------------------------------------------------//

cout   << "Generating points ........"		               ;
wrgmsh << "Vertices\n"
       <<  NPnt	<<"\n";

for(int i=0; i<PxPy; i++)
    {
        in     >> std::fixed >> xx >>        yy        >> zz                 ;
        wrgmsh << std::fixed << xx << "\t" << yy << "\t" << zz << " 0\n"     ;

        zznew=zz;
        delz= (zmax-zz)/PzM1;
        for(int j=0; j<PzM1; j++)
            {
                zznew  = zznew + delz;
                wrgmsh << std::fixed << xx << "\t" << yy << "\t" << zznew << " 0\n";
            }
    }

wrgmsh << "\n";
cout   << " finished for MPI rank : " << mpirank << "\n";

//-----------------------------------------------------------------------------------//
//---- Generating Tetrahedra -----
//-----------------------------------------------------------------------------------//

cout   << "Generating Tetrahedra ...."			       ;
wrgmsh << "Tetrahedra\n"
       <<  NTet <<"\n";

for(int j=0; j<PyM1;  j++)
    {
        for(int i=0; i<PxM1;  i++)
            {
                for(int k=1; k<=PzM1; k++)
                    {

                        IJK	        =	i*pntz  + j*PxPz + k  ;
                        Ip1JK	    =	IJK 	+ PxPz		  ;
                        IJp1K	    =	IJK 	+ pntz		  ;
                        Ip1Jp1K     =	IJK 	+ PxPz + pntz ;
                        IJKp1       =	IJK 	+ 1			  ;
                        Ip1JKp1     =	Ip1JK 	+ 1			  ;
                        IJp1Kp1     =	IJp1K   + 1			  ;
                        Ip1Jp1Kp1   =	Ip1Jp1K + 1			  ;

                        wrgmsh << std::fixed << IJK     << "\t" << IJKp1   << "\t" << IJp1K     << "\t" << Ip1Jp1K << " 0\n"
                               << IJKp1   << "\t" << IJK     << "\t" << Ip1JK     << "\t" << Ip1Jp1K << " 0\n"
                               << Ip1JKp1 << "\t" << IJKp1   << "\t" << Ip1JK     << "\t" << Ip1Jp1K << " 0\n"
                               << IJKp1   << "\t" << Ip1JKp1 << "\t" << Ip1Jp1Kp1 << "\t" << Ip1Jp1K << " 0\n"
                               << IJp1Kp1 << "\t" << IJKp1   << "\t" << Ip1Jp1Kp1 << "\t" << Ip1Jp1K << " 0\n"
                               << IJKp1   << "\t" << IJp1Kp1 << "\t" << IJp1K     << "\t" << Ip1Jp1K << " 0\n";
                    }
            }
    }

wrgmsh << "\n";
cout   << " finished for MPI rank : " << mpirank << "\n";

//-----------------------------------------------------------------------------------//
//---- Generating Triangles -----
//-----------------------------------------------------------------------------------//

cout   << "Generating Triangles ....."			       ;
wrgmsh << "Triangles\n"
       << NTri << "\n";

//----X-MIN-PLANE---//

for(int i=0; i<PyM1;  i++)
    {
        for(int j=0; j<PzM1;  j++)
            {

                IJK	      =	i*PxPz + j + 1	;
                IJKp1	  =	IJK + 1			;
                Ip1JK	  =	IJK + PxPz    	;
                Ip1JKp1   =	Ip1JK + 1		;

                wrgmsh << std::fixed << IJKp1   << "\t" <<  IJK  << "\t" << Ip1JK << " 1\n"
                       << Ip1JKp1 << "\t" << IJKp1 << "\t" << Ip1JK << " 1\n";
            }
    }


//----Y-MIN-PLANE----//
int labymin=99099;

if(mpirank==0)labymin=2;

for(int i=0; i<PxM1;  i++)
    {
        for(int j=0; j<PzM1;  j++)
            {

                IJK	      =	i*pntz + j + 1	;
                IJKp1	  =	IJK + 1		    ;
                IJp1K	  =	IJK + pntz	    ;
                IJp1Kp1   =	IJp1K + 1	    ;

                wrgmsh << std::fixed << IJK   << "\t" << IJKp1   << "\t" << IJp1K << "\t" << labymin << "\n"
                       << IJKp1 << "\t" << IJp1Kp1 << "\t" << IJp1K << "\t" << labymin << "\n";

            }
    }


//----Z-MIN-PLANE----//
for(int i=0; i<PyM1;  i++)
    {
        for(int j=0; j<PxM1;  j++)
            {

                IJK	      =	i*PxPz + j*pntz +1	    ;
                Ip1JK	  =	IJK + PxPz         		;
                IJp1K	  =	IJK + pntz		    	;
                Ip1Jp1K   =	Ip1JK + pntz			;

                wrgmsh << std::fixed << IJK   << "\t" << IJp1K << "\t" << Ip1Jp1K << " 3\n"
                       << Ip1JK << "\t" << IJK   << "\t" << Ip1Jp1K << " 3\n";
            }
    }

//----X-MAX-PLANE----//
for(int i=0; i<PyM1;  i++)
    {
        for(int j=0; j<PzM1;  j++)
            {

                IJK	      =	i*PxPz + j+1 + PxM1*(pntz)	;
                IJKp1	  =	IJK + 1					        ;
                Ip1JK	  =	IJK + PxPz			            ;
                Ip1JKp1   =	Ip1JK + 1				        ;

                wrgmsh << std::fixed << IJK   << "\t" << IJKp1   << "\t" << Ip1JK << " 4\n"
                       << IJKp1 << "\t" << Ip1JKp1 << "\t" << Ip1JK << " 4\n";


            }
    }


//----Y-MAX-PLANE----//
int labymax=99099;

if(mpirank==(mpisize-1))labymax=5;

for(int i=0; i<PxM1;  i++)
    {
        for(int j=0; j<PzM1;  j++)
            {

                IJK	      =	i*pntz + j+1 + PxPz*PyM1	;
                IJKp1	  =	IJK + 1					    ;
                IJp1K	  =	IJK + pntz				    ;
                IJp1Kp1   =	IJp1K + 1				    ;

                wrgmsh << std::fixed << IJKp1   << "\t" << IJK   << "\t" << IJp1K << "\t" << labymax << "\n"
                       << IJp1Kp1 << "\t" << IJKp1 << "\t" << IJp1K << "\t" << labymax << "\n";

            }
    }
//}

//----Z-MAX-PLANE----//
for(int i=0; i<PyM1;  i++)
    {
        for(int j=0; j<PxM1;  j++)
            {

                IJK	      =	i*PxPz + j*pntz + 1 + PzM1	;
                Ip1JK	  =	IJK + PxPz			        ;
                IJp1K	  =	IJK + pntz				    ;
                Ip1Jp1K   =	Ip1JK + pntz				;

                wrgmsh << std::fixed << IJp1K << "\t" << IJK   << "\t" << Ip1Jp1K << " 6\n"
                       << IJK   << "\t" << Ip1JK << "\t" << Ip1Jp1K << " 6\n";
            }
    }

cout   << " finished for MPI rank : " << mpirank << "\n";

//-----------------------------------------------------------------------------------//
//---- Finishing footer -----
//-----------------------------------------------------------------------------------//

wrgmsh << "\n"
       << "End\n";
