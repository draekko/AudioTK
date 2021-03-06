#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter, PipelineGlobalSinkFilter
from ATK.Delay import DoubleStereoUniversalFixedDelayLineFilter

import matplotlib.pyplot as plt

sample_rate = 96000

import sys, os
sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/..")
from display.compare_spec import plot_me

def filter(inputl, inputr, blend_ch1=0, blend_ch2=0,
    feedback_ch1_ch1=0, feedback_ch1_ch2=0, feedback_ch2_ch1=0, feedback_ch2_ch2=0,
    feedforward_ch1_ch1=1, feedforward_ch1_ch2=0, feedforward_ch2_ch1=0, feedforward_ch2_ch2=1):
  import numpy as np
  outputl = np.zeros(inputl.shape, dtype=np.float64)
  outputr = np.zeros(inputl.shape, dtype=np.float64)

  infilterL = DoubleInPointerFilter(inputl, False)
  infilterL.set_input_sampling_rate(sample_rate)
  infilterR = DoubleInPointerFilter(inputr, False)
  infilterR.set_input_sampling_rate(sample_rate)

  delayfilter = DoubleStereoUniversalFixedDelayLineFilter(5000)
  delayfilter.set_input_sampling_rate(sample_rate)
  delayfilter.set_input_port(0, infilterL, 0)
  delayfilter.set_input_port(1, infilterR, 0)
  delayfilter.set_delay_ch1(4800) #50ms
  delayfilter.set_delay_ch2(3600) #37.5ms
  delayfilter.set_blend_ch1(blend_ch1)
  delayfilter.set_blend_ch1(blend_ch2)
  delayfilter.set_feedback_ch1_ch1(feedback_ch1_ch1)
  delayfilter.set_feedback_ch1_ch2(feedback_ch1_ch2)
  delayfilter.set_feedback_ch2_ch1(feedback_ch2_ch1)
  delayfilter.set_feedback_ch2_ch2(feedback_ch2_ch2)
  delayfilter.set_feedforward_ch1_ch1(feedforward_ch1_ch1)
  delayfilter.set_feedforward_ch1_ch2(feedforward_ch1_ch2)
  delayfilter.set_feedforward_ch2_ch1(feedforward_ch2_ch1)
  delayfilter.set_feedforward_ch2_ch2(feedforward_ch2_ch2)
  
  outfilterl = DoubleOutPointerFilter(outputl, False)
  outfilterl.set_input_sampling_rate(sample_rate)
  outfilterl.set_input_port(0, delayfilter, 0)

  outfilterr = DoubleOutPointerFilter(outputr, False)
  outfilterr.set_input_sampling_rate(sample_rate)
  outfilterr.set_input_port(0, delayfilter, 1)
  
  pipelineend = PipelineGlobalSinkFilter()
  pipelineend.set_input_sampling_rate(sample_rate)
  pipelineend.add_filter(outfilterl)
  pipelineend.add_filter(outfilterr)
  pipelineend.process(inputl.shape[1])

  return outputl, outputr

if __name__ == "__main__":
  import numpy as np
  samples = 2000000
  freq_max = 20000

  t = np.arange(samples, dtype=np.float64).reshape(1, -1) / sample_rate
  d = np.sin(np.pi * (sample_rate * freq_max / samples * (t + .1)) * t)
  dr = d[:,::-1].copy()
  
  np.savetxt("input.txt", d)
  outl, outr = filter(d, dr, blend_ch1=1, blend_ch2=1,
    feedforward_ch1_ch1=-1, feedforward_ch2_ch2=-1, feedforward_ch1_ch2=.1, feedforward_ch2_ch1=.7,
    feedback_ch1_ch1=-.5, feedback_ch1_ch2=.1, feedback_ch2_ch1=.3, feedback_ch2_ch2=-.1, )
  np.savetxt("outputl.txt", outl)
  np.savetxt("outputr.txt", outr)

  plt.figure()
  plot_me((d[0], outl[0]), sample_rate)
  plt.gcf().suptitle("Delay Channel R")
  plt.figure()
  plot_me((dr[0], outr[0]), sample_rate)
  plt.gcf().suptitle("Delay Channel L")
  plt.show()
