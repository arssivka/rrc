/**
 *  @autor arssivka
 *  @date 8/29/16
 */

#pragma once


#include <string>
#include <exception>

namespace rrc {
    class UnregisteredTypeException : public std::exception {
    public:
        UnregisteredTypeException();

        UnregisteredTypeException(const std::string& typeName);

        virtual ~UnregisteredTypeException() override;

        virtual const char* what() const override;

    private:
        std::string mErrorString;
    };
}


