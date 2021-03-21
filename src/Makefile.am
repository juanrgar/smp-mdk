NULL=

sources_h = \
		   Mdk/SimpleTypes.h \
		   Mdk/Duration.h \
		   Mdk/DateTime.h \
		   Mdk/AnySimple.h \
		   Mdk/Uuid.h \
		   Mdk/Array.h \
		   Mdk/String.h \
		   Mdk/Object.h \
		   Mdk/Composite.h \
		   Mdk/Component.h \
		   Mdk/EntryPoint.h \
		   Mdk/EventSink.h \
		   Mdk/EventSource.h \
		   Mdk/Aggregate.h \
		   Mdk/Reference.h \
		   Mdk/Container.h \
		   Mdk/Model.h \
		   Mdk/Request.h \
		   Mdk/Invocator.h \
		   Mdk/Management/ManagedObject.h \
		   Mdk/Management/ManagedComponent.h \
		   Mdk/Management/ManagedContainer.h \
		   Mdk/Management/ManagedReference.h \
		   Mdk/Management/EventProvider.h \
		   Mdk/Management/EventConsumer.h \
		   Mdk/Management/EntryPointPublisher.h \
		   $(NULL)

sources_c = \
		   Mdk/Duration.cpp \
		   Mdk/DateTime.cpp \
		   Mdk/AnySimple.cpp \
		   Mdk/Uuid.cpp \
		   Mdk/Object.cpp \
		   Mdk/Composite.cpp \
		   Mdk/Component.cpp \
		   Mdk/Aggregate.cpp \
		   Mdk/Model.cpp \
		   Mdk/Request.cpp \
		   Mdk/Invocator.cpp \
		   Mdk/Management/ManagedObject.cpp \
		   Mdk/Management/ManagedComponent.cpp \
		   Mdk/Management/EventProvider.cpp \
		   Mdk/Management/EventConsumer.cpp \
		   Mdk/Management/EntryPointPublisher.cpp \
		   $(NULL)

lib_LTLIBRARIES = libsmpmdk.la

libsmpmdk_la_SOURCES = $(sources_c) $(sources_h)
libsmpmdk_la_LIBADD = @LTLIBOBJS@
libsmpmdk_la_CFLAGS = $(LIBSMPMDK_CFLAGS)
libsmpmdk_la_CXXFLAGS = $(LIBSMPMDK_CXXFLAGS) -std=c++98
libsmpmdk_la_LDFLAGS = -version-info $(LIBSMPMDK_LT_VERSION) -export-dynamic -no-undefined
