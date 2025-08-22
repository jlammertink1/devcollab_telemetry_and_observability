# DevCollab Telemetry & Observability

The project 'application' simulates a simple application that uses the OpenTelemetry C++ SDK to send telemetry data to a collector. 
The project 'logger' implements a custom logger that sends log messages to the collector. 
The project 'tracer' implements a custom tracer that sends trace data to the collector.
The projects 'logger_unittest' and 'tracer_unittest' are unit tests for the logger and tracer, respectively.
All other projects are used to build the OpenTelemetry C++ SDK and its dependencies.

## Clone the repository

```bash
git clone --recurse-submodules git@github.com:jlammertink1/devcollab_telemetry_and_observability.git
cd devcollab_telemetry_and_observability
```

## Build under Windows

In mingw64 git:
```bash
cd build
cmake ../opentelemetry-cpp -G "Visual Studio 17 2022" -A x64
```

Open solution "devcollab_telemetry_and_observability.sln"
Right mouse button press 'ALL_BUILD' in solution explorer, select 'Build'

Right mouse button press 'logger_unittest' in solution explorer, select 'Build'
Right mouse button press 'tracer_unittest' in solution explorer, select 'Build'
Right mouse button press 'application' in solution explorer, select 'Build'

## Build under Linux


## To do's

* Add a linux build (WSL)
* Move the repositories to KUBUS Azure
* Create a pipeline for the build
* Replace in logger the opentelemtry_exporter_ostream_logs by an exporter for Azure
* Replace in tracer the opentelemtry_exporter_ostream_logs by an exporter for Azure
* Configure Azure to receive the telemetry data
* Go to C++20 i.s.o. C++14