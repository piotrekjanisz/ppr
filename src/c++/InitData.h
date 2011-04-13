/* 
 * File:   InitData.h
 * Author: piotrek
 *
 * Created on 28 listopad 2010, 19:10
 */

#ifndef INITDATA_H
#define	INITDATA_H

#include <eq/eq.h>

class InitData : public eq::net::Object
{
public:
    InitData();
    virtual ~InitData();

    virtual void getInstanceData(eq::net::DataOStream& os);
    virtual void applyInstanceData(eq::net::DataIStream& is);

    uint32_t getFrameDataId() const { return _frameDataId; }
    void setFrameDataId(uint32_t frameDataId) { _frameDataId = frameDataId; }

    std::string getHdfFile() { return _hdfFile; }
    void setHdfFile(const std::string& hdfFile) { _hdfFile = hdfFile; }

private:
    uint32_t _frameDataId;
    std::string _hdfFile;
};

#endif	/* INITDATA_H */

