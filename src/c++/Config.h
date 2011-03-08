/* 
 * File:   Config.h
 * Author: piotrek
 *
 * Created on 28 listopad 2010, 17:04
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <eq/eq.h>
#include "FrameData.h"
#include "CameraFrame.h"
#include "InitData.h"

class Config : public eq::Config
{
public:

    virtual bool init();
    virtual uint32_t startFrame();
    virtual bool handleEvent(const eq::ConfigEvent* event);

    const InitData& getInitData() const
    {
        return _initData;
    }

    void mapData(const uint32_t initDataID);

    Config(eq::base::RefPtr< eq::Server > parent);
    virtual ~Config();
private:
    FrameData _frameData;
    CameraFrame _cameraFrame;
    InitData _initData;
    bool handleKeyEvent(const eq::KeyEvent& event);
};

#endif	/* CONFIG_H */

