/*****************************************************************************

             This file is a part of top-ii-vol meshing tools.

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@hotmail.com
     Date     : 2020‑10‑15

     -------------------------------------------------------------------

     top-ii-vol  provides  sequential  and  parallel tools for  creating
     volumic tetrahedral meshes from a topology defined by a point cloud.
     top-ii-vol  is  distributed in the hope that it will be useful, but
     WITHOUT  ANY  WARRANTY; or  without  even  the  implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*******************************************************************************/

//=============================================================================
// ---- Algorithm for top-ii-vol 2D partitioning of point cloud 
//=============================================================================

//----------------------------------------------------------------------------//
//---- Program variables -----
//----------------------------------------------------------------------------//

int counter   = 0;
int stripy    = 0;
int fileindex = 0;

double* xx = new double[pntx];
double* yy = new double[pntx];
double* zz = new double[pntx];

//----------------------------------------------------------------------------//
//---- Determining the patition number -----
//----------------------------------------------------------------------------//

if(*method=="1D")
  {
  if(pnty>=pntx)
    {
    NpX = 1;       
    NpY = mpisize;
    }
  else
    {
    NpX = mpisize;       
    NpY = 1;
    }
  }

//----------------------------------------------------------------------------//
//---- Open input file -----
//----------------------------------------------------------------------------//

ifstream in  ;
in.open(*inputfile+".xyz");

//----------------------------------------------------------------------------//
//---- Open output file -----
//----------------------------------------------------------------------------//

ofstream outputWrite[NpX*NpY];
ofstream infoWrite[NpX*NpY];

for(int j = 0; j<NpX*NpY; j++)
  {
   outputWrite[j].open(*outputfile+"_"+std::to_string(j)+".xyz");
   infoWrite[j].open(*outputfile+"_"+std::to_string(j)+".info");  
  }

//----------------------------------------------------------------------------//
//---- Divisions in X and Y -----
//----------------------------------------------------------------------------//

int *TNPtsx = new int[NpX];
int *TNPtsy = new int[NpY];


//----------------------------------------------------------------------------//
//---- Print information  ----
//----------------------------------------------------------------------------//

cout << "  # points in the .xyz ------------- "<< pntx*pnty << "        \n"
     << "  # points in X -------------------- "<< pntx << "             \n"
     << "  # points in Y -------------------- "<< pnty << "             \n"
     << "  # of strips ---------------------- "<< mpisize << "          \n"
     << "                                                               \n"
     << " *============================================================*\n"
     << "                                                               \n"
     << "  top-ii-vol is now stripping the point cloud .......          \n"
     << "                                                               \n"
     << "  writing "
     << string(*outputfile+"_"+std::to_string(stripy)+".xyz")<<" ... "    ;

//----------------------------------------------------------------------------//
//---- Calculate total number of points held by each strip ----
//----------------------------------------------------------------------------//

for(int j = 0; j<NpY; j++)
  TNPtsy[j] = (pnty+(NpY-1))/NpY;

for(int j = 0; j<((pnty+(NpY-1))%NpY); j++)
  TNPtsy[j] = TNPtsy[j]+1;
    
for(int j = 0; j<NpX; j++)
  TNPtsx[j] = (pntx+(NpX-1))/NpX;

for(int j = 0; j<((pntx+(NpX-1))%NpX); j++)
  TNPtsx[j] = TNPtsx[j]+1;

//----------------------------------------------------------------------------//
//---- Main loop to read point cloud and returns the strips ----
//----------------------------------------------------------------------------//
      
int kstrat = 0,
    kend   = TNPtsx[0];


for(int j=1; j<=pnty; j++)
  {
   for(int i=1; i<=pntx; i++)
     in >> std::fixed >> xx[i-1]         >> yy[i-1]         >> zz[i-1];
              
   for(int i=0; i <NpX; i++)
     {
      fileindex = i +  stripy*NpX;                            
      for(int k = kstrat; k<kend; k++)
        outputWrite[fileindex] << std::fixed << xx[k] << "\t" << yy[k] << "\t" << zz[k] << "\n"; 
      kstrat  = kend -1;
      kend   += TNPtsx[i+1] -1;
     }

   counter++;

   if(counter==TNPtsy[stripy] && stripy < NpY -1)
     {
      stripy++;
      kstrat  = 0;
      kend    = TNPtsx[0];
      for(int i=0; i <NpX; i++)
        {
         fileindex = i +  stripy*NpX;
         for(int k = kstrat; k<kend; k++)
           outputWrite[fileindex] << std::fixed << xx[k] << "\t" << yy[k] << "\t" << zz[k] << "\n"; 
         kstrat  = kend -1;
         kend   += TNPtsx[i+1] -1;
         infoWrite[i +  (stripy-1)*NpX] << counter <<  "\t" <<  TNPtsx[i] << "\n";
        }
      counter = 0;
      counter++;
     }
   kstrat = 0;
   kend   = TNPtsx[0];           
  }


for(int i=0; i <NpX; i++)
 {
  fileindex = i +  (NpY -1)*NpX;
  infoWrite[fileindex] << counter <<  "\t" <<  TNPtsx[i] << "\n";
 } 

cout << "  done\n";

//----------------------------------------------------------------------------//
//---- Clean up variables memory optimization ----
//----------------------------------------------------------------------------//

delete[] TNPtsy;
delete[] TNPtsx;

delete[] xx;
delete[] yy;
delete[] zz;

in.close();

for(int j = 0; j<NpX*NpY; j++)
 {
  outputWrite[j].close();
  infoWrite[j].close();  
 }   
  
cout << "\n *============================================================*\n";
