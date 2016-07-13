/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <memory>
#include <vector>
#include "ID.h"
#include "NonCopyable.h"

namespace rrc {
    class Node : private NonCopyable {
    public:
        typedef std::unique_ptr<Node> Ptr;

        template <class NodeType, class Args...>
        static Node::Ptr create(const std::string& name, Args... args) {
            return Node::Ptr(new NodeType(name, std::forward<Args>(args)...));
        }

        void attachNode(Node::Ptr node);

        Node::Ptr detachNode(Node* node);

        Node* findChild(const std::string& name) const;

        Node* findChild(const ID& id) const;

        const ID& getID() const;

        Node* getParent() const;

        const std::vector<Ptr>& getChildren() const;

    protected:
        Node(const std::string& name);

    private:
        const ID mID;
        Node* mParent;
        std::vector<Node::Ptr> mChildren;
    };
}


