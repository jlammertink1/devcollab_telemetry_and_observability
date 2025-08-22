#include "tracer/tracer.h"

#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/sdk/trace/provider.h"
#include "opentelemetry/trace/provider.h"

namespace { // anonymous

class tracer_instance_t
{
public:
	tracer_instance_t()
	{ 
		// Create ostream span exporter instance
		auto exporter = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();
		auto processor = opentelemetry::sdk::trace::SimpleSpanProcessorFactory::Create(std::move(exporter));

		std::shared_ptr<opentelemetry::sdk::trace::TracerProvider> sdk_provider =
			opentelemetry::sdk::trace::TracerProviderFactory::Create(std::move(processor));

		// Set the global trace provider
		const std::shared_ptr<trace_api::TracerProvider>& api_provider = sdk_provider;
		opentelemetry::sdk::trace::Provider::SetTracerProvider(api_provider);
	}
	~tracer_instance_t()
	{
		std::shared_ptr<trace_api::TracerProvider> noop;
		opentelemetry::sdk::trace::Provider::SetTracerProvider(noop);
	}
	tracer::ptracer_t get()
	{
		auto provider = opentelemetry::trace::Provider::GetTracerProvider();
		return provider->GetTracer("bimcollab_tracer");
	}
};

} // anonymous namespace

namespace tracer {

/* The compiler dependent code below ensures that the tracer is initialized before any other
   object is called. 
   At least, when tracer.cpp is compiled into a static library and linked into an application.
   This allows also tracing in static objects' constructors.
 */
#ifdef _WIN32
#pragma init_seg(lib)
static tracer_instance_t tracer_instance;
tracer::ptracer_t ptracer = tracer_instance.get();
#elif __linux__
static tracer_instance_t tracer_instance __attribute__((init_priority(101)));
tracer::ptracer_t ptracer __attribute__((init_priority(101))) = tracer_instance.get();
#elif __APPLE__
#error "Apple platforms are not supported yet."
#else
#error "Unsupported platform. Please define ptracer for your platform."
#endif

} // namespace tracer
