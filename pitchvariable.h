#ifndef PITCHVARIABLE_H
#define PITCHVARIABLE_H

#include <memory>
#include <QMutex>
#include <QObject>
#include <QtGlobal>

class PitchVariable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
    Q_PROPERTY(qreal min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(qreal max READ max WRITE setMax NOTIFY maxChanged)
public:
    PitchVariable(QMutex* pitchVariableMutex, float * pitchVariable, float min, float max);
    PitchVariable(PitchVariable& variable);
    qreal pitch();
    qreal max();
    qreal min();
    void setPitch(qreal newPitch);
    void setMax(qreal newMax);
    void setMin(qreal newMin);
signals:
    void pitchChanged();
    void minChanged();
    void maxChanged();
private:
    float * _pitchValue;
    QMutex * _pitchMutex;
    float _minPitchValue;
    float _maxPitchValue;

};

#endif // PITCHVARIABLE_H
