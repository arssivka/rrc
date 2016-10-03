/**
 * @author arssivka
 * @date 9/30/16
 */

#pragma once


#include "AbstractMessageFilter.h"

namespace rrc {
    /**
     * @brief This message filter accepts message if it has right type id
     */
    class TypeIdMessageFilter : public AbstractMessageFilter {
    public:

        /**
         * @brief Constructor of TypeIdMessageFilter
         * @param typeId Needed type id for messages to accept. Will be UNKNOWN_TYPE_ID if not specifeid.
         */
        TypeIdMessageFilter(TypeId typeId = MetaTable::UNKNOWN_TYPE_ID);

        /**
         * @brief Virtual method for checking the message validity
         * @param message Pointer to message that needs to be checked
         * @return True if message accpeted, otherwise false.
         */
        virtual bool accept(MessagePtr message) override;

        /**
         * @brief Returns type id of the messages that this filter accepts
         * @return Type id
         */
        TypeId getTypeId() const;

        /**
         * @brief Sets type id of the messages that this filter needs to accept
         * @param typeId Needed type id
         */
        void setTypeId(TypeId typeId);

    private:
        TypeId mTypeId;
    };
}


