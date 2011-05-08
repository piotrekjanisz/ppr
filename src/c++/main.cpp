#include <eq/eq.h>
#include "GL/glew.h"
#include <stdlib.h>
#include "Channel.h"
#include "Config.h"
#include "Pipe.h"
#include "Node.h"
#include "CommandLineParser.h"

using namespace eq::base;
using namespace std;

class NodeFactory : public eq::NodeFactory
{
public:

    virtual eq::Channel* createChannel(eq::Window* parent)
    {
        return new Channel(parent);
    }

    virtual eq::Pipe* createPipe(eq::Node* parent)
    {
        return new Pipe(parent);
    }

    virtual eq::Config* createConfig(eq::ServerPtr parent)
    {
        return new Config(parent);
    }

    virtual eq::Node* createNode(eq::Config* parent)
    {
        return new Node(parent);
    }
};

const int DEF_SPHERE_NUM = 100000;

int main(const int argc, char** argv)
{
    glewExperimental = GL_TRUE;

    NodeFactory nodeFactory;
    if (!eq::init(argc, argv, &nodeFactory)) {
        EQERROR << "Equalizer init failed" << endl;
        return EXIT_FAILURE;
    }

    bool error = false;
    Config* config = static_cast<Config*> (eq::getConfig(argc, argv));
    if (config) {

    	CommandLineParser parser;
        const char* hdfFile = parser.findArg(argc, argv, "-hdfFile");
        if (hdfFile) {
        	cout << "HAVE HDF FILE: " << hdfFile << endl;
        	config->setHdfFileName(hdfFile);
        } else {
        	cout << "HDF FILE NOT SPECIFIED" << endl;
        	config->setHdfFileName("");
        }

        const char* sphereNumStr = parser.findArg(argc, argv, "-sphereNum");
        if (sphereNumStr) {
        	config->setSphereNum(atoi(sphereNumStr));
        } else {
        	config->setSphereNum(DEF_SPHERE_NUM);
        }

        if (config->init()) {
            while (config->isRunning()) {
                config->startFrame();
                config->finishFrame();
            }

            config->exit();
        } else {
            EQERROR << "Config initialization failed: "
                    << config->getErrorMessage() << endl;
            error = true;
        }

        eq::releaseConfig(config);
    } else {
        EQERROR << "Cannot get config" << endl;
        error = true;
    }

    eq::exit();
    return error ? EXIT_FAILURE : EXIT_SUCCESS;
}
