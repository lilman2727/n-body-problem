#include "webview.h"
#include "PhysicsEngine.h"
#include <thread>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <random>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


std::string getBodiesAsJSON(PhysicsEngine& engine)
{
    json j_array = json::array();
    const auto& bodies = engine.getBodies();

    for (const auto& body : bodies)
    {
        json j_body;

        j_body["x"] = body.getPos().getX();
        j_body["y"] = body.getPos().getY();
        j_body["r"] = body.RED;
        j_body["g"] = body.GREEN;
        j_body["b"] = body.BLUE;
        j_body["mass"] = body.getMass();

        j_array.push_back(j_body);
    }
    //Converts JSON into a formatted std::string
    return j_array.dump();
}

int ranColor()
{
    return std::rand() % 255;
}

int main() {
    PhysicsEngine engine;

    //Create window
    webview::webview w(false, nullptr);
    w.set_title("N-Body Simulator");
    w.set_size(1920, 1080, WEBVIEW_HINT_NONE);

    //Binding adding bodies function
    w.bind("addBody", [&](std::string req) -> std::string {
        // req will come in this format [x, y, mass, isMovable,r, g, b]
        try {
            json j = json::parse(req);

            if (j.is_array() && j.size() >= 4)
            {
                double x = j[0].get<double>();
                double y = j[1].get<double>();
                double mass = j[2].get<double>() * 1e14;
                bool movable = j[3].get<bool>();

                // Generate random color only if JS didn't provide one
                int r = (j.size() >= 7) ? j[4].get<int>() : ranColor();
                int g = (j.size() >= 7) ? j[5].get<int>() : ranColor();
                int b = (j.size() >= 7) ? j[6].get<int>() : ranColor();


                engine.addBody(Body(Vector2D(x, y), mass, movable, r, g, b));
            }
    } catch (const json::exception& e) {
        std::cerr << e.what();
    }

    // WebView requires a valid JSON response
    return "{}";
    });

    w.bind("startStopSim", [&](std::string req) -> std::string {
        try
        {
            json j = json::parse(req);
            if (j.is_array() && j.size() >= 1)
            {
                bool shouldRun = j[0].get<bool>();

                if (shouldRun)
                {
                    engine.start();
                }
                else
                {
                    engine.stop();
                }

            }
        }
        catch (const json::exception&e)
        {
            std::cerr << e.what();
        }

        return "{}";
    });

    w.bind("resetSim", [&](std::string req) -> std::string {
        engine.clearBodies();
        return "{}";
    });

    //Displaying the UI
    std::filesystem::path html_path = std::filesystem::current_path() / "ui" / "index.html";
    std::string url = "file://" + html_path.string();
    w.navigate(url.c_str());

    // Run physics simulation on another thread to not disturb UI
    std::thread physics_thread([&]() {
        double dt = 1.0 / 60.0;
        while (true) {
            engine.step(dt);

            // Generate JSON
            std::string json_data = getBodiesAsJSON(engine);

            // Call JS function to update the position of bodies
            w.dispatch([&w, json_data]() {
                w.eval("updateBodies(" + json_data + ");");
            });
            //simulation is 60FPS -> make the thread sleep for approx 1/60s
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    });

    // Run the UI
    w.run(); 
    
    // Kill the physics thread
    physics_thread.detach(); 
    return 0;
}

