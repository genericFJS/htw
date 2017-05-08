#include <osgDB\ReadFile>
#include <osgViewer\Viewer>

using namespace std;
using namespace osgViewer;
using namespace osgDB;

int main(void)
{
	Viewer v;
	v.setSceneData(readNodeFile("C:\\temp\\cessna.osg"));
	return v.run();
}

