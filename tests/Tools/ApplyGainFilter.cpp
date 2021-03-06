/**
 * \ file ApplyGainFilter.cpp
 */

#include <ATK/Tools/ApplyGainFilter.h>

#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>
#include <boost/scoped_array.hpp>

#define PROCESSSIZE (1024*64)

BOOST_AUTO_TEST_CASE( ApplyGainFilter_sinus_test )
{
  boost::scoped_array<float> data(new float[PROCESSSIZE]);
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    data[i] = std::sin(2 * boost::math::constants::pi<float>() * (i+1.)/48000 * 1000);
  }
  
  ATK::InPointerFilter<float> generator(data.get(), 1, PROCESSSIZE, false);
  generator.set_output_sampling_rate(48000);

  boost::scoped_array<float> outdata(new float[PROCESSSIZE]);

  ATK::ApplyGainFilter<float> filter(1);
  filter.set_input_sampling_rate(48000);
  filter.set_input_port(0, &generator, 0);
  filter.set_input_port(1, &generator, 0);

  ATK::OutPointerFilter<float> output(outdata.get(), 1, PROCESSSIZE, false);
  output.set_input_sampling_rate(48000);
  output.set_input_port(0, &filter, 0);

  output.process(PROCESSSIZE);
  
  for(int64_t i = 0; i < PROCESSSIZE; ++i)
  {
    BOOST_REQUIRE_EQUAL(data[i] * data[i], outdata[i]);
  }
}
