#ifndef GUARD_test_compute_app_H
#define GUARD_test_compute_app_H
#endif

#include <stdint.h>
#include "pal_api_loader/ApiRegistry.hpp"

// depends on le_backend_vk. le_backend_vk must be loaded before this class is used.

#ifdef __cplusplus
extern "C" {
#endif

void register_test_compute_app_api( void *api );

struct test_compute_app_o;

// clang-format off
struct test_compute_app_api {

	static constexpr auto id      = "test_compute_app";
	static constexpr auto pRegFun = register_test_compute_app_api;

	struct test_compute_app_interface_t {
		test_compute_app_o * ( *create               )();
		void         ( *destroy                  )( test_compute_app_o *self );
		bool         ( *update                   )( test_compute_app_o *self );
		void         ( *initialize               )(); // static methods
		void         ( *terminate                )(); // static methods
	};

	test_compute_app_interface_t test_compute_app_i;
};
// clang-format on

#ifdef __cplusplus
} // extern "C"

namespace test_compute_app {
#ifdef PLUGINS_DYNAMIC
const auto api = Registry::addApiDynamic<test_compute_app_api>( true );
#else
const auto api = Registry::addApiStatic<test_compute_app_api>();
#endif

static const auto &test_compute_app_i = api -> test_compute_app_i;

} // namespace test_compute_app

class TestComputeApp : NoCopy, NoMove {

	test_compute_app_o *self;

  public:
	TestComputeApp()
	    : self( test_compute_app::test_compute_app_i.create() ) {
	}

	bool update() {
		return test_compute_app::test_compute_app_i.update( self );
	}

	~TestComputeApp() {
		test_compute_app::test_compute_app_i.destroy( self );
	}

	static void initialize() {
		test_compute_app::test_compute_app_i.initialize();
	}

	static void terminate() {
		test_compute_app::test_compute_app_i.terminate();
	}
};

#endif