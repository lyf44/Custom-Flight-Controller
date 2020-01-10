#include "state_estimator.h"

/*
 * Defines
 */

#define DEFAULT_FILTER_FREQ 50 //hz

StateEstimator::StateEstimator() :
    mFilter()
{
    mState.att.roll = 0.0f;
    mState.att.yaw = 0.0f;
    mState.att.pitch = 0.0f;

    mFilter.begin(DEFAULT_FILTER_FREQ);
}

StateEstimator& StateEstimator::GetInstance()
{
    static StateEstimator stateEstimator;
    return stateEstimator;
}

bool StateEstimator::Init()
{
    return true;
}

bool StateEstimator::EstimateState(FCSensorMeasType& meas)
{
    mFilter.updateIMU(meas.gyroData.x, meas.gyroData.y, meas.gyroData.z,
                      meas.accData.x, meas.accData.y, meas.accData.z);
    mState.att.roll = mFilter.getRollRadians();
    mState.att.pitch = mFilter.getPitchRadians();
    mState.att.yaw = mFilter.getYawRadians();
    mState.attRate.roll = meas.gyroData.x;
    mState.attRate.pitch = meas.gyroData.y;
    mState.attRate.yaw = meas.gyroData.z;

    return true;
}