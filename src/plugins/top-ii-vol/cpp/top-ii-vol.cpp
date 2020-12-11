/*****************************************************************************

             This file is a part of top-ii-vol meshing tools.

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@hotmail.com
     Date     : 2019‑03‑29

     -------------------------------------------------------------------

     top-ii-vol  provides  sequential  and  parallel tools for  creating
     volumic tetrahedral meshes from a topology defined by apoint cloud.
     top-ii-vol  is  distributed in the hope that it will be useful, but
     WITHOUT  ANY  WARRANTY; or  without  even  the  implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*******************************************************************************/


#include "ff++.hpp"
#include <mpi.h>

using namespace std;

template<class K>
class partPointCloud_Op : public E_F0mps
{
public:
    Expression filename			;

    static const int n_name_param = 8		;
    static basicAC_F0::name_and_type name_param[]	;
    Expression nargs[n_name_param]			;

    partPointCloud_Op(const basicAC_F0& args		,
                      Expression param1
                     ) :
        filename     (param1)
    {
        args.SetNameParam(n_name_param	,
                          name_param	,
                          nargs
                         )		;
    }

    AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type partPointCloud_Op<K>::name_param[] =
{
    {"outfile", &typeid(std::string*)},
    {"pointsx", &typeid(long)},
    {"pointsy", &typeid(long)},
    {"pointsz", &typeid(long)},
    {"zdepth", &typeid(double)},       
    {"partx"  , &typeid(long)},
    {"party"  , &typeid(long)},    
    {"partz"  , &typeid(long)}
};


template<class K>
class partPointCloud : public OneOperator
{
public:
    partPointCloud() : OneOperator(atype<long>()	,
                                       atype<string*>()
                                      ) {}

    E_F0* code(const basicAC_F0& args) const
    {
        return new partPointCloud_Op<K>(args,
                                        t[0]->CastTo(args[0])
                                       );
    }
};


template<class K>
AnyType partPointCloud_Op<K>::operator()(Stack stack) const
{
    string* inputfile  = GetAny<string*>((*filename)(stack))	;
    string* outputfile = nargs[0] ? GetAny<std::string*>((*nargs[0])(stack)) : NULL;
    int     pntx       = nargs[1] ? GetAny<long>((*nargs[1])(stack)) : -1;
    int     pnty       = nargs[2] ? GetAny<long>((*nargs[2])(stack)) : -1;
    int     pntz       = nargs[3] ? GetAny<long>((*nargs[3])(stack)) : -1;
    double  zmax       = nargs[4] ? GetAny<double>((*nargs[4])(stack)) : -1.;        
    int     NpX        = nargs[5] ? GetAny<long>((*nargs[5])(stack)) : -1;
    int     NpY        = nargs[6] ? GetAny<long>((*nargs[6])(stack)) : -1;
    int     NpZ        = nargs[7] ? GetAny<long>((*nargs[7])(stack)) : -1;        

//    cout << " Px "<< pntx << " py  "<<pnty  << " Name input "<< *inputfile << " Name output "<< *outputfile << endl;

    string *time_log  = new string();
    *time_log  = "";

    double t_phase    ; 
    t_phase = MPI_Wtime();  


    if(mpirank == 0)
        {

#include "./../lib/LogoTopiiVolCpp.hpp"
//#include "./../lib/TopiiVolPartAlgo1D2D3D.hpp"       
        }
        {                                              // Temporary solution
#include "./../lib/TopiiVolParPartAlgo1D2D3D.hpp"      // Temporary solution        
        }                                              // Temporary solution


    t_phase = MPI_Wtime() - t_phase;
    *time_log = string( *time_log+"\tPoint cloud partitioning : "
                        +std::to_string(t_phase)+" s\n"           );

    if(mpirank==0)
        {
            cout << "                                                               \n"
                 << " *============================================================*\n"
                 <<  "  Time-log:\n"
                 << *time_log
                 << " *============================================================*\n"
                 << "                                                               \n";
        }

    return 0L;
}


template<class K>
class meshPointCloud_Op : public E_F0mps
{
public:
    Expression filename			;

    static const int n_name_param = 6		;
    static basicAC_F0::name_and_type name_param[]	;
    Expression nargs[n_name_param]			;

    meshPointCloud_Op(const basicAC_F0& args		,
                      Expression param1
                     ) :
        filename     (param1)
    {
        args.SetNameParam(n_name_param	,
                          name_param	,
                          nargs
                         )		;
    }

    AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type meshPointCloud_Op<K>::name_param[] =
{
    {"outfile", &typeid(std::string*)},
    {"pointsz", &typeid(long)},
    {"zdepth", &typeid(double)},
    {"partx"  , &typeid(long)},
    {"party"  , &typeid(long)},    
    {"partz"  , &typeid(long)}
};


template<class K>
class meshPointCloud : public OneOperator
{
public:
    meshPointCloud() : OneOperator(atype<long>()	,
                                       atype<string*>()
                                      ) {}

    E_F0* code(const basicAC_F0& args) const
    {
        return new meshPointCloud_Op<K>(args,
                                        t[0]->CastTo(args[0])
                                       );
    }
};

template<class K>
AnyType meshPointCloud_Op<K>::operator()(Stack stack) const
{
    string* inputfile  = GetAny<string*>((*filename)(stack))	;
    string* outputfile = nargs[0] ? GetAny<std::string*>((*nargs[0])(stack)) : NULL;
    int     pntz       = nargs[1] ? GetAny<long>((*nargs[1])(stack)) : -1;
    double  zmax       = nargs[2] ? GetAny<double>((*nargs[2])(stack)) : -1.;
    int     NpX        = nargs[3] ? GetAny<long>((*nargs[3])(stack)) : -1;
    int     NpY        = nargs[4] ? GetAny<long>((*nargs[4])(stack)) : -1;
    int     NpZ        = nargs[5] ? GetAny<long>((*nargs[5])(stack)) : -1;    

//    string* outputfile= GetAny<string*>((*outname)(stack))	;
//    int     pntz      = GetAny<long>((*ptz)(stack))	        ;
//    double  zmax      = GetAny<double>((*dpth)(stack))	    ;


    string *time_log  = new string();
    *time_log  = "";

    int pnty;
    int pntx;

    double t1 = 0     ,
           t_phase    ; 

    if(mpirank==0)
#include "./../lib/LogoTopiiVolCpp.hpp"
#include "./../lib/TopiiVolMeshAlgo1D2D3D.hpp"

    if(mpirank==0)
        {
            cout << "                                                               \n"
                 << " *============================================================*\n"
                 <<  "  Time-log:\n"
                 << *time_log
                 << " *============================================================*\n"
                 << "                                                               \n";
        }

    return 0L;
    };

static void InitFF()
{
    Global.Add("topiivolpart", "(", new partPointCloud<double>);
    Global.Add("topiivolmesh", "(", new meshPointCloud<double>);
}
LOADFUNC(InitFF)

