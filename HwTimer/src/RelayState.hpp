#pragma once

enum class RelayState
{
  Off,
  On
};

const char *stateToString(RelayState s)
{
  switch (s)
  {
  case RelayState::Off:
    return "Off";
  case RelayState::On:
    return "On";
  }
  return "???";
}