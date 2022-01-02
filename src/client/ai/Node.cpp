#include <ai/Node.h>  // Included from library shared_static
#include "Node.h"



namespace ai {

    ai::Node::Node(state::State& rGameContext, int rNodeValue){
        this->mGameContext = rGameContext;
        mValue = rNodeValue;
        mNodeJunction.reserve(4);
    }

    void ai::Node::AddBranch(Node* rNewNodeBranch){
        std::unique_ptr<Node> lNewNodeBranch(rNewNodeBranch);
        mNodeJunction.push_back(std::move(lNewNodeBranch));
    }
    void ai::Node::SetNodeValue(int rNodeValue){
        mValue = rNodeValue;
    }



}