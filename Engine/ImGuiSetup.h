//
// Created by nikita on 18.08.2025.
//

#ifndef ENGINE7_IMGUISETUP_H
#define ENGINE7_IMGUISETUP_H

void SetCustomImStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 10.0f;
    style.FrameRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 0.0f;

    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.54,0.54,0.54,0.93);
    style.Colors[ImGuiCol_Border] = ImVec4(0.76,0.76,0.76,1);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.31,0.31,0.31,1);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.54,0.54,0.54,0.93);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.54,0.54,0.54,0.93);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.54,0.54,0.54,0.70);

    //el
    style.Colors[ImGuiCol_Button] = ImVec4(0.54,0.54,0.54,0.93);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3,0.3,0.3,0.93);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.3,0.3,0.3,0.93);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.6,0.6,0.6,0.93);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.54,0.54,0.54,0.93);

    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.54,0.54,0.54,0.93);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.54,0.54,0.54,0.93);

    //
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.54,0.54,0.54,0.93);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.54,0.54,0.54,0.93);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.54,0.54,0.54,0.93);

    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.50,0.50,0.50,0.93);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54,0.54,0.54,0.93);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.6,0.6,0.6,0.93);


}

#endif //ENGINE7_IMGUISETUP_H
