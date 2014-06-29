/**
 * \file CachedSinusGeneratorFilter.h
 */

#ifndef ATK_TOOLS_CACHEDSINUSGENERATORFILTER_H
#define ATK_TOOLS_CACHEDSINUSGENERATORFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   *
   */
  template<typename DataType_>
  class ATK_TOOLS_EXPORT CachedSinusGeneratorFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs_size;
    using Parent::outputs;
    using Parent::output_sampling_rate;

  public:
    CachedSinusGeneratorFilter(int periods, int seconds = 1);
    ~CachedSinusGeneratorFilter();

    void set_volume(double volume);
    double get_volume() const;

    void set_offset(double offset);
    double get_offset() const;

  protected:
    virtual void process_impl(std::int64_t size);
    virtual void setup();
    
  private:
    int indice;
    int periods;
    int seconds;
    double volume;
    double offset;
    std::vector<DataType_> cache;
  };
}

#endif