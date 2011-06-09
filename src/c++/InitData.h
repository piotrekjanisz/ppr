/* 
 * File:   InitData.h
 * Author: piotrek
 *
 * Created on 28 listopad 2010, 19:10
 */

#ifndef INITDATA_H
#define	INITDATA_H

#include <eq/eq.h>

class InitData : public co::Object
{
public:
    InitData();
    virtual ~InitData();

    virtual void getInstanceData(co::DataOStream& os);
    virtual void applyInstanceData(co::DataIStream& is);

    eq::uint128_t getFrameDataId() const { return _frameDataId; }
    void setFrameDataId(const eq::uint128_t& frameDataId) { _frameDataId = frameDataId; }

    std::string getHdfFile() { return _hdfFile; }
    void setHdfFile(const std::string& hdfFile) { _hdfFile = hdfFile; }

    uint32_t getSphereNum() const { return _sphereNum; }
    void setSphereNum(uint32_t sphereNum) { _sphereNum = sphereNum; }

private:
    eq::uint128_t _frameDataId;
    std::string _hdfFile;
    uint32_t _sphereNum;
};

#endif	/* INITDATA_H */

