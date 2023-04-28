#include "editor_window.h"
#include <string>
namespace SPG
{
    EditorWidnow::EditorWidnow()
    {
        _editorFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
        _scriptBuffer = new char[SCRIPT_BUFFER_SIZE];
        memset(_scriptBuffer, 0, SCRIPT_BUFFER_SIZE * sizeof(char));
    }

    EditorWidnow::~EditorWidnow()
    {
        delete _scriptBuffer;
    }
    void EditorWidnow::Show()
    {
        ImGui::Begin("Editor");
        {
            size = ImGui::GetContentRegionAvail();
            ImGui::InputTextMultiline("edit", _scriptBuffer, SCRIPT_BUFFER_SIZE, size, ImGuiInputTextFlags_AllowTabInput);
        }
        ImGui::End();
    }
    
    char* EditorWidnow::GetScriptBuffer()
    {
        return _scriptBuffer;
    }
    
    void EditorWidnow::SetScriptBuffer(void* data, size_t size)
    {
        memset(_scriptBuffer, 0, SCRIPT_BUFFER_SIZE * sizeof(char));
        strcpy(_scriptBuffer, (char*)data);
    }
}