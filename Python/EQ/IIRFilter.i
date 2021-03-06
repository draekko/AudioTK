
%{
#include <ATK/EQ/IIRFilter.h>
%}

%include <std_vector.i>

%template(FloatVector) std::vector<float>;
%template(DoubleVector) std::vector<double>;

namespace ATK
{
  template<class Coefficients>
  class IIRFilter: public Coefficients
  {
  public:
    IIRFilter(int nb_channels = 1);
    ~IIRFilter();
    void process(long size);
  };
}

%define IIRFilterExtend(name, T)
%extend name {
  std::vector<T> get_coefficients_in()
  {
    return (*self).get_coefficients_in();
  }
  std::vector<T> get_coefficients_out()
  {
    return (*self).get_coefficients_out();
  }
}
%enddef

%define FIRFilterExtend(name, T)
%extend name {
  std::vector<T> get_coefficients_in()
  {
    return (*self).get_coefficients_in();
  }
}
%enddef
