/**
 *  @autor tekatod
 *  @date 7/15/16
 */
#include <rrc/Property.h>

namespace rrc {
    template<>
    int Property::get<int>() const {
        int id = mField->which();
        switch (id) {
            case 0:
                return std::stoi(mField->get<std::string>());
            case 1:
                return (int) mField->get<float>();
            case 2:
                return (int) mField->get<bool>();
            case 3:
                return mField->get<int>();
            default:
                return 0;
        }

    }

    template<>
    float Property::get<float>() const {
        int id = mField->which();
        switch (id) {
            case 0:
                return std::stof(mField->get<std::string>());
            case 1:
                return mField->get<float>();
            case 2:
                return (float) mField->get<bool>();
            case 3:
                return (float) mField->get<int>();
            default:
                return 0.0;
        }
    }

    template<>
    bool Property::get<bool>() const {
        int id = mField->which();
        switch (id) {
            case 0:
                bool res;
                std::istringstream(mField->get<std::string>()) >> std::boolalpha >> res;
                return res;
            case 1:
                return (bool) mField->get<float>();
            case 2:
                return mField->get<bool>();
            case 3:
                return (bool) mField->get<int>();
            default:
                return false;
        }
    }

    template<>
    std::string Property::get<std::string>() const {
        int id = mField->which();
        switch (id) {
            case 0:
                return mField->get<std::string>();
            case 1:
                return std::to_string(mField->get<float>());
            case 2:
                return std::to_string(mField->get<bool>());
            case 3:
                return std::to_string(mField->get<int>());
            default:
                return std::string();
        }
    }

    int Property::getInt() {
        return this->get<int>();
    }

    float Property::getFloat() {
        return this->get<float>();
    }

    bool Property::getBool() {
        return this->get<bool>();
    }

    std::string Property::getString() {
        return this->get<std::string>();
    }
}