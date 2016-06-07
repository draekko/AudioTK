/**
 * \file SD1ToneFilter.h
 */

#ifndef ATK_EQ_SD1TONEFILTERFILTER_H
#define ATK_EQ_SD1TONEFILTERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Emulation of the SD1 tone section
  template<typename DataType_>
  class SD1ToneCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    /// Electronic components of the stack
    DataType R1, R2, R3, R4, C1, C2, C3;
    /// Parameter of the stack
    DataType alpha;
    
    static const int in_order = 2;
    static const int out_order = 2;
    
    void setup() override;
    
    /// MA part of the filter, based on the electronic components specifications
    std::vector<DataType> coefficients_in;
    /// AR part of the filter, based on the electronic components specifications
    std::vector<DataType> coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    SD1ToneCoefficients(int nb_channels = 1);
    
    /// Sets the tone of the filter
    void set_tone(DataType_ alpha);
    /// Returns the tone of the filter
    DataType_ get_tone() const;
  };
}

#endif