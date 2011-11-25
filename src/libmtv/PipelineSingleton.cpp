#include "libmtv_global.h"
#include "Pipeline.h"

extern "C" {
    LIBMTV_EXPORT mtv::Pipeline *singletonPipelineInstance = 0x0;


    LIBMTV_EXPORT mtv::Pipeline *Pipeline() {
        if(singletonPipelineInstance = 0x0) {
            singletonPipelineInstance = new mtv::Pipeline();
        }
        return singletonPipelineInstance;
    }
}
