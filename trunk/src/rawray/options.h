/////////////////////////////////////////////////////////////////////////////
// Project Options : options.h
//
/////////////////////////////////////////////////////////////////////////////
#ifndef RAWRAY_RAWRAY_OPTIONS_H
#define RAWRAY_RAWRAY_OPTIONS_H

namespace rawray {
namespace options {

    enum TriangleIntersection {
        BARYCENTRIC,
        PLUCKER,
        MOLLER,
    };

    extern TriangleIntersection triangle_intersection_algorithm;

} // namespace rawray::options
} // namespace rawray

#endif // RAWRAY_RAWRAY_OPTIONS_H
