# summary
The program requires a user to record a sample word to be identified and a sentence that *may* contain the word. 
Matched filtering is then performed in the frequency domain using *fast-convolution*. 
The result is a time-domain signal with a peak indicating the presence of (or lack there of) the word in the sentence.
Theoretically words with a higher bandwidth should produce better peaks. Try whistling a chirp as your word.

## prerequisites 
  * cmake
  * fftw3
  * sfml
  * gnuplot-qt

## how to install
```bash
mkdir build
cd build
cmake ..
make -j4
./amf
```
