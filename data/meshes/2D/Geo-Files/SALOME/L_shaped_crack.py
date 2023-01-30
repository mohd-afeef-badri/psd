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
SketchLine_1 = Sketch_1.addLine(0, 0, 250, 0)

### Create SketchProjection
SketchProjection_1 = Sketch_1.addProjection(model.selection("VERTEX", "PartSet/Origin"), False)
SketchPoint_1 = SketchProjection_1.createdFeature()
Sketch_1.setCoincident(SketchLine_1.startPoint(), SketchPoint_1.result())

### Create SketchProjection
SketchProjection_2 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OX"), False)
SketchLine_2 = SketchProjection_2.createdFeature()
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchLine_2.result())

### Create SketchLine
SketchLine_3 = Sketch_1.addLine(250, 0, 250, 250)
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchLine_3.startPoint())
Sketch_1.setVertical(SketchLine_3.result())

### Create SketchLine
SketchLine_4 = Sketch_1.addLine(250, 250, 470, 250)
Sketch_1.setCoincident(SketchLine_3.endPoint(), SketchLine_4.startPoint())
Sketch_1.setHorizontal(SketchLine_4.result())

### Create SketchLine
SketchLine_5 = Sketch_1.addLine(470, 250, 500, 250)
Sketch_1.setCoincident(SketchLine_4.endPoint(), SketchLine_5.startPoint())
Sketch_1.setHorizontal(SketchLine_5.result())

### Create SketchLine
SketchLine_6 = Sketch_1.addLine(500, 250, 500, 500)
Sketch_1.setCoincident(SketchLine_5.endPoint(), SketchLine_6.startPoint())
Sketch_1.setVertical(SketchLine_6.result())

### Create SketchLine
SketchLine_7 = Sketch_1.addLine(500, 500, 0, 500)
Sketch_1.setCoincident(SketchLine_6.endPoint(), SketchLine_7.startPoint())

### Create SketchProjection
SketchProjection_3 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OY"), False)
SketchLine_8 = SketchProjection_3.createdFeature()
Sketch_1.setCoincident(SketchLine_7.endPoint(), SketchLine_8.result())
Sketch_1.setHorizontal(SketchLine_7.result())

### Create SketchLine
SketchLine_9 = Sketch_1.addLine(0, 500, 0, 0)
Sketch_1.setCoincident(SketchLine_7.endPoint(), SketchLine_9.startPoint())
Sketch_1.setCoincident(SketchLine_1.startPoint(), SketchLine_9.endPoint())
Sketch_1.setLength(SketchLine_5.result(), 30)
Sketch_1.setLength(SketchLine_7.result(), 500)
Sketch_1.setLength(SketchLine_4.result(), 220)
Sketch_1.setLength(SketchLine_9.result(), 500)
Sketch_1.setLength(SketchLine_3.result(), 250)
model.do()

### Create Face
Face_1 = model.addFace(Part_1_doc, [model.selection("COMPOUND", "all-in-Sketch_1")])

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_1")])
Group_1.setName("bot")
Group_1.result().setName("bot")

### Create Group
Group_2_objects = [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_3"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_4"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_5"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_6"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_7"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_9")]
Group_2 = model.addGroup(Part_1_doc, "Edges", Group_2_objects)
Group_2.setName("other")
Group_2.result().setName("other")

### Create Group
Group_3 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Face_1_1")])
Group_3.setName("volume")
Group_3.result().setName("volume")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Face_1_1, bot, other, volume, = SHAPERSTUDY.shape(model.featureStringId(Face_1))
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
NETGEN_2D_Parameters_1.SetMaxSize( 10 )
NETGEN_2D_Parameters_1.SetMinSize( 10 )
NETGEN_2D_Parameters_1.SetSecondOrder( 0 )
NETGEN_2D_Parameters_1.SetOptimize( 1 )
NETGEN_2D_Parameters_1.SetFineness( 2 )
NETGEN_2D_Parameters_1.SetChordalError( -1 )
NETGEN_2D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_2D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_2D_Parameters_1.SetFuseEdges( 1 )
NETGEN_2D_Parameters_1.SetWorstElemMeasure( 0 )
NETGEN_2D_Parameters_1.SetUseDelauney( 32 )
NETGEN_2D_Parameters_1.SetQuadAllowed( 0 )
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 0 )
bot_1 = Mesh_1.GroupOnGeom(bot,'bot',SMESH.EDGE)
other_1 = Mesh_1.GroupOnGeom(other,'other',SMESH.EDGE)
volume_1 = Mesh_1.GroupOnGeom(volume,'volume',SMESH.FACE)
isDone = Mesh_1.Compute()
[ bot_1, other_1, volume_1 ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'./L_shaped_crack.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')


## Set names of Mesh objects
smesh.SetName(NETGEN_1D_2D.GetAlgorithm(), 'NETGEN 1D-2D')
smesh.SetName(volume_1, 'volume')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(bot_1, 'bot')
smesh.SetName(other_1, 'other')
smesh.SetName(NETGEN_2D_Parameters_1, 'NETGEN 2D Parameters_1')


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
