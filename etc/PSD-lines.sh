cd ..;
echo "---------------------------------------------------------------"
echo "TOTAL"
echo "---------------------------------------------------------------"
find * -regextype posix-extended -regex '.*\.(edp|cpp|h|hpp|c|geo|am|ac|MD|script|mfront)' | xargs wc -l
echo "---------------------------------------------------------------"
echo "MESHING"
echo "---------------------------------------------------------------"
find * -regextype posix-extended -regex '.*\.(geo)' | xargs wc -l
