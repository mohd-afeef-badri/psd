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
SketchLine_1 = Sketch_1.addLine(1, 0, 0, 0)

### Create SketchProjection
SketchProjection_1 = Sketch_1.addProjection(model.selection("VERTEX", "PartSet/Origin"), False)
SketchPoint_1 = SketchProjection_1.createdFeature()
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchPoint_1.result())

### Create SketchLine
SketchLine_2 = Sketch_1.addLine(0, 0, 0, 1)

### Create SketchLine
SketchLine_3 = Sketch_1.addLine(0, 1, 1, 1)

### Create SketchLine
SketchLine_4 = Sketch_1.addLine(1, 1, 1, 0)
Sketch_1.setCoincident(SketchLine_4.endPoint(), SketchLine_1.startPoint())
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchLine_2.startPoint())
Sketch_1.setCoincident(SketchLine_2.endPoint(), SketchLine_3.startPoint())
Sketch_1.setCoincident(SketchLine_3.endPoint(), SketchLine_4.startPoint())
Sketch_1.setHorizontal(SketchLine_1.result())
Sketch_1.setVertical(SketchLine_2.result())
Sketch_1.setHorizontal(SketchLine_3.result())
Sketch_1.setVertical(SketchLine_4.result())
Sketch_1.setLength(SketchLine_1.result(), 1)
Sketch_1.setLength(SketchLine_4.result(), 1)
model.do()

### Create Face
Face_1 = model.addFace(Part_1_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_4r-SketchLine_3r-SketchLine_2r-SketchLine_1r")])

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Face_1_1")])
Group_1.setName("volume")
Group_1.result().setName("volume")

### Create Group
Group_2 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_2")])
Group_2.setName("surface-left")
Group_2.result().setName("surface-left")

### Create Group
Group_3 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_3")])
Group_3.setName("surface-top")
Group_3.result().setName("surface-top")

### Create Group
Group_4 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_4")])
Group_4.setName("surface-right")
Group_4.result().setName("surface-right")

### Create Group
Group_5 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_1")])
Group_5.setName("surface-bottom")
Group_5.result().setName("surface-bottom")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Face_1_1, volume, surface-left, surface-top, surface-right, surface-bottom, = SHAPERSTUDY.shape(model.featureStringId(Face_1))
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
NETGEN_2D_Parameters_1.SetMaxSize( 0.1 )
NETGEN_2D_Parameters_1.SetMinSize( 0.1 )
NETGEN_2D_Parameters_1.SetSecondOrder( 0 )
NETGEN_2D_Parameters_1.SetOptimize( 1 )
NETGEN_2D_Parameters_1.SetFineness( 2 )
NETGEN_2D_Parameters_1.SetChordalError( -1 )
NETGEN_2D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_2D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_2D_Parameters_1.SetFuseEdges( 1 )
NETGEN_2D_Parameters_1.SetWorstElemMeasure( 0 )
NETGEN_2D_Parameters_1.SetUseDelauney( 248 )
NETGEN_2D_Parameters_1.SetQuadAllowed( 0 )
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 128 )
volume_1 = Mesh_1.GroupOnGeom(volume,'volume',SMESH.FACE)
surface_left = Mesh_1.GroupOnGeom(surface-left,'surface-left',SMESH.EDGE)
surface_top = Mesh_1.GroupOnGeom(surface-top,'surface-top',SMESH.EDGE)
surface_right = Mesh_1.GroupOnGeom(surface-right,'surface-right',SMESH.EDGE)
surface_bottom = Mesh_1.GroupOnGeom(surface-bottom,'surface-bottom',SMESH.EDGE)
isDone = Mesh_1.Compute()
[ volume_1, surface_left, surface_top, surface_right, surface_bottom ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'./quasistatic.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
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
