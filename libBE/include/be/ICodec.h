#ifndef ICODEC
#define ICODEC

#include "be/IEncoder.h"
#include "be/IDecoder.h"
#include "be/Global.h"

namespace be{

class BE_SHARED_EXPORT ICodec : public IEncoder, public IDecoder{
public:
    virtual ~ICodec(){
    }
};

} // be
#endif // ICODEC

