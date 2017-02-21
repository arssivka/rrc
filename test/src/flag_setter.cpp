/**
 *  @autor arssivka
 *  @date 2/20/17
 */

#include <flag_setter.h>


flag_setter::flag_setter(bool& _flag)
        : m_flag(_flag) {
    m_flag = false;
}


void flag_setter::operator()() {
    m_flag = true;
}
