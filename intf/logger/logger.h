#ifndef LOGGER__LOGGER_H
#define LOGGER__LOGGER_H

#include "opentelemetry/sdk/logs/logger.h"
#include "opentelemetry/logs/logger.h"

namespace logger {

using plogger_t = opentelemetry::nostd::shared_ptr<opentelemetry::logs::Logger>;

extern plogger_t plogger;

} // namespace logger

#endif // LOGGER__LOGGER_H