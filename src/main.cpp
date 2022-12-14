#include "DB/db.h"
#include "crow/crow_all.h"
#include "nlohmann/json.hpp"
#include <iostream>


int main()
{
    db* testDB = new db("testDB");
    nlohmann::json response;

    //Change this when in production builds
    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
            .global()
            .methods("POST"_method, "GET"_method)
            .prefix("/")
            .origin("*");
    //====================================================================================================

    CROW_ROUTE(app, "/")
            .methods(crow::HTTPMethod::POST)([&testDB, &response](const crow::request& req, crow::response& res) {
                CROW_LOG_INFO << "msg from client: " << req.body;  //for debug purposes
                response = testDB->query(req.body);
                res.add_header("Access-Control-Allow-Origin", "*");
                res.add_header("Content-Type", "application/json");
                res.write(response.dump());
                res.end();
            });

    app.bindaddr("127.0.0.1").port(8080).multithreaded().run();
    std::cout << "Saving and Exiting..." << std::endl;
    delete(testDB);
    return 0;
}
