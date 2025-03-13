Adaptation of Lissajous demonstrtor to STM32F030, without RTOS


* branch irq is first sw work, using irq on TIM1
  (but for a 48MHz core, and sampling  at 50kHz, this is less than 1000 cpu 
  cycles per sample. While we don't do much, it's a large waste of cpu

* branch dma uses DMA, and no cpu cycle are needed at all (not yet ok)


Outputs are on PA8 and PA9 and requires a RC low pass filter
  
