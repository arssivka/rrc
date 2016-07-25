/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <memory>
#include <vector>
#include "ID.h"
#include "NonCopyable.h"
#include "TSQueue.h"
#include "Subscriber.h"
#include "Pipe.h"
#include "TaskQueue.h"
#include "Core.h"

namespace rrc {
    class Node : private NonCopyable {
    public:
        typedef std::unique_ptr<Node> UPtr;

        template <class NodeType, class... Args>
        static std::unique_ptr<NodeType> create(const std::string& name, Args... args) {
            return std::make_unique<NodeType>(name, std::forward<Args>(args)...);
        }

        void attachNode(Node::UPtr node);

        Node::UPtr detachNode(Node* node);

        Node* findChild(const std::string& name) const;

        Node* findChild(const ID& id) const;

        const ID& getID() const;

        Node* getParent() const;

        const std::vector<UPtr>& getChildren() const;

        virtual ~Node() {
            auto core = Core::instance();
            core->detachEntryForID(mID);
        }

    protected:
        Node(const std::string& name);

        virtual void entry();

        void pollEvent();

        void pollEvents();

//        Subscriber createSubscriber(const std::string& topic);

//        Pipe createPipe(const std::string& topic);


    private:
        const ID mID;
        Node* mParent;
        std::vector<Node::UPtr> mChildren;
        TaskQueue::SPtr mTaskQueue;
    };
}


