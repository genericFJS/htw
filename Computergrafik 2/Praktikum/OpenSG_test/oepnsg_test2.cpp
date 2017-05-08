/*
 * OpenSceneGraph Tutorial Example 2
 *
 */
#include <osgDB\ReadFile>
#include <osgViewer\Viewer>

using namespace std;
using namespace osgViewer;
using namespace osgDB;
using namespace osg;

int main(void)
{
	Group* root = new Group();
	Geode* pyramidGeode = new Geode();
	Geometry* pyramidGeometry = new Geometry();

	pyramidGeode->addDrawable(pyramidGeometry);
	root->addChild(pyramidGeode);

	Vec3Array* pyramidVertices = new Vec3Array;
	pyramidVertices->push_back(Vec3(0, 0, 0));
	pyramidVertices->push_back(Vec3(10, 0, 0));
	pyramidVertices->push_back(Vec3(10, 10, 0));
	pyramidVertices->push_back(Vec3(0, 10, 0));
	pyramidVertices->push_back(Vec3(5, 5, 10));

	pyramidGeometry->setVertexArray(pyramidVertices);

	DrawElementsUInt* pyramidBase = new DrawElementsUInt(PrimitiveSet::QUADS, 0);
	pyramidBase->push_back(3);
	pyramidBase->push_back(2);
	pyramidBase->push_back(1);
	pyramidBase->push_back(0);
	pyramidGeometry->addPrimitiveSet(pyramidBase);

	osg::DrawElementsUInt* pyramidFaceOne =
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceOne->push_back(0);
	pyramidFaceOne->push_back(1);
	pyramidFaceOne->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceOne);

	osg::DrawElementsUInt* pyramidFaceTwo =
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceTwo->push_back(1);
	pyramidFaceTwo->push_back(2);
	pyramidFaceTwo->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceTwo);

	osg::DrawElementsUInt* pyramidFaceThree =
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceThree->push_back(2);
	pyramidFaceThree->push_back(3);
	pyramidFaceThree->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceThree);

	osg::DrawElementsUInt* pyramidFaceFour =
		new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	pyramidFaceFour->push_back(3);
	pyramidFaceFour->push_back(0);
	pyramidFaceFour->push_back(4);
	pyramidGeometry->addPrimitiveSet(pyramidFaceFour);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); //index 0 red
	colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f)); //index 1 green
	colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)); //index 2 blue
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //index 3 white 
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); //index 4 red

	pyramidGeometry->setColorArray(colors);
	pyramidGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	Viewer v;
	v.setSceneData(root);

	v.run();
}

