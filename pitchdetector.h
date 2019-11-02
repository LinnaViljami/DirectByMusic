#ifndef PITCHDETECTOR_H
#define PITCHDETECTOR_H

#include <QMutex>
#include <memory>
#include "RtAudio.h"
#include "pitchvariable.h"


class PitchDetector
{
public:
    PitchDetector(PitchVariable* pitchVariable);

    void startDetection();
    void stopDetection();
    void initRealTimeAudioListener(unsigned int nChannels, unsigned int sampleRate, unsigned int bufferSize, unsigned int blockSize);
private:
    PitchVariable * _pitchVariable;
    std::shared_ptr<RtAudio> _audioListener;
    RtAudio::StreamParameters _streamParameters;
    bool _isInitialized;
    unsigned int _sampleRate;
    unsigned int _blockSize;
    unsigned int _bufferSize;
    RtAudioCallback getBufferDataHandler();

};

#endif // PITCHDETECTOR_H
