   {
   
   ofstream script ("style.gnu");
   //script<<" set terminal tikz standalone" <<endl;
   script<<" set terminal pdfcairo enhanced color lw 3 size 3,2 font 'Arial-Bold'" <<endl;  
   script<<" set output 'matrix.pdf'" <<endl;  
   script<<" a=system(\"cat -n mat.dat | awk '{if ($1 == 3) print $2}'\")" << endl; 
   script<<" b=system(\"cat -n mat.dat | awk '{if ($1 == 3) print $5}'\")" << endl; 
   script<<" set tics nomirror out scale 0.75" <<endl;
   script<<" set size ratio -1 \n set xtics rotate" <<endl;
   script<<" set palette defined (0 0 0 0, 1 0 0 1, 3 0 1 0, 4 1 0 0, 6 1 1 1)" <<endl;
   script<<" f(x) = x>0 ? x : 1./10 " <<endl;
   script<<" set style fill transparent solid 0.8 noborder" <<endl;
   script<<" set yrange [a+1:-1]" <<endl;
   script<<" set xrange [-1:a+1]" <<endl;
   script<<" set title ' '"<<endl;
   script<<" plot '<sort -g -k3 mat.dat' u 1:2:(0.6):(f($3)) w circles lc palette t ''" <<endl;
   
   }
