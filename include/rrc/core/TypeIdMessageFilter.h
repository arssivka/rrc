/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "AbstractMessageFilter.h"

namespace rrc {
    class TypeIdMessageFilter : public AbstractMessageFilter {
    public:
        TypeIdMessageFilter(TypeId typeId = MetaTable::UNKNOWN_TYPE_ID);

        virtual bool accept(MessagePtr message) override;

        TypeId getTypeId() const;

        void setTypeId(TypeId typeId);

    private:
        TypeId mTypeId;
    };
}


