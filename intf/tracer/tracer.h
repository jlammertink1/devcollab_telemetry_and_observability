#ifndef TRACER__TRACER_H
#define TRACER__TRACER_H

#include "opentelemetry/sdk/trace/tracer.h"
#include "opentelemetry/trace/tracer.h"

namespace tracer {

using ptracer_t = opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer>;
using scope_t = opentelemetry::trace::Scope;

extern ptracer_t ptracer;

} // namespace tracer

#endif // TRACER__TRACER_H
