/*
 * Cube Example from Raphael Pour
 * adapted from the Pyramid example
 */
#include <osgDB\ReadFile>
#include <osgViewer\Viewer>

using namespace osgViewer;
using namespace osgDB;
using namespace osg;

int main(void)
{
	//
	// INITIALIZE OSG-DATA-STRUCTURE
	//

	// Create a new hierarchy by creating a root node
	Group *root = new Group();

	// Create a new geometry node for the cube.
	// A Geometry Node (=Geode) extends a node with the possibility
	// to hold any amount of 'drawables' for example a Geometry Object
	Geode *cubeGeode = new Geode();

	// Create a new geometry for the cube
	// A Geometry Object holds the Vertex Information of a geometric object
	// For example: Position, Color, Normal, Texture Coordinate
	Geometry *cubeGeometry = new Geometry();

	// Add geometry to the cubes geometry node
	cubeGeode->addDrawable(cubeGeometry);
	
	// Add the geometry node of the cube to the hierarchy
	root->addChild(cubeGeode);


	//
	// DEFINE VERTICES
	//

	Vec3Array* cubeVertices = new Vec3Array;
	
	// All Vertices of a cube: {0,1}^3
	cubeVertices->push_back(Vec3(0, 0, 0)); // 0
	cubeVertices->push_back(Vec3(0, 0, 1)); // 1
	cubeVertices->push_back(Vec3(0, 1, 0)); // 2
	cubeVertices->push_back(Vec3(0, 1, 1)); // 3
	cubeVertices->push_back(Vec3(1, 0, 0)); // 4
	cubeVertices->push_back(Vec3(1, 0, 1)); // 5
	cubeVertices->push_back(Vec3(1, 1, 0)); // 6
	cubeVertices->push_back(Vec3(1, 1, 1)); // 7

	cubeGeometry->setVertexArray(cubeVertices);


	//
	// DEFINE GRAPHIC OBJECT ELEMENTS WITH POSITION
	//

	
	// Create a new Graphic Element
	DrawElementsUInt *cubeFront = new DrawElementsUInt(PrimitiveSet::QUADS, 4);
	// Push the index of our the previously defined vertice in order
	// to create an object with it
	cubeFront->push_back(0);
	cubeFront->push_back(4);
	cubeFront->push_back(6);
	cubeFront->push_back(2);

	// Add the new Graphic Element to our cube geometry
	cubeGeometry->addPrimitiveSet(cubeFront);

	DrawElementsUInt *cubeBack = new DrawElementsUInt(PrimitiveSet::QUADS, 4);
	cubeBack->push_back(5);
	cubeBack->push_back(1);
	cubeBack->push_back(3);
	cubeBack->push_back(7);
	cubeGeometry->addPrimitiveSet(cubeBack);

	DrawElementsUInt *cubeLeft = new DrawElementsUInt(PrimitiveSet::QUADS, 4);
	cubeLeft->push_back(1);
	cubeLeft->push_back(0);
	cubeLeft->push_back(2);
	cubeLeft->push_back(3);
	cubeGeometry->addPrimitiveSet(cubeLeft);

	DrawElementsUInt *cubeRight = new DrawElementsUInt(PrimitiveSet::QUADS, 4);
	cubeRight->push_back(4);
	cubeRight->push_back(5);
	cubeRight->push_back(7);
	cubeRight->push_back(6);
	cubeGeometry->addPrimitiveSet(cubeRight);

	DrawElementsUInt *cubeTop = new DrawElementsUInt(PrimitiveSet::QUADS, 4); 
	cubeTop->push_back(2);
	cubeTop->push_back(6);
	cubeTop->push_back(7);
	cubeTop->push_back(3);
	cubeGeometry->addPrimitiveSet(cubeTop);
	
	DrawElementsUInt *cubeBottom = new DrawElementsUInt(PrimitiveSet::QUADS, 4);
	cubeBottom->push_back(5);
	cubeBottom->push_back(1);
	cubeBottom->push_back(0);
	cubeBottom->push_back(4);
	cubeGeometry->addPrimitiveSet(cubeBottom);


	//
	// DEFINE GRAPHIC OBJECT COLORS
	//

	Vec4Array *cubeColors = new Vec4Array;
	
	// Index of color = Index of vertex
	// This means that the vertex with index 0 has the
	// color black
	cubeColors->push_back(Vec4(0.f, 0.f, 0.f, 1.f)); // 0
	cubeColors->push_back(Vec4(0.f, 0.f, 1.f, 1.f)); // 1
	cubeColors->push_back(Vec4(0.f, 1.f, 0.f, 1.f)); // 2
	cubeColors->push_back(Vec4(0.f, 1.f, 1.f, 1.f)); // 3
	cubeColors->push_back(Vec4(1.f, 0.f, 0.f, 1.f)); // 4
	cubeColors->push_back(Vec4(1.f, 0.f, 1.f, 1.f)); // 5
	cubeColors->push_back(Vec4(1.f, 1.f, 0.f, 1.f)); // 6
	cubeColors->push_back(Vec4(1.f, 1.f, 1.f, 1.f)); // 7

	// Add the colors to our cube geometry 
	cubeGeometry->setColorArray(cubeColors);
	cubeGeometry->setColorBinding(Geometry::BIND_PER_VERTEX);

	// Create a new Viewer (including the GUI and some basic
	// mouse/keyboard interactions) which can render our cube<
	Viewer v;
	v.setSceneData(root);
	v.run();

}