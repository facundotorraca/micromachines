#include "FinishLine.h"
#include "RacingTrack.h"
#include <common/Sizes.h>
#include <common/EntityType.h>
#include <model/Vehicle/Car.h>

FinishLine::FinishLine(Coordinate begin, Coordinate end, b2World& track):
    cross_first(false),
    cross_second(false),
    f_finish_line(begin, end, cross_first, cross_second, track),
    s_finish_line(begin, end, cross_first, cross_second, track)
{}
