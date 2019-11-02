#include "pitchdetector.h"
#include <exception>
#include "customexception.h"
#include "source/libpyincpp.h"
#include <QMutexLocker>
#include <functional>

int HandlePitchAnalyzeResult(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

struct PitchAnalyzeData
{
    PitchVariable * pitchVariable;
    unsigned int samplerate;
    unsigned int blocksize;
    PitchAnalyzeData(PitchVariable * variable) : pitchVariable(variable) {}
    PitchAnalyzeData(PitchAnalyzeData& data) : pitchVariable(data.pitchVariable), samplerate(data.samplerate), blocksize(data.blocksize){}
};


PitchDetector::PitchDetector(PitchVariable* pitchVariable) : _pitchVariable(pitchVariable)
{
    _audioListener = nullptr;
    _isInitialized = false;

}


void PitchDetector::initRealTimeAudioListener(unsigned int nChannels, unsigned int sampleRate, unsigned int bufferSize, unsigned int blockSize)
{
    //init audio listener
    this->_audioListener = std::make_unique<RtAudio>();
    if ( this->_audioListener->getDeviceCount() < 1 ) {
        throw CustomException("Pitch detector unable to use device microphone");
    }
    else {
        //init stream parameters
        RtAudio::StreamParameters parameters;
        parameters.deviceId = this->_audioListener->getDefaultInputDevice();
        parameters.nChannels = nChannels;
        parameters.firstChannel = 0;
        _streamParameters = parameters;

        _sampleRate = sampleRate;
        _blockSize = blockSize;
        _bufferSize = bufferSize;
        _isInitialized = true;
    }
}


RtAudioCallback PitchDetector::getBufferDataHandler()
{

    return HandlePitchAnalyzeResult;

}

void PitchDetector::startDetection()
{
    if(!_isInitialized){
        throw CustomException("PitchDetector init function must called before start detection");
    }
    else {
        PitchAnalyzeData * analyzeData = new PitchAnalyzeData(this->_pitchVariable);
        analyzeData->blocksize = this->_blockSize;
        analyzeData->samplerate = this->_sampleRate;
        this->_audioListener->openStream( nullptr, &this->_streamParameters, RTAUDIO_FLOAT32, this->_sampleRate, &this->_bufferSize,
                                      this->getBufferDataHandler(), analyzeData);
        this->_audioListener->startStream();
    }

}

void PitchDetector::stopDetection()
{
    if ( _audioListener->isStreamOpen() ) _audioListener->closeStream();

}


int HandlePitchAnalyzeResult(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData){
    (void) outputBuffer;
    (void) streamTime;
    if ( status )
        throw CustomException("Stream overflow detected!");
    else {
        // open user params
        PitchAnalyzeData * analyzeData = static_cast<PitchAnalyzeData * >(userData);

        //copy buffer to vector
        float * inputBegin = static_cast<float *>(inputBuffer);
        int lenght = static_cast<int>(nBufferFrames);
        std::vector<float> samples(inputBegin, inputBegin+lenght);

        //analyze pitch with Pyin algorithm
        //init pyin analyzator
        const int sampleRate = static_cast<int>(analyzeData->samplerate);
        const int blockSize = static_cast<int>(analyzeData->blocksize);
        const int stepSize = blockSize;
        PyinCpp my_pyin(sampleRate, blockSize, stepSize);
        //make analyze
        std::vector<float> pitches = my_pyin.feed(samples);
        //update shared variable
        analyzeData->pitchVariable->setPitch(static_cast<qreal>(pitches.front()));
        return 0;
    }
}
