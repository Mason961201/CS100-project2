#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other) {
     if ( count > other.count ){
	return true;
     }
     else if( count < other.count ){
	return false;
     }
     else{
	return symbol > other.symbol;
     }
     // TODO (checkpoint)
}
