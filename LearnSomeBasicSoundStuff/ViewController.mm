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
    NSString * path = [[NSBundle mainBundle] pathForResource:  @"electricguitar" ofType: @"wav"];
    self.monoGuitar = new WaveReader([path cStringUsingEncoding:1]);
    self.monoGuitar->fillSamples();
    
    //Set up the delay module
    self.delayModule = new DelayModule();
    
    //Set up the distortion
    self.simpleDist = new SimpleDistortion();
    
    //Set up the flanger
    self.flangerModule = new FlangerModule();
    
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (void)viewDidAppear{
    __weak ViewController * wself = self;
    //If I want to start experimenting with my own live input
    [self.audioManager setInputBlock:^(float *data, UInt32 numFrames, UInt32 numChannels) {
        
    }];
    
    //Start filling buffer with this
    [self.audioManager setOutputBlock:^(float *data, UInt32 numFrames, UInt32 numChannels)
     {
         if(wself.playSine){
             wself.sineOsc->tick(data, numFrames, numChannels);
         } else {
             //For delay
//             self.monoGuitar->tick(self.delayModule->getInputBuffer(), MAX_SAMPLES, 1);
//             self.delayModule->processNextSamples();
//             self.delayModule->tick(data, numFrames, numChannels);
             //For simple distortion
//             wself.monoGuitar->tick(wself.simpleDist->getInputBuffer(), MAX_SAMPLES, 1);
//             wself.simpleDist->processNextSamples();
//             wself.simpleDist->fillOutputBuffer(data, numFrames, numChannels);
             //For tremolo
            wself.monoGuitar->tick(wself.flangerModule->getInputBuffer(), MAX_SAMPLES, 1);
            wself.flangerModule->processNextSamples();
            wself.flangerModule->fillOutputBuffer(data, numFrames, numChannels);
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
    [self.delayLengthSlider setFloatValue:self.delayLengthText.floatValue];
    self.delayModule->setDelayTime(self.delayLengthSlider.floatValue);
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
 
 Simple Distortion
 
 *******************************************************************************/
- (IBAction)setGainLevel:(id)sender {
    self.simpleDist->setNewDrive(self.gainLevelSlider.floatValue);
    self.gainLevelTextField.stringValue =
        [NSString stringWithFormat:@"%.2f", self.gainLevelSlider.floatValue];
}

- (IBAction)setGainLevelFromText:(id)sender {
}

/*******************************************************************************
 
Simple Flanger
 
 *******************************************************************************/

- (IBAction)setNewMinDelay:(id)sender {
    self.flangerModule->setMinDelay(self.minDelaySlider.floatValue);
    self.minDelayTextField.stringValue =
        [NSString stringWithFormat:@"%.2f", self.minDelaySlider.floatValue];
}

- (IBAction)setNewDelayRate:(id)sender {
    self.flangerModule->setDelayRate(self.delayRateSlider.floatValue);
    self.delayRateTextField.stringValue =
        [NSString stringWithFormat:@"%.2f", self.delayRateSlider.floatValue];
}

- (IBAction)setNewDelayDepth:(id)sender {
    self.flangerModule->setDelayDepth(self.delayDepthSlider.floatValue);
    self.delayDepthTextField.stringValue =
        [NSString stringWithFormat:@"%.2f", self.delayDepthSlider.floatValue];
}

- (IBAction)setFlangerNewDryGain:(id)sender {
    self.flangerModule->setDryGain(self.flangerDryGainSlider.floatValue);
    self.flangerDryGainTextField.stringValue =
        [NSString stringWithFormat:@"%.2f", self.flangerDryGainSlider.floatValue];
}

- (IBAction)setFlangerNewWetGain:(id)sender {
    self.flangerModule->setWetGain(self.flangerWetGainSlider.floatValue);
    self.flangerWetGainTextField.stringValue =
        [NSString stringWithFormat:@"%.2f", self.flangerWetGainSlider.floatValue];
}

- (IBAction)setFlangerNewFeedbackGain:(id)sender {
    self.flangerModule->setFeedbackGain(self.flangerFeedbackGainSlider.floatValue);
    self.flangerFeedbackGainTextField.stringValue =
        [NSString stringWithFormat:@"%.2f", self.flangerFeedbackGainSlider.floatValue];
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
