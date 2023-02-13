//
// Created by Michael Ferents on 21/03/2022.
//

#include "Program.h"

using namespace Wuu;

void Program::run()
{
    window.initialize();

    auto ctx = window.create_context();

    while(window.is_running())
    {
        window.poll_events();

        ctx->Button();
        ctx->Image();
        ctx->Text();

        ctx->render(window.getGLFWWindow());

        ctx->update_input();
        ctx->reset_input();
    }
}

void Program::destroy()
{
    window.destroy();
}