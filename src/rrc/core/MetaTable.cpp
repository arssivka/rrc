/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#include <rrc/core/MetaTable.h>


const rrc::TypeId rrc::MetaTable::UNKNOWN_TYPE_ID = std::numeric_limits<rrc::TypeId>::max();


bool rrc::MetaTable::freeTypeId(rrc::TypeId typeId) {
    auto found1 = mMessageFactoryHash.find(typeId);
    if (found1 == mMessageFactoryHash.end()) {
        return false;
    }

    mMessageFactoryHash.erase(typeId);
    auto found2 = std::find_if(mTypeInfoHash.begin(), mTypeInfoHash.end(),
                             [typeId](const std::pair<std::type_index, TypeId>& pair) {
                                 return typeId == pair.second;
                             });
    mTypeInfoHash.erase(found2);
    return true;
}


bool rrc::MetaTable::isIdReserved(rrc::TypeId tid) {
    auto found = mMessageFactoryHash.find(tid);
    return found != mMessageFactoryHash.end();
}


rrc::MessageFactoryPtr rrc::MetaTable::getMessageFactory(rrc::TypeId typeId) {
    auto found = mMessageFactoryHash.find(typeId);
    return (found != mMessageFactoryHash.end())
           ? found->second
           : nullptr;
}
