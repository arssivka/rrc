/**
 *  @autor arssivka
 *  @date 8/25/16
 */

#include "include/rrc/MetaTable.h"


bool rrc::MetaTable::freeTypeId(rrc::TypeId typeId) {
    auto found1 = mReservedIds.find(typeId);
    if (found1 == mReservedIds.end()) {
        return false;
    }

    mReservedIds.erase(typeId);
    auto found2 = std::find_if(mTypeInfoHash.begin(), mTypeInfoHash.end(),
                             [typeId](const std::pair<std::type_index, TypeId>& pair) {
                                 return typeId == pair.second;
                             });
    mTypeInfoHash.erase(found2);
    return true;
}


bool rrc::MetaTable::isIdReserved(rrc::TypeId tid) {
    auto found = mReservedIds.find(tid);
    return found == mReservedIds.end();
}
