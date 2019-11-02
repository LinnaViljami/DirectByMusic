#include "pitchvariable.h"
#include <math.h>
PitchVariable::PitchVariable(QMutex* pitchVariableMutex, float * pitchVariable, float min, float max) :  _pitchValue(pitchVariable), _pitchMutex(pitchVariableMutex)
  , _minPitchValue(min), _maxPitchValue(max)
{

}

PitchVariable::PitchVariable(PitchVariable &variable) : _pitchValue(variable._pitchValue), _pitchMutex(variable._pitchMutex)
  , _minPitchValue(variable._minPitchValue), _maxPitchValue(variable._maxPitchValue)
{



}

qreal PitchVariable::pitch()
{
    QMutexLocker locker(_pitchMutex);
    return static_cast<qreal>(*_pitchValue);

}

qreal PitchVariable::max()
{
    return static_cast<qreal>(_maxPitchValue);
}

qreal PitchVariable::min()
{
    return static_cast<qreal>(_minPitchValue);
}



void PitchVariable::setPitch(qreal newPitch)
{
    float epsilon = float(0.0001);
    float castedNew = static_cast<float>(newPitch);

    QMutexLocker locker(_pitchMutex);
    if(_minPitchValue < castedNew && _maxPitchValue > castedNew && fabs(castedNew - *_pitchValue) > epsilon){
        *_pitchValue = castedNew;
    }

}

void PitchVariable::setMax(qreal newMax)
{
    _maxPitchValue = static_cast<float>(newMax);
}

void PitchVariable::setMin(qreal newMin)
{
    _minPitchValue = static_cast<float>(newMin);
}

