//
//  ViewController.h
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 1/25/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Novocaine.h"
#import "RingBuffer.h"
#import "AudioFileWriter.h"
#import "AudioFileReader.h"
#import "MySoundStuff.h"



@interface ViewController : NSViewController
@property (strong) IBOutlet NSView *selectTab;
@property (strong) IBOutlet NSButton *playPauseButton;

//Sine oscillator UI elements
@property (strong) IBOutlet NSSlider *sineFreqSlider;
@property (strong) IBOutlet NSTextField *freqLabel;

//Delay UI elements
@property (strong) IBOutlet NSButton *tapTempoButton;
@property (strong) IBOutlet NSTextField *delayLengthText;
@property (strong) IBOutlet NSSlider *delayLengthSlider;
@property (strong) IBOutlet NSTextField *feedbackGainText;
@property (strong) IBOutlet NSSlider *feedbackGainSlider;
@property (strong) IBOutlet NSTextField *wetGainText;
@property (strong) IBOutlet NSSlider *wetGainSlider;
@property (strong) IBOutlet NSTextField *dryGainText;
@property (strong) IBOutlet NSSlider *dryGainSlider;

//Distortion UI Elements
@property (strong) IBOutlet NSSliderCell *gainLevelSlider;
@property (strong) IBOutlet NSTextFieldCell *gainLevelTextField;

//My Flags
@property (nonatomic) BOOL playFlag;
@property (nonatomic) BOOL playSine;

//Novocaine stuff
@property (nonatomic, strong) Novocaine *audioManager;
@property (nonatomic, strong) AudioFileReader *fileReader;
@property (nonatomic, strong) AudioFileWriter *fileWriter;
@property (nonatomic, assign) RingBuffer * ringBuffer;

//MySoundStuff
@property (nonatomic) SineWaveOsc * sineOsc;
@property (nonatomic) WaveReader * monoGuitar;
@property (nonatomic) DelayModule * delayModule;
@property (nonatomic) SimpleDistortion * simpleDist;

@end

