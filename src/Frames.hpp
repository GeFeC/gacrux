#pragma once

#include "Frames/App.hpp"
#include "States/AppState.hpp"

enum class Frame{
  App
};

static auto current_frame = Frame::App;

const auto frame_manager = []{
  gx::Font::current = &gx::fonts::consolas;

  if (current_frame == Frame::App){
    app();
  }
};
