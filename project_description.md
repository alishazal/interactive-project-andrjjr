## Gestural Light Controller for DJs/Electronic Music Performers

My idea for this project came from my experiences in electronic music performance, and the desire to offer a degree of visual control to musical performers/DJs in performance contexts where lighting technicians and designers may not be available, or in the case where a performer wants to have more specific control over some parameters of light and visual elements of a performance. I thought about designing a system, that allows a performer who is primarily wokring with faders and knobs, to have quick access control to some pre-programmed visual elements. I wanted to prototpye a system that allows the performer quick access controls, without taking their attention too far away from the musical performance, as this is their primary directive. 

What I decided to create was a system that lets the performer/DJ use one hand, to trigger or instantiate certain setting presets in a lu
lighting system. In this proof-of-concept, I used my own simple lighting system, a NeoPixel LED strip, but I imagine that this could be inetrfaced with a lighting console, and have the performer send out DMX values. The idea was to develop an open-ended system in terms of what inputs are mapped to what outputs. The input options are given by me, but the output can really be mapped to whatever the performer needs / can code. To that end, this could be a multi-purpose gestural performance tool.

### The Technology

Since I would be working with gestures, I needed an input device that can help me identify these. A normal video input could work, but since this device would be used in very different environments, in low light conditions, and in spaces with rapidly changing visible light, it made sense to go for a non-visible light camera, so an IR camera. The two options were the Kinekt and Leap Motion. I had worked with Kinekt before and foudn it more sueful for larger-scale applications, so I chose the Leap Motion instead. 

For my output, I used a NeoPixel LED strip. This allowed me quickly build a working demo. 

Leap-motion:
![leap-motion](https://github.com/artintelclass/interactive-project-andrjjr/blob/master/leap-motion.JPG)

Neo-pixels
![neo-pixels](https://github.com/artintelclass/interactive-project-andrjjr/blob/master/neopixel.JPG)

Arduino
![arduino](https://github.com/artintelclass/interactive-project-andrjjr/blob/master/ardiuno.JPG)

### Inputs + machine learning models

The Leap Motion works with a pre-made processing library, [nok-leap-motion-processing](https://github.com/nok/leap-motion-processing). The class Wekinator examples are built on top of this library. This outputs 15 data points, the x, y, and z values of each finger-tip. I planned to use this data in three ways:
  1. To track specific **finger combinations**.
  2. To determine the **proximity of the user's hand** to the Leap
  3. A few **gestures** (swipe left, and swipe right). 

I managed to succesfully get this data into Wekinator (via the Wekinator helpers in some cases) for each of the desired inputs, and to a different machine learning program. For finger combinations I used a classifier, with **k-nearest neighbour** (tests with the other methods didn't give much different results). The proximity used **continuous input**, with an avergaing function in the weki input helper. Lastly, the gesture worked with a **dynamic time warping model**. With the gestures, I tried to filter the input data in the weki-input helper, by selecting only the x-positions of the fingertips, and then also outputting their acceleration, in the hopes that it would help better distinguish the directions of the swipes. This howeverm significantly worsened my learning model, so I resorted to the unfiltered data. Although I managed to train all these inputs successfully in Wekinator, for this demonstration I only used the finger combinations due to limitations imposed by the serial routing of the output (discussed below).

### Output routing

![ideal vs final image](https://github.com/artintelclass/interactive-project-andrjjr/blob/master/IMG_5941.JPG)

My initial idea was to route the outputs from Wekinator, via OSC directly to my Arduino using the OSCuino library. I wanted to do this becasue then I would avoid difficulties between timing conflicts in serial transmission, and and rate of operation of my light flashing functions in Arduino. However, I did not have access to an Ethernet shield and after a few failed attempts (Wifi shield, Arduino Yun, MIDI communication), I resorted to sending my Weki outputs to Max/MSP via OSC, and then to Arduino via Serial transmission. This turned out to be quite difficult to figure out!

Finally, I managed to get all my Wekinator outputs to Max, and from Max to my Arduino board. However, because of the way my lighting function for the NeoPixel strip worked, I wasn't able to figure out how to utilize the data, apart from the finger combinations in the way that I initially wanted. So for the purpose of getting this to work, I used just a few finger combinations. The original setup trained 11 finger combinations, but in the demo videos below you see three of these implemented.

![original finger comb charts](https://github.com/artintelclass/interactive-project-andrjjr/blob/master/IMG_5942.JPG)
![finger-combo-1](https://github.com/artintelclass/interactive-project-andrjjr/blob/master/IMG_5937.JPG)
![finger-combo-2](https://github.com/artintelclass/interactive-project-andrjjr/blob/master/IMG_5938.JPG)
![finger-combo-3](https://github.com/artintelclass/interactive-project-andrjjr/blob/master/IMG_5939.JPG)

### in Arduino

In Arduino, I used functions I had developed for the NeoPixel before. It's basically a strobe function with adjustable r,g,b,w values and strobe rate. I made each finger combo correspond to a certain preset of color and flash-rate. In the videos below, you can see how certain finger combinations change toe behaviour of the light system. 

[Demo 1](https://www.youtube.com/watch?v=RXOOUA0MhtE)

[demo 2](https://www.youtube.com/watch?v=ftwYaqqo1Zw)

[Demo 3, with altered rates](https://www.youtube.com/watch?v=c19MdWHTY7M)


