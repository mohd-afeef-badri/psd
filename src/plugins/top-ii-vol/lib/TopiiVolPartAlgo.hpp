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

//=============================================================================
// ---- Algorithm for top-ii-vol partitioning of point cloud
//=============================================================================

//----------------------------------------------------------------------------//
//---- Program variables -----
//----------------------------------------------------------------------------//

int fileNo  = 0 ;
int counter = 0 ;

double* xx = new double[pntx];
double* yy = new double[pntx];
double* zz = new double[pntx];

int *TNPts = new int[mpisize];

//----------------------------------------------------------------------------//
//---- Open input & output files -----
//----------------------------------------------------------------------------//

ifstream in  ;
in.open(*inputfile+".xyz");

ofstream wr  ;
wr.open(*outputfile+"_"+std::to_string(fileNo)+".xyz");

ofstream wr1 ;
wr1.open(*outputfile+"_"+std::to_string(fileNo)+".info");

//----------------------------------------------------------------------------//
//---- Print information  ----
//----------------------------------------------------------------------------//

cout << "                                                               \n"
     << "  # points in the .xyz ------------- "<< pntx*pnty << "        \n"
     << "  # points in X -------------------- "<< pntx << "             \n"
     << "  # points in Y -------------------- "<< pnty << "             \n"
     << "  # of strips ---------------------- "<< mpisize << "          \n"
     << "                                                               \n"
     << " *============================================================*\n"
     << "                                                               \n"
     << "  top-ii-vol is now stripping the point cloud .......          \n"
     << "                                                               \n"
     << "  writing "
     << string(*outputfile+"_"+std::to_string(fileNo)+".xyz")<<" ... "    ;

//----------------------------------------------------------------------------//
//---- Calculate total number of points held by each strip ----
//----------------------------------------------------------------------------//

for(int j = 0; j<mpisize; j++)
    TNPts[j]=(pnty+(mpisize-1))/mpisize;

for(int j = 0; j<((pnty+(mpisize-1))%mpisize); j++)
    TNPts[j]=TNPts[j]+1;

//----------------------------------------------------------------------------//
//---- Main loop to read point cloud and returns the strips ----
//----------------------------------------------------------------------------//

for(int j=1; j<=pnty; j++)
    {

        for(int i=1; i<=pntx; i++)
            {
                in >> std::fixed >> xx[i-1]         >> yy[i-1]         >> zz[i-1];
                wr << std::fixed << xx[i-1] << "\t" << yy[i-1] << "\t" << zz[i-1] << "\n";
            }

        counter++;

        if(counter==TNPts[fileNo] && fileNo < mpisize-1)
            {

                fileNo++;

                cout << "  done\n  writing "
                     << string(*outputfile+"_"+std::to_string(fileNo)+".xyz")
                     << " ... ";

                wr.close();
                wr.open(*outputfile+"_"+std::to_string(fileNo)+".xyz");

                wr1 << counter <<  "\t" <<  pntx << "\n";
                wr1.close();
                wr1.open(*outputfile+"_"+std::to_string(fileNo)+".info");

                counter = 0;
                counter++;

                for(int i=1; i<=pntx; i++)
                    wr<< std::fixed << xx[i-1] << "\t" << yy[i-1] << "\t" << zz[i-1] << "\n";
            }
    }

cout << "  done\n";
wr1  << counter <<  "\t" <<  pntx;

//----------------------------------------------------------------------------//
//---- Clean up variables memory optimization ----
//----------------------------------------------------------------------------//

delete[] TNPts;

delete[] xx;
delete[] yy;
delete[] zz;

in.close();
wr.close();
wr1.close();

//----------------------------------------------------------------------------//
//---- Prints footer ----
//----------------------------------------------------------------------------//

cout << "\n *============================================================*\n";
