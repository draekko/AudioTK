/**
 * \file GainMaxColoredExpanderFilter.h
 */

#ifndef ATK_DYNAMIC_GAINMAXCOLOREDEXPANDERFILTER_H
#define ATK_DYNAMIC_GAINMAXCOLOREDEXPANDERFILTER_H

#include <vector>

#include <ATK/Dynamic/GainFilter.h>
#include "config.h"

namespace ATK
{
  /// Colored gain "expander". Computes a new amplitude/volume gain based on threshold, slope and the power of the input signal
  /*!
   * The maximum reduction is given by max_reduction
   */
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT GainMaxColoredExpanderFilter : public GainFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef GainFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::ratio;
    using Parent::recomputeFuture;
    using Parent::recomputeLUT;
    using Parent::start_recomputeLUT;

    DataType_ softness;
    DataType_ max_reduction;
    DataType_ color;
    DataType_ quality;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    * @param LUTsize is the total LUT size used by the filter
    * @param LUTprecision is the number of elements used to compute values < 1
    */
    GainMaxColoredExpanderFilter(int nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 1024);
    /// Destructor
    ~GainMaxColoredExpanderFilter();

    /// Sets the softness of the knee of the filter (positive value)
    void set_softness(DataType_ softness);
    /// Retrieves the softness afctor
    DataType_ get_softness() const;

    /// Sets the color of the filter, the behavior around the threshold
    /*!
    * A positive value increases the gain, a negative value lowers it
    */
    void set_color(DataType_ color);
    /// Returns the color factor
    DataType_ get_color() const;
    /// Sets the quality, the extent around the threshold where the color factor has an effect
    void set_quality(DataType_ quality);
    /// Returns the quality factor
    DataType_ get_quality() const;

    /// Sets the maximum reduction factor of the filter (limit reduction to this factor instead of infinite)
    void set_max_reduction(DataType_ max_reduction);
    /// Sets the maximum reduction in dB
    void set_max_reduction_db(DataType_ max_reduction);
    /// Gets the maximum reduction factor
    DataType_ get_max_reduction() const;

  protected:
    DataType_ computeGain(DataType_ value) const override final;
  };
}

#endif
