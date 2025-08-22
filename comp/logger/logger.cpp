#include "logger/logger.h"

#include <memory>
#include "opentelemetry/exporters/ostream/log_record_exporter.h"
#include "opentelemetry/logs/provider.h"
#include "opentelemetry/sdk/logs/exporter.h"
#include "opentelemetry/sdk/logs/logger_provider.h"
#include "opentelemetry/sdk/logs/logger_provider_factory.h"
#include "opentelemetry/sdk/logs/provider.h"
#include "opentelemetry/sdk/logs/simple_log_record_processor_factory.h"

namespace { // anonymous

class logger_instance_t
{
public:
	logger_instance_t()
	{ 
        // Create ostream log exporter instance
        auto exporter =
            std::unique_ptr<opentelemetry::sdk::logs::LogRecordExporter>(new opentelemetry::exporter::logs::OStreamLogRecordExporter);
        auto processor = opentelemetry::sdk::logs::SimpleLogRecordProcessorFactory::Create(std::move(exporter));

        std::shared_ptr<opentelemetry::sdk::logs::LoggerProvider> sdk_provider(
            opentelemetry::sdk::logs::LoggerProviderFactory::Create(std::move(processor)));

        // Set the global logger provider
        const std::shared_ptr<opentelemetry::logs::LoggerProvider>& api_provider = sdk_provider;
        opentelemetry::sdk::logs::Provider::SetLoggerProvider(api_provider);
    }
	~logger_instance_t()
	{
        std::shared_ptr<opentelemetry::logs::LoggerProvider> noop;
        opentelemetry::sdk::logs::Provider::SetLoggerProvider(noop);
    }
	logger::plogger_t get()
	{
        auto provider = opentelemetry::logs::Provider::GetLoggerProvider();
        return provider->GetLogger("foo_library_logger", "foo_library");
    }
};

} // anonymous namespace

namespace logger {

/* The compiler dependent code below ensures that the logger is initialized before any other
    object is called.
    At least, when logger.cpp is compiled into a static library and linked into an application.
    This allows also logging in static objects' constructors.
    */
#ifdef _WIN32
#pragma init_seg(lib)
static logger_instance_t logger_instance;
logger::plogger_t plogger = logger_instance.get();
#elif __linux__
static logger_instance_t logger_instance __attribute__((init_priority(101)));
logger::plogger_t plogger __attribute__((init_priority(101))) = logger_instance.get();
#elif __APPLE__
#error "Apple platforms are not supported yet."
#else
#error "Unsupported platform. Please define ptracer for your platform."
#endif

} // namespace logger
