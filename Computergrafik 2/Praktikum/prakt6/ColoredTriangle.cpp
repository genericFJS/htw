
#include <osg/Group >
#include <osgViewer/Viewer >
#include <osgDB/WriteFile>
#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>

USE_GRAPHICSWINDOW()

// scene definition
osg::ref_ptr < osg::Node > createTriangle() {

	// node which stores the geometry
	osg::ref_ptr < osg::Geometry > geo = new osg::Geometry;

	// array of vertices
	osg::ref_ptr < osg::Vec3Array > v = new osg::Vec3Array;
	geo->setVertexArray(v.get());
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

	// array of colors
	osg::ref_ptr < osg::Vec4Array > c = new osg::Vec4Array;
	geo->setColorArray(c.get());
	geo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	c->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	c->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));

	// array of normals
	osg::ref_ptr < osg::Vec3Array > n = new osg::Vec3Array;
	geo->setNormalArray(n.get());
	geo->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	// set face
	geo->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));

	// attach the drawable to a geode node
	osg::ref_ptr < osg::Geode > geode = new osg::Geode;
	geode->addDrawable(geo.get());
	return geode.get();
}

osg::ref_ptr <osg::Node> addPlane() {
	osg::ref_ptr <osg::Geometry> geo = new osg::Geometry;
	float size = 500.0f;
	float z = 20.0f;

	// array of vertices
	osg::ref_ptr <osg::Vec3Array> v = new osg::Vec3Array;
	geo->setVertexArray(v.get());
	v->push_back(osg::Vec3(size / 2, z, -size / 2));
	v->push_back(osg::Vec3(size / 2, z, size / 2));
	v->push_back(osg::Vec3(-size / 2, z, -size / 2));
	v->push_back(osg::Vec3(-size / 2, z, size / 2));

	// array of colors
	osg::ref_ptr < osg::Vec4Array > c = new osg::Vec4Array;
	geo->setColorArray(c.get());
	geo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));

	// array of normals
	osg::ref_ptr < osg::Vec3Array > n = new osg::Vec3Array;
	geo->setNormalArray(n.get());
	geo->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	// set face
	geo->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));
	geo->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 1, 3));

	// attach the drawable to a geode node
	osg::ref_ptr < osg::Geode > geode = new osg::Geode;
	geode->addDrawable(geo.get());
	return geode.get();
}

osg::ref_ptr <osg::Node> addStick() {
	osg::ref_ptr<osg::Geode> cylGeode(new osg::Geode);
	osg::ref_ptr<osg::ShapeDrawable> cylShapeDrawable(new osg::ShapeDrawable);
	cylShapeDrawable = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(-1, 2, -55), 2, 100));
	cylShapeDrawable->setColor(osg::Vec4f(1.0f, 0.0f, 1.0f, 1.0f));
	cylGeode->addDrawable(cylShapeDrawable);
	return cylGeode.get();
}

// main program
int main(int argc, char * argv[]) {

	// create an empty root node
	osg::ref_ptr <osg::Group > root = new osg::Group;

	// add the geode to the root node
	//root->addChild(createTriangle());
	// AUFGABE 3+4
	root->addChild(addPlane());
	root->addChild(addStick());

	// AUFGABE 2
	osgDB::writeNodeFile(*root, "export.osg");

	// AUFGABE 5
	osg::Node* logo = osgDB::readNodeFile("fjs.obj");
	root->addChild(logo);

	// create a viewer object to display the scene
	osgViewer::Viewer viewer;

	// attach the scenegraph to the viewer and the window
	viewer.setSceneData(root.get());
	viewer.setUpViewInWindow(20, 20, 800, 600);

	// start the loop which displays the viewer
	return viewer.run();
}