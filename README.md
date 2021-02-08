# R5560 16k-samples/ch waveform digitizer

This code example for SciCompiler demostrate how to use the new Oscilloscope Dual component to digitize waveforms from 32 channel with a memory depth of 16Ksamples per channels at 14bits.

The standard oscilloscope component limit the waveform length to 8ksamples/ch while the new dual oscilloscope will digitize, using the same amount of memory up to 16ksamples/ch with only two limitations
	- The number of channel must be even
	- The digital tracks for channels are two

In order to be able to compile for R5560A using 16 Ksamples user must select as image type minimal in the project settings
(See the two image in the repository)
