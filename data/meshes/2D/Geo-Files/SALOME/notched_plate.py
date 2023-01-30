#!/usr/bin/env python

import sys
import salome

salome.salome_init()

###
### SHAPER component
###

from SketchAPI import *

from salome.shaper import model

model.begin()
partSet = model.moduleDocument()

### Create Part
Part_1 = model.addPart(partSet)
Part_1_doc = Part_1.document()

### Create Sketch
Sketch_1 = model.addSketch(Part_1_doc, model.defaultPlane("XOY"))

### Create SketchPoint
SketchPoint_1 = Sketch_1.addPoint(0, 0)

### Create SketchProjection
SketchProjection_1 = Sketch_1.addProjection(model.selection("VERTEX", "PartSet/Origin"), False)
SketchPoint_2 = SketchProjection_1.createdFeature()
Sketch_1.setCoincident(SketchPoint_1.coordinates(), SketchPoint_2.result())

### Create SketchPoint
SketchPoint_3 = Sketch_1.addPoint(65, 0)

### Create SketchProjection
SketchProjection_2 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OX"), False)
SketchLine_1 = SketchProjection_2.createdFeature()
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchLine_1.result())

### Create SketchPoint
SketchPoint_4 = Sketch_1.addPoint(65, 120)

### Create SketchPoint
SketchPoint_5 = Sketch_1.addPoint(0, 120)

### Create SketchProjection
SketchProjection_3 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OY"), False)
SketchLine_2 = SketchProjection_3.createdFeature()
Sketch_1.setCoincident(SketchPoint_5.coordinates(), SketchLine_2.result())

### Create SketchPoint
SketchPoint_6 = Sketch_1.addPoint(0, 65.001)
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_2.result())

### Create SketchPoint
SketchPoint_7 = Sketch_1.addPoint(10, 65)

### Create SketchPoint
SketchPoint_8 = Sketch_1.addPoint(0, 64.999)
Sketch_1.setCoincident(SketchPoint_8.coordinates(), SketchLine_2.result())

### Create SketchPoint
SketchPoint_9 = Sketch_1.addPoint(36.5, 51)

### Create SketchLine
SketchLine_3 = Sketch_1.addLine(0, 0, 65, 0)
Sketch_1.setCoincident(SketchPoint_1.coordinates(), SketchLine_3.startPoint())
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchLine_3.endPoint())

### Create SketchLine
SketchLine_4 = Sketch_1.addLine(65, 0, 65, 120)
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchLine_4.startPoint())
Sketch_1.setCoincident(SketchPoint_4.coordinates(), SketchLine_4.endPoint())
Sketch_1.setVertical(SketchLine_4.result())

### Create SketchLine
SketchLine_5 = Sketch_1.addLine(65, 120, 0, 120)
Sketch_1.setCoincident(SketchPoint_4.coordinates(), SketchLine_5.startPoint())
Sketch_1.setCoincident(SketchPoint_5.coordinates(), SketchLine_5.endPoint())
Sketch_1.setHorizontal(SketchLine_5.result())

### Create SketchLine
SketchLine_6 = Sketch_1.addLine(0, 120, 0, 65.001)
Sketch_1.setCoincident(SketchPoint_5.coordinates(), SketchLine_6.startPoint())
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_6.endPoint())

### Create SketchLine
SketchLine_7 = Sketch_1.addLine(0, 65.001, 10, 65)
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_7.startPoint())
Sketch_1.setCoincident(SketchPoint_7.coordinates(), SketchLine_7.endPoint())

### Create SketchLine
SketchLine_8 = Sketch_1.addLine(10, 65, 0, 64.999)
Sketch_1.setCoincident(SketchPoint_7.coordinates(), SketchLine_8.startPoint())
Sketch_1.setCoincident(SketchPoint_8.coordinates(), SketchLine_8.endPoint())

### Create SketchLine
SketchLine_9 = Sketch_1.addLine(0, 64.999, 0, 0)
Sketch_1.setCoincident(SketchPoint_8.coordinates(), SketchLine_9.startPoint())
Sketch_1.setCoincident(SketchPoint_1.coordinates(), SketchLine_9.endPoint())

### Create SketchCircle
SketchCircle_1 = Sketch_1.addCircle(36.5, 51, 10)
Sketch_1.setCoincident(SketchPoint_9.coordinates(), SketchCircle_1.center())
Sketch_1.setLength(SketchLine_3.result(), 65)
Sketch_1.setLength(SketchLine_4.result(), 120)
Sketch_1.setRadius(SketchCircle_1.results()[1], 10)
Sketch_1.setHorizontalDistance(SketchPoint_9.coordinates(), SketchAPI_Point(SketchPoint_2).coordinates(), 36.5)
Sketch_1.setHorizontalDistance(SketchPoint_1.coordinates(), SketchPoint_7.coordinates(), 10)
Sketch_1.setVerticalDistance(SketchLine_8.startPoint(), SketchLine_9.endPoint(), 65)
Sketch_1.setLength(SketchLine_9.result(), 64.999)
Sketch_1.setVerticalDistance(SketchPoint_6.coordinates(), SketchAPI_Point(SketchPoint_2).coordinates(), 65.001)
Sketch_1.setVerticalDistance(SketchCircle_1.center(), SketchPoint_1.coordinates(), 51)
model.do()

### Create Face
Face_1 = model.addFace(Part_1_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_3f-SketchLine_4f-SketchLine_5f-SketchLine_6f-SketchLine_7f-SketchLine_8f-SketchLine_9f-SketchCircle_1_2r")])

### Create Vertex
Vertex_1 = model.addVertex(Part_1_doc, [model.selection("VERTEX", "Sketch_1/SketchPoint_7")], False)

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_3")])
Group_1.setName("bot")
Group_1.result().setName("bot")

### Create Group
Group_2 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_5")])
Group_2.setName("top")
Group_2.result().setName("top")

### Create Group
Group_3_objects = [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_4"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_6"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_9")]
Group_3 = model.addGroup(Part_1_doc, "Edges", Group_3_objects)
Group_3.setName("other")
Group_3.result().setName("other")

### Create Group
Group_4 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_7"), model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_8")])
Group_4.setName("mid")
Group_4.result().setName("mid")

### Create Group
Group_5 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Face_1_1")])
Group_5.setName("sur")
Group_5.result().setName("sur")

### Create Group
Group_6 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchCircle_1_2")])
Group_6.setName("notch")
Group_6.result().setName("notch")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Face_1_1, bot, top, other, mid, sur, notch, = SHAPERSTUDY.shape(model.featureStringId(Face_1))
Vertex_1_1, = SHAPERSTUDY.shape(model.featureStringId(Vertex_1))
###
### SMESH component
###

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

smesh = smeshBuilder.New()
#smesh.SetEnablePublish( False ) # Set to False to avoid publish in study if not needed or in some particular situations:
                                 # multiples meshes built in parallel, complex and numerous mesh edition (performance)

NETGEN_2D_Parameters_1 = smesh.CreateHypothesis('NETGEN_Parameters_2D', 'NETGENEngine')
NETGEN_2D_Parameters_1.SetMaxSize( 2.5 )
NETGEN_2D_Parameters_1.SetMinSize( 2.5 )
NETGEN_2D_Parameters_1.SetSecondOrder( 0 )
NETGEN_2D_Parameters_1.SetOptimize( 1 )
NETGEN_2D_Parameters_1.SetFineness( 2 )
NETGEN_2D_Parameters_1.SetChordalError( -1 )
NETGEN_2D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_2D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_2D_Parameters_1.SetFuseEdges( 1 )
NETGEN_2D_Parameters_1.SetWorstElemMeasure( 0 )
NETGEN_2D_Parameters_1.SetUseDelauney( 254 )
NETGEN_2D_Parameters_1.SetQuadAllowed( 0 )
NETGEN_2D_Parameters_1.SetLocalSizeOnShape(Vertex_1_1, 0.001)
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 0 )
NETGEN_1D_2D = smesh.CreateHypothesis('NETGEN_2D', 'NETGENEngine')
Mesh_1 = smesh.Mesh(Face_1_1,'Mesh_1')
status = Mesh_1.AddHypothesis(NETGEN_2D_Parameters_1)
status = Mesh_1.AddHypothesis(NETGEN_1D_2D)
bot_1 = Mesh_1.GroupOnGeom(bot,'bot',SMESH.EDGE)
top_1 = Mesh_1.GroupOnGeom(top,'top',SMESH.EDGE)
other_1 = Mesh_1.GroupOnGeom(other,'other',SMESH.EDGE)
mid_1 = Mesh_1.GroupOnGeom(mid,'mid',SMESH.EDGE)
sur_1 = Mesh_1.GroupOnGeom(sur,'sur',SMESH.FACE)
notch_1 = Mesh_1.GroupOnGeom(notch,'notch',SMESH.EDGE)
isDone = Mesh_1.Compute()
[ bot_1, top_1, other_1, mid_1, sur_1, notch_1 ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'./notched_plate.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')


## Set names of Mesh objects
smesh.SetName(sur_1, 'sur')
smesh.SetName(NETGEN_1D_2D, 'NETGEN 1D-2D')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(notch_1, 'notch')
smesh.SetName(mid_1, 'mid')
smesh.SetName(other_1, 'other')
smesh.SetName(top_1, 'top')
smesh.SetName(bot_1, 'bot')
smesh.SetName(NETGEN_2D_Parameters_1, 'NETGEN 2D Parameters_1')


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
