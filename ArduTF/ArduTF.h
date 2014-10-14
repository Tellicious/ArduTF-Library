#if defined(ARDUINO_ARCH_AVR)
#include "inttypes.h"
#elif defined(ARDUINO_ARCH_SAM)
#include "variant.h"
#else
#error "This library only supports boards with an AVR or SAM processor."
#endif
#include "Integrator.h"
#include "Derivative.h"
#include "Filter.h"