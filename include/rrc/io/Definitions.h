/**
 *  @autor nikitas
 *  @date 10/12/16
 */
#pragma once

namespace rrc {

    enum Mode {
        Read        =   0x01,
        Write       =   0x02,
        ReadWrite   =   Read | Write
    };

    enum Console {
        Input,
        Ouput,
        Error
    };

}
