'''
Author : MAB 
Date   : 10/03/2016
Comment: Gather together vtk files into single vtu file.
'''
from paraview.simple import *
import os
import sys

for i in range(0,int(sys.argv[2])):
  r = LegacyVTKReader( FileNames=[''+sys.argv[1]+''+str(i)+'.vtk'] )
  w = XMLUnstructuredGridWriter()
  w.FileName = ''+sys.argv[1]+''+str(i)+'.vtu'
  w.UpdatePipeline()
  os.system("rm "+sys.argv[1]+""+str(i)+".vtk")

target = open('output.pvd', 'w')
target.truncate()
target.write("<?xml version=\"1.0\"?>")
target.write("\n")
target.write("<VTKFile type=\"Collection\" version=\"0.1\"  byte_order=\"LittleEndian\" compressor=\"vtkZLibDataCompressor\">")
target.write("\n")
target.write("  <Collection>")
target.write("\n")
for i in range(0,int(sys.argv[2])):
  target.write("    <DataSet timestep=\"0\" group=\"\" part=\""+str(i)+"\"")
  target.write("\n")
  target.write("             file=\""+sys.argv[1]+""+str(i)+".vtu\"/>")
  target.write("\n")
target.write("  </Collection>")
target.write("\n")
target.write("</VTKFile>")
target.write("\n")
target.close()
