/////////////////////////////////////////////////////////////////////////////
// Project Options : stats.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_STATS_H
#define RAWRAY_RAWRAY_STATS_H

namespace rawray {
namespace stats {

extern uint64 triangleIntersections;
extern uint64 boxIntersections;
extern uint64 primaryRays;
extern uint64 shadowRays;
extern uint64 bvhLeaves;
extern uint64 bvhSplits;


} // namespace rawray::stats
} // namespace rawray

#endif // RAWRAY_RAWRAY_STATS_H
