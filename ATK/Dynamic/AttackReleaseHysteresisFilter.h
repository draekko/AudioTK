/**
 * \file AttackReleaseHysteresisFilter.h
 */

#ifndef ATK_DYNAMIC_ATTACKRELEASEHYSTERESISFILTER_H
#define ATK_DYNAMIC_ATTACKRELEASEHYSTERESISFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Creates an output signal with the filter power of the input (computed with an AR1 with hysteresis)
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT AttackReleaseHysteresisFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    AttackReleaseHysteresisFilter(int nb_channels = 1);
    /// destructor
    ~AttackReleaseHysteresisFilter();

    /// Sets the speed of the attack (between 0 and 1)
    void set_attack(DataType_ attack);
    /// Gets the attack speed
    DataType_ get_attack() const;
    /// Sets the speed of the release (between 0 and 1)
    void set_release(DataType_ release);
    /// Gets the release speed
    DataType_ get_release() const;

    /// Change the attack hysteresis (must be superior to the release hysteresis)
    /*!
     * Be aware that attack hysteresis is tricky, as you can never get up to the input power...
     */
    void set_attack_hysteresis(DataType_ attack_hysteresis);
    /// Change the attack hysteresis in dB
    void set_attack_hysteresis_db(DataType_ attack_hysteresis_db);
    /// Gets the attack hysteresis factor
    DataType_ get_attack_hysteresis() const;
    /// Change the release hysteresis (between 0 and 1)
    void set_release_hysteresis(DataType_ release_hysteresis);
    /// Change the release hysteresis in dB
    void set_release_hysteresis_db(DataType_ release_hysteresis_db);
    /// Gets the release hysteresis factor
    DataType_ get_release_hysteresis() const;
    
  protected:
    virtual void process_impl(int64_t size) const override final;
    
  private:
    DataType_ attack;
    DataType_ release;
    DataType_ attack_hysteresis;
    DataType_ release_hysteresis;
  };
}

#endif
