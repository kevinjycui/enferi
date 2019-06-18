# ENFERI

*Electroencephalographic Neuromuscular Facial Expression Recognition Interface*

## Contributors
 - Kevin Cui ([kevinjycui](https://github.com/kevinjycui))
 - Jordan Frankel ([jordanfrankel](https://github.com/jordanfrankel))

## Description
The objective is to use an LED matrix that successfully manages to replicate facial expressions. This will be done by using EEG facial expression recognition technology to interpret the facial expressions and to send them to the matrix to be displayed. The EEG headband uses 5 electrodes to detect electric neurotransmission signals caused by the firing of neurons to interpret the facial expressions expressed. The matrix then takes the signals from Python and Arduino (using JSON-RPC to communicate between the EEG and Python; using the serial port to communicate between Python and Arduino) to draw corresponding movements.

## Schematic
The face animated on the matrix, nicknamed ENFERI (Electroencephalographic Neuromuscular Facial Expression Recognition Interface) matches the expression based on 3 variables: the upper face (muscles in the forehead), the eyes (muscles in the movement of the eyes; eyelids), and the lower face (muscles around the mouth). The 5 electrodes are placed on the head at strategic positions to take in frequencies from the extrapyramidal system and primary motor cortex, that translate into stimulated muscle motion. Using Bluetooth, the USB Receiver can take this data and feed it to a JSON communication module. This can then use the data in a Python script in the form of strings that represent the expression from a set of possibilities. The Python script produces a single byte variable that corresponds to each expression and sends it through the serial port. The Arduino reads this data, and displays an animation based on the expression.

## Components
 - Emotiv INSIGHT 5 Channel Mobile EEG
 - 64x32 LED Matrix
 - Arduino Mega
 - 15 Jumpers
 - USB Receiver Universal Model
