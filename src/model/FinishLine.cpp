#include "FinishLine.h"

FinishLine::FinishLine(Coordinate begin, Coordinate end, b2World& track, Orientation orientation):
    cross_first(false),
    cross_second(false),
    f_finish_line(begin, end, orientation,cross_first, cross_second, track),
    s_finish_line(begin, end, orientation, cross_first, cross_second, track)
{}
