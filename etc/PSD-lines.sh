cd ..; 
find * -regextype posix-extended -regex '.*\.(edp|cpp|h|hpp|c|geo|am|ac|MD|script)' | xargs wc -l
