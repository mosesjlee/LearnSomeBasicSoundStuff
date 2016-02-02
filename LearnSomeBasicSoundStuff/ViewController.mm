//
//  ViewController.m
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 1/25/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.audioManager = [Novocaine audioManager];
    self.ringBuffer = new RingBuffer(32768, 2);
    self.playFlag = NO;
    self.playSine = NO;
    
    //Open a simple mono guitar file
    NSString * path = [[NSBundle mainBundle] pathForResource:  @"guitar1" ofType: @"wav"];
    self.monoGuitar = new WaveReader([path cStringUsingEncoding:1]);
    self.monoGuitar->fillSamples();
    
    //Set up the delay module
    self.delayModule = new DelayModule();
    
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (void)viewDidAppear{
    
    //Start filling buffer with this
    [self.audioManager setOutputBlock:^(float *data, UInt32 numFrames, UInt32 numChannels)
     {
         if(self.playSine){
             self.sineOsc->tick(data, numFrames, numChannels);
         } else {
//             self.monoGuitar->tick(data, numFrames, numChannels);
             self.monoGuitar->tick(self.delayModule->getInputBuffer(), MAX_SAMPLES, 1);
//             self.delayModule->fillInputBuffer(self.monoGuitar->getBuffer(), MAX_SAMPLES, );
             self.delayModule->processNextSamples();
             self.delayModule->tick(data, numFrames, numChannels);

         }
     }];
}


- (void)viewDidDisappear{
    if (self.playFlag){
        self.playFlag = NO;
        [self.audioManager pause];
    }
    
    if(self.sineOsc != nil){
        delete self.sineOsc;
    }
}

//Play or pause
- (IBAction)playPause:(id)sender {
    if(!self.playFlag) {
        [self.audioManager play];
        self.playFlag = YES;
        
#if DEBUG
        NSLog(@"playFlag is set to yes");
#endif
        
    } else {
        [self.audioManager pause];
        self.playFlag = NO;
#if DEBUG
        NSLog(@"playFlag is set to no");
#endif
    }
}

/*******************************************************************************
 
 Delay Controls
 
 *******************************************************************************/
- (IBAction)setTapTempo:(id)sender {
}

- (IBAction)updateDelayLength:(id)sender {
    self.delayModule->setDelayTime(self.delayLengthSlider.floatValue);
    self.delayLengthText.stringValue =
            [NSString stringWithFormat:@"%.2f", self.delayLengthSlider.floatValue];
}

- (IBAction)updateDelayLengthFromText:(id)sender {
}

- (IBAction)updateFeedbackGain:(id)sender {
    self.delayModule->setFeedbackGain(self.feedbackGainSlider.floatValue);
    self.feedbackGainText.stringValue =
            [NSString stringWithFormat:@"%.2f", self.feedbackGainSlider.floatValue];
}

- (IBAction)updateFeedbackGainFromText:(id)sender {
}

- (IBAction)updateWetGain:(id)sender {
    self.delayModule->setWetGain(self.wetGainSlider.floatValue);
    self.wetGainText.stringValue =
        [NSString stringWithFormat:@"%.2f", self.wetGainSlider.floatValue];
}

- (IBAction)updateWetGainFromText:(id)sender {
}

- (IBAction)updateDryGain:(id)sender {
    self.delayModule->setDryGain(self.dryGainSlider.floatValue);
    self.dryGainText.stringValue =
        [NSString stringWithFormat:@"%.2f", self.dryGainSlider.floatValue];
}

- (IBAction)updateDryGainFromText:(id)sender {
}

/*******************************************************************************
 
 Play Sine
 
 *******************************************************************************/
- (IBAction)playSineTone:(id)sender {
    if(self.sineOsc == nil) {
        self.sineOsc = new SineWaveOsc();
    }
    
    self.playSine = !self.playSine;
    
#if DEBUG
    NSLog(@"playSine: %d", self.playSine);
#endif
}

- (IBAction)changeFreq:(id)sender {
    if (self.sineOsc != nil){
        self.sineOsc->setFreq(self.sineFreqSlider.floatValue);
    }
    self.freqLabel.stringValue = [NSString stringWithFormat:@"%.2f", self.sineFreqSlider.floatValue];
}


@end
