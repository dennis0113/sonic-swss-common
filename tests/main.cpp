#include "gtest/gtest.h"
#include "common/dbconnector.h"
#include <iostream>

using namespace std;
using namespace swss;

string existing_file = "./tests/redis_multi_db_ut_config/database_config.json";
string nonexisting_file = "./tests/redis_multi_db_ut_config/database_config_nonexisting.json";

class SwsscommonEnvironment : public ::testing::Environment {
public:
    // Override this to define how to set up the environment.
    void SetUp() override {
        // by default , init should be false
        cout<<"Default : isInit = "<<SonicDBConfig::isInit()<<endl;
        EXPECT_FALSE(SonicDBConfig::isInit());

        // load nonexisting file, should throw exception with NO file existing
        try
        {
            cout<<"INIT: loading nonexisting db config file"<<endl;
            SonicDBConfig::initialize(nonexisting_file);
        }
        catch (exception &e)
        {
            EXPECT_TRUE(strstr(e.what(), "Sonic database config file doesn't exist"));
        }
        EXPECT_FALSE(SonicDBConfig::isInit());

        // load local config file, init should be true
        SonicDBConfig::initialize(existing_file);
        cout<<"INIT: load local db config file, isInit = "<<SonicDBConfig::isInit()<<endl;
        EXPECT_TRUE(SonicDBConfig::isInit());
    }
};

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    // Registers a global test environment, and verifies that the
    // registration function returns its argument.
    SwsscommonEnvironment* const env = new SwsscommonEnvironment;
    testing::AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}
