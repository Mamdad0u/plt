#include <ai/Node.h>  // Included from library shared_static
#include "Node.h"



namespace ai {
    ai::Node::Node(){
        
    }
    ai::Node::Node(state::State& rGameContext, int rNodeValue){
        this->mGameContext = rGameContext;
        mNodeValue = rNodeValue;
        mNodeJunction.reserve(4);
    }

    void ai::Node::AddBranch(Node* rNewNodeBranch){
        mNodeJunction.push_back(rNewNodeBranch);
    }

    Node* ai::Node::GetBranch(int rNodeBranch){
        return this->mNodeJunction[rNodeBranch];
    }

    void ai::Node::SetIndex (int rNodeIndex){
        mNodeIndex = rNodeIndex;
    }

    state::State* ai::Node::GetGameContext(){
        return &this->mGameContext;
    }

                /*** DEPRECATED ***/
/*     void ai::Node::AddBranch(Node* rNewNodeBranch){
        std::unique_ptr<Node> lNewNodeBranch(rNewNodeBranch);
        
        mNodeJunction.push_back(std::move(lNewNodeBranch));
    } */

/*     Node* ai::Node::GetBranch(int rNodeBranch){
        return this->mNodeJunction[rNodeBranch].get();


    } */


}