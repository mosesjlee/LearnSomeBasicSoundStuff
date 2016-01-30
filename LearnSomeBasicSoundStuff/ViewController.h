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
@property (strong) IBOutlet NSSlider *sineFreqSlider;
@property (strong) IBOutlet NSTextField *freqLabel;

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

@end

