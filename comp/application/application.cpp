#include <iostream>

#include "tracer/tracer.h"
#include "logger/logger.h"

void trace_something()
{
    std::cout << "Trace something\n";
    auto scoped_span = tracer::scope_t(tracer::ptracer->StartSpan("Something for tracing"));
}

void log_something()
{
    std::cout << "Log something\n";
    logger::plogger->Debug("Something for logging");
}

int main()
{
    trace_something();
	log_something();
    std::cout << "Done\n";
}
