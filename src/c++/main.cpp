#include <eq/eq.h>
#include "GL/glew.h"
#include <stdlib.h>
#include "Channel.h"
#include "Config.h"
#include "Pipe.h"
#include "Node.h"

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

int main(const int argc, char** argv)
{
    // Init GLEW
    glewExperimental = GL_TRUE;

    // 1. Equalizer initialization
    NodeFactory nodeFactory;
    if (!eq::init(argc, argv, &nodeFactory)) {
        EQERROR << "Equalizer init failed" << endl;
        return EXIT_FAILURE;
    }

    // 2. get a configuration
    bool error = false;
    Config* config = static_cast<Config*> (eq::getConfig(argc, argv));
    if (config) {
        // 3. init config
        if (config->init()) {
            // 4. run main loop
            while (config->isRunning()) {
                config->startFrame();
                config->finishFrame();
                //const eq::ConfigEvent* event = config->nextEvent();
                //config->handleEvents();
                //if (event) {
                //    config->handleEvent(event);
                //}
            }

            // 5. exit config
            config->exit();
        } else {
            EQERROR << "Config initialization failed: "
                    << config->getErrorMessage() << endl;
            error = true;
        }

        // 6. release config
        eq::releaseConfig(config);
    } else {
        EQERROR << "Cannot get config" << endl;
        error = true;
    }

    // 7. exit
    eq::exit();
    return error ? EXIT_FAILURE : EXIT_SUCCESS;
}
