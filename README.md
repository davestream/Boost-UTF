C-Standard-Template-Library
===========================

# **Test Enumeration Module**  #
 
## How use UTFrunner in your project ##

Start with `BOOST_MACROS`:

`BOOST_TEST_NO_MAIN`: to define unit test without the main function
`BOOST_TEST_MODULE`: to provide the Master test unit
`BOOST_GLOBAL_FIXTURE`: to work with Global fixture
`BOOST_AUTO_TEST_SUITE`: to format the unit test suite
`BOOST_AUTO_TEST_CASE`: to provide assertions and checking 
`BOOST_TEST_TEMPLATE_CASE`: to measure object template
`BOOST_TEST_TEMPLATE_FUNCTION`: to manipulate function template 
`BOOST_AUTO_TEST_CASE_TEMPLATE`: to run only template test case
`BOOST_CHECK_PREDICATE`:

Now compiling the source codes our test case is passing: 

    Running 1 test case...
    Starting Case : Constructors_By_Default
    *** No errors detected
    
    EXIT STATUS: 0

The `constructor_redis_by_default` tests by default the constructor in the test case at subdirectory: `../utfrunner/TestSuite/` open the file: 
> TestGlobalRedis.cpp

where you can see the source codes that using the `BOOST_CHECK`

    BOOST_TEST_CASE( constructor_redis_by_default ){
    	BOOST_TEST_MESSAGE( "Starting Case : Constructor_Redis_By_Default" );
		...
	    TGlobalRedis globalRedis(NULL);
		BOOST_CHECK_EQUAL();
	    BOOST_CHECK( globalRedis.ExistSet());
		...
		BOOST_TEST_MESSAGE( "Default constructor initialized" );
	}

it will report to the compiler that the initialization of the default constructor of the 
`TGlobalRedis` is initialized:

    Running 1 test case
	Default constructor initialized 
      
    *** No errors detected

