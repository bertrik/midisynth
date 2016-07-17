This is an experiment for a simple Arduino based synthesizer.
Probably not the first time anyone came up with this idea,
but I just like to play around creating this myself.

The idea is that the arduino receives midi commands over the
serial port and then synthesizes them as simple tones.
I have not decided yet how to output the audio, as PWM
or perhaps through a D/A-converter (like an R-2R ladder
on D2-D7).

I plan to use ttymidi to create a midi device on the PC
to play midi files on, see
http://www.varal.org/ttymidi/

