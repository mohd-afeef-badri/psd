#!/usr/bin/env python

import sys
import salome

salome.salome_init()
###
### SHAPER component
###

from salome.shaper import model

model.begin()
partSet = model.moduleDocument()

### Create Part
Part_1 = model.addPart(partSet)
Part_1_doc = Part_1.document()

### Create Sketch
Sketch_1 = model.addSketch(Part_1_doc, model.defaultPlane("XOY"))

### Create SketchLine
SketchLine_1 = Sketch_1.addLine(0, 0, 5, 0)

### Create SketchProjection
SketchProjection_1 = Sketch_1.addProjection(model.selection("VERTEX", "PartSet/Origin"), False)
SketchPoint_1 = SketchProjection_1.createdFeature()
Sketch_1.setCoincident(SketchLine_1.startPoint(), SketchPoint_1.result())

### Create SketchProjection
SketchProjection_2 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OX"), False)
SketchLine_2 = SketchProjection_2.createdFeature()
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchLine_2.result())

### Create SketchLine
SketchLine_3 = Sketch_1.addLine(5, 0, 5, 1)
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchLine_3.startPoint())
Sketch_1.setVertical(SketchLine_3.result())

### Create SketchLine
SketchLine_4 = Sketch_1.addLine(5, 1, 0, 1)
Sketch_1.setCoincident(SketchLine_3.endPoint(), SketchLine_4.startPoint())

### Create SketchProjection
SketchProjection_3 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OY"), False)
SketchLine_5 = SketchProjection_3.createdFeature()
Sketch_1.setCoincident(SketchLine_4.endPoint(), SketchLine_5.result())
Sketch_1.setHorizontal(SketchLine_4.result())

### Create SketchLine
SketchLine_6 = Sketch_1.addLine(0, 1, 0, 0)
Sketch_1.setCoincident(SketchLine_4.endPoint(), SketchLine_6.startPoint())
Sketch_1.setCoincident(SketchLine_1.startPoint(), SketchLine_6.endPoint())
Sketch_1.setLength(SketchLine_1.result(), 5)
Sketch_1.setLength(SketchLine_3.result(), 1)
model.do()

### Create Face
Face_1 = model.addFace(Part_1_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_1r-SketchLine_3f-SketchLine_4f-SketchLine_6f")])

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_6")])
Group_1.setName("surface-left")
Group_1.result().setName("surface-left")

### Create Group
Group_2 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_4")])
Group_2.setName("surface-top")
Group_2.result().setName("surface-top")

### Create Group
Group_3 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_3")])
Group_3.setName("surface-right")
Group_3.result().setName("surface-right")

### Create Group
Group_4 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_1")])
Group_4.setName("surface-bottom")
Group_4.result().setName("surface-bottom")

### Create Group
Group_5 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Face_1_1")])
Group_5.setName("volume")
Group_5.result().setName("volume")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Face_1_1, surface_left, surface_top, surface_right, surface_bottom, volume, = SHAPERSTUDY.shape(model.featureStringId(Face_1))
###
### SMESH component
###

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

smesh = smeshBuilder.New()
#smesh.SetEnablePublish( False ) # Set to False to avoid publish in study if not needed or in some particular situations:
                                 # multiples meshes built in parallel, complex and numerous mesh edition (performance)

Mesh_1 = smesh.Mesh(Face_1_1,'Mesh_1')
NETGEN_1D_2D = Mesh_1.Triangle(algo=smeshBuilder.NETGEN_1D2D)
NETGEN_2D_Parameters_1 = NETGEN_1D_2D.Parameters()
NETGEN_2D_Parameters_1.SetMaxSize( 1./31 )
NETGEN_2D_Parameters_1.SetMinSize( 1./31 )
NETGEN_2D_Parameters_1.SetSecondOrder( 0 )
NETGEN_2D_Parameters_1.SetOptimize( 1 )
NETGEN_2D_Parameters_1.SetFineness( 2 )
NETGEN_2D_Parameters_1.SetChordalError( -1 )
NETGEN_2D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_2D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_2D_Parameters_1.SetFuseEdges( 1 )
NETGEN_2D_Parameters_1.SetWorstElemMeasure( 0 )
NETGEN_2D_Parameters_1.SetUseDelauney( 34 )
NETGEN_2D_Parameters_1.SetQuadAllowed( 0 )
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 128 )
surface_left = Mesh_1.GroupOnGeom(surface_left,'surface-left',SMESH.EDGE)
surface_top = Mesh_1.GroupOnGeom(surface_top,'surface-top',SMESH.EDGE)
surface_right = Mesh_1.GroupOnGeom(surface_right,'surface-right',SMESH.EDGE)
surface_bottom = Mesh_1.GroupOnGeom(surface_bottom,'surface-bottom',SMESH.EDGE)
volume_1 = Mesh_1.GroupOnGeom(volume,'volume',SMESH.FACE)
isDone = Mesh_1.Compute()
[ surface_left, surface_top, surface_right, surface_bottom, volume_1 ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'/home/mb258512/Work/repo/psd_sources/data/meshes/2D/Geo-Files/bar.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')


## Set names of Mesh objects
smesh.SetName(NETGEN_1D_2D.GetAlgorithm(), 'NETGEN 1D-2D')
smesh.SetName(volume_1, 'volume')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(surface_left, 'surface-left')
smesh.SetName(surface_top, 'surface-top')
smesh.SetName(surface_right, 'surface-right')
smesh.SetName(surface_bottom, 'surface-bottom')
smesh.SetName(NETGEN_2D_Parameters_1, 'NETGEN 2D Parameters_1')


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
