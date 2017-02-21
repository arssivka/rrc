/**
 *  @autor arssivka
 *  @date 2/20/17
 */

#pragma once


class flag_setter {
public:
    flag_setter(bool& _flag);

    void operator()();

private:
    bool& m_flag;
};