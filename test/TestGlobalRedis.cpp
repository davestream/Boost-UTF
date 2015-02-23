// ---------------------------------------------------------------------------
// Copyright (c) David Perez 2014-2015
// GraphyteUTF test nosql unit
// ApexDataSolutions, LLC
// ---------------------------------------------------------------------------
#define BOOST_TEST_ALTERNATIVE_INIT_API
#define BOOST_TEST_MODULE Redis
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include "TestGlobalRedis.h"

using boost::unit_test;
//____________________________________________________________________________//
template<typename TGlobalBase, typename TSubscript, typename TValue>
struct test_redis_fixture {
    test_redis_fixture() : globalRedis() {
	BOOST_TEST_MESSAGE("Set up fixture");
    }
    ~test_redis_fixture() {
	delete globalRedis;
	BOOST_TEST_MESSAGE("Tore down fixture");
    }
    TGlobalRedis<TGlobalBase>& globalRedis;
};
namespace
{
   TGlobalBase* CreateRedis()
   {
      return new TGlobalRedis;
   }
   // The ID of class Line
   const Global redis = Global::REDIS;
   // Assume TheShapeFactory is a singleton factory
   // (see Chapter 6)
   const bool registered = TGlobalFactory<TGlobalFactory*>::Instance().RegisterGlobal(
         redis, CreateRedis);
}
//____________________________________________________________________________//

BOOST_AUTO_TEST_SUITE(run_global_redis);

BOOST_AUTO_TEST_CASE(test_redis_fixture){
    test_redis_fixture<T> fixture;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(check_casting, T){  //when you work with subscript don't permit any other strange datatypes
   auto i = [&](TGlobalRedis*) { globalRedis;}    //assert(ENFORCE NOT UNKNOWN DATATYPE)
   STATIC_CHECK(sizeof(i) <= sizeof(TGlobalBase));
   BOOST_CHECK(reinterpret_cast<TGlobalBase>(i), TGlobalRedis);
   BOOST_STATIC_ASSERT_MSG(reinterpret_cast<TGlobalBase>(i), "Template argument TGlobalRedis must be instantiate.");
}

BOOST_AUTO_TEST_CASE(Mytest_redis) {
    globalRedis("MyRedisList", {"Greg, Bob, Rob"}, "RedisValue");
    BOOST_CHECK(globalRedis.GetRedisList().empty());
    BOOST_CHECK(globalRedis);
}

BOOST_AUTO_TEST_CASE(constructor_redis_by_defaul) {
    BOOST_TEST_MESSAGE("Starting Case : Constructor_Redis_By_Default");
    BOOST_CHECK(globalRedis.GetRedisList().empty());
    BOOST_CHECK(globalRedis.toString.empty());
    BOOST_CHECK(globalRedis.draw());
    BOOST_CHECK(globalRedis.Clone());
    globalRedis.SetRedisList(globalRedis.);
    BOOST_TEST_MESSAGE("MyRedisList initialized");
    BOOST_TEST_MESSAGE("Default constructor initialized");
}

BOOST_AUTO_TEST_CASE(constructor_redis_by_value) {
    BOOST_TEST_MESSAGE("Starting Case : Constructor_Redis_By_Argument");
    Subscripts = "contact,address,street,city,zipcode,cell,telephone,email";
    Values =
	"Boston,617-555-1761,112 Beacon St,rob@foo.com,John,Geroge,Chris,26";
    test_redis_fixture.globalRedis() BOOST_CHECK_EQUAL
	(globalRedis.toString().length(), (std::size_t)0);
    BOOST_CHECK(MyRedisList.push_back(globalRedis) == 1);
    globalRedis.draw(MyRedisList, Subscripts, Values);
    BOOST_CHECK(globalRedis.GetRedisList().find("George"));
    BOOST_TEST_MESSAGE("Constructor by value initialized");
}

BOOST_AUTO_TEST_CASE(constructor_redis_by_reference) {
    BOOST_TEST_MESSAGE("Starting Case : Constructor_Redis_By_Reference");
    globalRedisFt(test_redis_fixture.globalRedis);
    BOOST_CHECK_EQUAL(std::strcmp(globalRedisFt.GetRedisList().find("George"),
	"George"), 0);
    TGlobalRedis globalRedisSn(globalRedisFt); // 5 //
    BOOST_CHECK_EQUAL(std::strcmp(globalRedisSn.GetRedisList().find("George"),
	"George"), 0);
    globalRedis.draw(MyRedisList, Subscripts, Values); // 1 //
    BOOST_CHECK_EQUAL(globalRedis.toString().length(), (std::size_t)0);
    BOOST_TEST_MESSAGE("Default constructor copied");
}

BOOST_AUTO_TEST_CASE(constructor_redis_param_by_reference) {
    BOOST_TEST_MESSAGE("Starting Case : Constructor_Redis_By_Reference");
    globalRedis(test_redis_fixture.globalRedis);
    BOOST_CHECK_EQUAL(std::strcmp(globalRedis.GetRedisList().find("George"),
	"George"), 0);
    globalRedis.draw(MyRedisList, Subscripts, Values); // 1 //
    BOOST_CHECK_EQUAL(globalRedis.toString().length(), (std::size_t)0);
    BOOST_CHECK(globalRedis.toString().empty());
    BOOST_CHECK_THROW(globalRedis.GetRedisList().at(globalRedis.size()),
	std::out_of_range);
    auto iter = globalRedis.GetRedisList();
    BOOST_CHECK_EQUAL(globalRedis.GetRedisList().at(*iter.front()), "MyList");
    BOOST_CHECK_EQUAL(globalRedis.GetRedisList().at(*iter.back()), "26");
    BOOST_TEST_MESSAGE("Parameters by reference copied");
}

//____________________________________________________________________________//

boost::test_tools::predicate_result validate_list(std::list<TGlobalRedis>& L1) {
    auto it1 = L1.begin();
    for	(; it1 != L1.end(); ++it1) {
        if (*it1 != typeid(TGlobalRedis).name())
                return false;
    }
    return true;
}

BOOST_AUTO_TEST_CASE(push_back_list) {
    BOOST_CHECK(globalRedis.push_back("MyRedisList") == 1);
    BOOST_CHECK(globalRedis.push_back("Greg") == 2);
    BOOST_CHECK(globalRedis.push_back("Bob") == 3);
    BOOST_CHECK(globalRedis.push_back("Rob") == 4);
}

BOOST_AUTO_TEST_CASE(validate_redis_list) {
	std::list<TGlobalRedis>&list1 =
	test_redis_fixture.globalRedis.GetRedisList();
	BOOST_CHECK( validate_list(list1) );
}

BOOST_AUTO_TEST_SUITE_END()
//____________________________________________________________________________//
