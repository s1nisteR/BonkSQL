#include "DB/db.h"
#include "crow/crow_all.h"




int main()
{
    db* testDB = new db;

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
            .methods(crow::HTTPMethod::POST)([&testDB](const crow::request& req) {
                CROW_LOG_INFO << "msg from client: " << req.body;
                testDB->query(req.body);
                return "";
            });

    app.bindaddr("127.0.0.1").port(8080).multithreaded().run();
    return 0;
}
