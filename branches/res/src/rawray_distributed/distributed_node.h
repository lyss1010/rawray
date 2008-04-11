/////////////////////////////////////////////////////////////////////////////
// Class : distributed_node.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_DISTRIBUTED_DISTRIBUTED_NODE_H
#define RAWRAY_RAWRAY_DISTRIBUTED_DISTRIBUTED_NODE_H
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
namespace rawray_distributed {
	
class DistributedNode {
public:
	DistributedNode(bool isServer);
	~DistributedNode();

	void Run();

private:
	bool isServer_;

	DISALLOW_IMPLICIT_CONSTRUCTORS(DistributedNode);
};

} // namespace rawray_distributed

#endif // RAWRAY_RAWRAY_DISTRIBUTED_DISTRIBUTED_NODE_H
