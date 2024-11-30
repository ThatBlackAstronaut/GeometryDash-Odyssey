#pragma once

using namespace geode::prelude;

namespace Odyssey {
    DialogLayer * createDialog(const char* event);
    DialogLayer * createDialogResponse(const char * event, int times);
};