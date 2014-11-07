//
//  AudioScriptingInterface.h
//  libraries/audio/src
//
//  Created by Stephen Birarda on 1/2/2014.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_AudioScriptingInterface_h
#define hifi_AudioScriptingInterface_h

#include <qpointer.h>

#include "AbstractAudioInterface.h"
#include "AudioInjector.h"
#include "Sound.h"

const AudioInjectorOptions DEFAULT_INJECTOR_OPTIONS;

class AudioScriptingInterface : public QObject {
    Q_OBJECT
public:
    static AudioScriptingInterface& getInstance();
    
    void stopAllInjectors();
    
    void setLocalLoopbackInterface(AbstractAudioInterface* audioInterface) { _localLoopbackInterface = audioInterface; }
public slots:

    static float getLoudness(AudioInjector* injector);

    void playLocalSound(Sound *sound, const AudioInjectorOptions* injectorOptions = NULL);
    AudioInjector* playSound(Sound* sound, const AudioInjectorOptions* injectorOptions = NULL);
    
    void stopInjector(AudioInjector* injector);
    bool isInjectorPlaying(AudioInjector* injector);
    
    void injectorStopped();
    
private:
    AudioScriptingInterface();
    QList< QPointer<AudioInjector> > _activeInjectors;
    AbstractAudioInterface* _localLoopbackInterface;
};
#endif // hifi_AudioScriptingInterface_h
