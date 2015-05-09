# ppm2analog

simple ppm to analog converter written in plain C

useful to drive any standard toy remote control with a ppm signal from a radio tx:

* fetch a arduino pro mini from ebay/banggood for 2 Eur (don't worry, we are NOT going to use the arduino software...)
* drive the ppm input with your standard radio (trainer port)
* disconnect the trim pots connection to the controller ic on a toy remote of your choice
* connect the controller pin with a RC low pass to the dac pin of the atmega (see below)
* call make program (connect arduino pro min with an ftdi cable)
* have fun ;)

# lowpass filter

```
[Atmega I/O] ---------[15K]--------+------------> to toy remote IC
                                   |
                                   = 100nF
                                   |
                                  GND
```

# pinout

PPM input: 
ICP1 = PORTB.0 (labeled 8)

PWM (DAC) output:
PORTD.6 = channel 0 ( 6)
PORTD.5 = channel 1 ( 5)
PORTB.3 = channel 2 (11)
PORTD.3 = channel 3 ( 3)



