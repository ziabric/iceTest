#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Network.hpp>

#include <ClientUDPThread.h>

float valueVoltage = 0;
float valueStrength = 0;
float valueFuel = 0;
float valueFuelSpeed = 0;
float valueX = 0;
float valueY = 0;
float valueMagnetometer = 0;
float valueAccelerometer = 0;
float valueHeight = 0;

int servo1 = 0;
int servo2 = 0;
int servo3 = 0;

char flagFromServer = ' ';
float valueFromServer = '0';
char* bufferFromServer;
size_t bufferSizeFromServer;
std::string bufferString;

void parsing(ClientUDPThread &cl)
{
    if ( !cl.HasMessages() ) return;

    cl.PopRecievedMessage(bufferFromServer, bufferSizeFromServer);
    bufferString = std::string(bufferFromServer, bufferSizeFromServer);

    if ( bufferString.size() < 3 ) return;

    flagFromServer = bufferString[0];
    valueFromServer = std::stoi(bufferString.substr(2));

    if ( flagFromServer == 'v' ) valueVoltage = valueFromServer;
    else if ( flagFromServer == 'i' ) valueStrength = valueFromServer;
    else if ( flagFromServer == 'h' ) valueFuel = valueFromServer;
    else if ( flagFromServer == 'V' ) valueFuelSpeed = valueFromServer;
    else if ( flagFromServer == 'x' ) valueX = valueFromServer;
    else if ( flagFromServer == 'y' ) valueY = valueFromServer;
    else if ( flagFromServer == 'o' ) valueMagnetometer = valueFromServer;
    else if ( flagFromServer == 'a' ) valueAccelerometer = valueFromServer;
    else if ( flagFromServer == 'H' ) valueHeight = valueFromServer;
}

void display(ImVec2 size, ClientUDPThread &cl)
{
    if (ImGui::Begin("Video window", nullptr, ImGuiWindowFlags_NoMove + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetWindowPos({0,0});
        ImGui::SetWindowSize({800, 600});
        


        ImGui::End();
    }

    if (ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoMove + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetWindowPos({800, 0});
        ImGui::SetWindowSize({300, 600});

        if (ImGui::BeginChild("infoFromDron", {280, 250}, ImGuiChildFlags_Border))
        {
            ImGui::Text(std::string("Voltage -- " + std::to_string(valueVoltage)).c_str());
            ImGui::Separator();
            ImGui::Text(std::string("Strength -- " + std::to_string(valueStrength)).c_str());
            ImGui::Separator();
            ImGui::Text(std::string("Fuel level -- " + std::to_string(valueFuel)).c_str());
            ImGui::Separator();
            ImGui::Text(std::string("Fuel speed -- " + std::to_string(valueFuelSpeed)).c_str());
            ImGui::Separator();
            ImGui::Text(std::string("X -- " + std::to_string(valueX)).c_str());
            ImGui::Separator();
            ImGui::Text(std::string("Y -- " + std::to_string(valueY)).c_str());
            ImGui::Separator();
            ImGui::Text(std::string("Magnetometer -- " + std::to_string(valueMagnetometer)).c_str());
            ImGui::Separator();
            ImGui::Text(std::string("Accelerometer -- " + std::to_string(valueAccelerometer)).c_str());
            ImGui::Separator();
            ImGui::Text(std::string("Height -- " + std::to_string(valueHeight)).c_str());
            ImGui::EndChild();
        }

        if (ImGui::BeginChild("Controls", {280, 150}, ImGuiChildFlags_Border))
        {
            ImGui::Text("Controls");
            ImGui::Separator();
            if (ImGui::SliderInt("Servo 1", &servo1, 0, 180)) cl.SendMessage("s1:"+std::to_string(servo1));
            if (ImGui::SliderInt("Servo 2", &servo2, 0, 180)) cl.SendMessage("s2:"+std::to_string(servo2));
            if (ImGui::SliderInt("Servo 3", &servo3, 0, 180)) cl.SendMessage("s3:"+std::to_string(servo3));
            ImGui::EndChild();
        }
        ImGui::End();
    }
}


int main()
{
    ClientUDPThread client(80, {"192.168.0.1"}, SocketDirection::Both);

    sf::RenderWindow window(sf::VideoMode(1100, 600), "ICE", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    if(ImGui::SFML::Init(window))
    {
        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(window, event);
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            ImGui::SFML::Update(window, deltaClock.restart());

            display({(float)window.getSize().x, (float)window.getSize().y}, client);

            window.clear();
            ImGui::SFML::Render(window);
            window.display();
        }
        ImGui::SFML::Shutdown();
    }
    client.StopThread();
    return 0;
}
