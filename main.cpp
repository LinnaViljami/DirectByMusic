#include <QApplication>
#include <FelgoApplication>
#include "RtAudio.h"
#include "pitchvariable.h"
#include "pitchdetector.h"
#include <QMutex>
#include <memory>

#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QMutex pitchVariableMutex;
    float pitchValue;
    std::unique_ptr<PitchVariable> detectorSharedPitchVariable = std::make_unique<PitchVariable>(&pitchVariableMutex, &pitchValue, 80.0, 240.0);
    std::unique_ptr<PitchVariable> applicationSharedPitchVariable = std::make_unique<PitchVariable>(&pitchVariableMutex, &pitchValue, 80.0, 240.0);
    std::unique_ptr<PitchDetector> pitchDetector = std::make_unique<PitchDetector>(detectorSharedPitchVariable.get());
    pitchDetector->initRealTimeAudioListener(1,44100,2048,1024);
    pitchDetector->startDetection();






    QApplication app(argc, argv);

    FelgoApplication felgo;

    // QQmlApplicationEngine is the preferred way to start qml projects since Qt 5.2
    // if you have older projects using Qt App wizards from previous QtCreator versions than 3.1, please change them to QQmlApplicationEngine
    QQmlApplicationEngine engine;
    felgo.initialize(&engine);

    // Set an optional license key from project file
    // This does not work if using Felgo Live, only for Felgo Cloud Builds and local builds
    felgo.setLicenseKey(PRODUCT_LICENSE_KEY);

    // use this during development
    // for PUBLISHING, use the entry point below
    felgo.setMainQmlFileName(QStringLiteral("qml/Main.qml"));

    // use this instead of the above call to avoid deployment of the qml files and compile them into the binary with qt's resource system qrc
    // this is the preferred deployment option for publishing games to the app stores, because then your qml files and js files are protected
    // to avoid deployment of your qml files and images, also comment the DEPLOYMENTFOLDERS command in the .pro file
    // also see the .pro file for more details
    // felgo.setMainQmlFileName(QStringLiteral("qrc:/qml/Main.qml"));

    engine.load(QUrl(felgo.mainQmlFileName()));

    int appResult = app.exec();
    pitchDetector->stopDetection();
    return appResult;

    }
