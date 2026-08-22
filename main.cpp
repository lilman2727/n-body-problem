#include "webview.h"
#include "PhysicsEngine.h"
#include <thread>
#include <chrono>
#include <filesystem>
#include <random>
#include <string>


std::string getBodiesAsJSON(PhysicsEngine& engine) {
    std::string json = "[";
    auto bodies = engine.getBodies();
    for (size_t i = 0; i < bodies.size(); ++i) {
        // Získáme souřadnice
        double x = bodies[i].getPos().getX();
        double y = bodies[i].getPos().getY();

        json += "{\"x\":" + std::to_string(x) + ",\"y\":" + std::to_string(y) + "}";

        // Přidáme čárku, pokud to není poslední prvek
        if (i < bodies.size() - 1) json += ",";
    }
    json += "]";
    return json;
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
        // req will come in this format [xxx.x, yyy.y]
        try {
            // get rid of the square braces
        std::string clean = req.substr(1, req.length() - 2);

        // Find the position of the comma that separates the two values
        size_t comma = clean.find(',');
        if (comma != std::string::npos) {
            // Split the string and convert the parts into doubles
            double x = std::stod(clean.substr(0, comma));
            double y = std::stod(clean.substr(comma + 1));

            // Create the new body
            double mass = 1.0e15;
            engine.addBody(Body(Vector2D(x, y), mass, ranColor(), ranColor(), ranColor()));
        }
    } catch (...) {
        // Just in case something fails
    }

    // WebView requires a valid JSON answer
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

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    });

    // Run the UI
    w.run(); 
    
    // Kill the physics thread
    physics_thread.detach(); 
    return 0;
}

