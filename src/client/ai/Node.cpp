#include <ai/Node.h>  // Included from library shared_static
#include "Node.h"
#include <iostream>


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

    void ai::Node::SetIndex (int rNodeIndex){
        mNodeIndex = rNodeIndex;
    }

    state::State* ai::Node::GetGameContext(){
        return &this->mGameContext;
    }

    int ai::Node::GetNodeValue(){
        return mNodeValue;
    }

/**
 * @brief Return the number of child of the parent 
 * 
 * @return int Number of child
 */
    int ai::Node::GetChildNumber(){
       return mNodeJunction.size();
    }


/**
 * @brief Delete all child 
 * 
 */
    void ai::Node::KillChild(){
        int lOrigin_mNodeJunction_Size = mNodeJunction.size();
        if(mNodeJunction.size() != 0){  
            /*If we reach max depth of tree, no child to kill*/
        

            for(int i=0;i<lOrigin_mNodeJunction_Size;i++){
                mNodeJunction[i]->KillChild();
                mNodeJunction.erase(mNodeJunction.begin());

            }
        
        }



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