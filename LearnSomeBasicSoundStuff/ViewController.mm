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
    self.audioManager = [Novocaine audioManager];
    self.ringBuffer = new RingBuffer(32768, 2);
    self.playFlag = NO;
    self.playSine = NO;
    
    //Open a simple mono guitar file
    NSString * path = [[NSBundle mainBundle] pathForResource:  @"guitar1" ofType: @"wav"];
    self.monoGuitar = new WaveReader([path cStringUsingEncoding:1]);
    self.monoGuitar->fillSamples();
    // Do any additional setup after loading the view.
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
             self.monoGuitar->tick(data, numFrames, numChannels);
             //Zero fill this
//             for (int i = 0; i < numFrames; i++){
//                 for (int j = 0; j < numChannels; j++){
//                     data[i * numChannels + j] = 0;
//                 }
//             }
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

//Delay Stuff
- (IBAction)setTapTempo:(id)sender {
}

//Play Sine
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
