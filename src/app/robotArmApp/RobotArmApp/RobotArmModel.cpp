#include "RobotArmApp.h"
#include "pa_CommonLib/src/util/pa_Math/pa_Math.h"
RobotArmModel::RobotArmModel()
{
}

void RobotArmModel::recalcVeticalPlane(float x, float y)
{
    float cos_theata2plus3 = cosf(theata3 + theata2);
    float sin_theata2plus3 = sqrtf(1 - cos_theata2plus3);
    float l3 = sqrt(l2 * l2 + l1 * l1 - 2 * cos_theata2plus3 * l1 * l2);
    float theata4 = asinf(sin_theata2plus3 * l2 / l3);
}

void RobotArmModel::initDatas()
{
    l2 = sqrtf(l2_y * l2_y + l2_x + l2_x);
    theata3 = atan2f(l2_x, l2_y);
}
