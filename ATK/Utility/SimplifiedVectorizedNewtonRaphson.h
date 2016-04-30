/**
 * \file SimplifiedVectorizedNewtonRaphson.h
 */

#ifndef ATK_UTILITY_SIMPLIFIEDVECTORIZEDNEWTONRAPHSON_H
#define ATK_UTILITY_SIMPLIFIEDVECTORIZEDNEWTONRAPHSON_H

#include <cmath>
#include <limits>

#include <ATK/config.h>

#include <Eigen/Dense>

namespace ATK
{
  /// Simplified Vectorized Newton Raphson optimizer
  /*!
   * A NR optimizer, 10 iterations max, for stabilized computation
   */
  template<typename Function, int size, int max_iterations=10>
  class SimplifiedVectorizedNewtonRaphson
  {
    typedef typename Function::DataType DataType;
    
    Function function;
    
    DataType precision;
    DataType maxstep;
    
    typedef Eigen::Matrix<DataType, size, 1> Vector;
    
  public:
    /*!
     * @brief Constructs the optimizer
     * @param function is the function that we will try to optimize.
     *   It is a functor taking x[n-1], x[n], y[n-1] and an estimate y[n], returning the value of the cost function and its derivative according to y[n]
     * @param precision is the precision that the optimizer will try to achieve. By default uses $$\\sqrt{\\epsilon_{Datatype}}$$
     */
    SimplifiedVectorizedNewtonRaphson(Function&& function, DataType precision = 0)
    :function(std::move(function)), precision(precision), maxstep(static_cast<DataType>(.1))
    {
      if(precision == 0)
      {
        this->precision = std::sqrt(std::numeric_limits<DataType>::epsilon());
      }
    }
    
    /// Optimize the function and sets its internal state
    Vector optimize()
    {
      Vector y1(Vector::Zero());
      int j;
      for(j = 0; j < max_iterations; ++j)
      {
        auto all = function(y1);
        Vector cx = all.second.colPivHouseholderQr().solve(all.first);
        auto yk = y1 - cx;
        if((cx.array().abs() < precision).all())
        {
          return yk;
        }
        y1 = yk;
      }
      return y1;
    }
  };
}

#endif
