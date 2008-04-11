/////////////////////////////////////////////////////////////////////////////
// distributed_node.cpp
//
/////////////////////////////////////////////////////////////////////////////
#include "distributed_node.h"

namespace rawray_distributed {

DistributedNode::DistributedNode(bool isServer) : isServer_(isServer) { }
DistributedNode::~DistribtuedNode() { }

DistributedNode::Run() { 
	if( isServer_ ) {
		std::cout << "Running server" << std::endl;


	} else {
		std::cout << "Running client" << std::endl;


	}
}

} // namespace rawray_distributed
