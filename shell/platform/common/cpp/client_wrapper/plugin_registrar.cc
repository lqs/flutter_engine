// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "include/flutter/plugin_registrar.h"

#include <iostream>
#include <map>

#include "binary_messenger_impl.h"
#include "include/flutter/engine_method_result.h"
#include "include/flutter/method_channel.h"

namespace flutter {

// ===== PluginRegistrar =====

PluginRegistrar::PluginRegistrar(FlutterDesktopPluginRegistrarRef registrar)
    : registrar_(registrar) {
  auto core_messenger = FlutterDesktopPluginRegistrarGetMessenger(registrar_);
  messenger_ = std::make_unique<BinaryMessengerImpl>(core_messenger);
}

PluginRegistrar::~PluginRegistrar() {}

void PluginRegistrar::AddPlugin(std::unique_ptr<Plugin> plugin) {
  plugins_.insert(std::move(plugin));
}

// ===== PluginRegistrarManager =====

// static
PluginRegistrarManager* PluginRegistrarManager::GetInstance() {
  static PluginRegistrarManager* instance = new PluginRegistrarManager();
  return instance;
}

PluginRegistrarManager::PluginRegistrarManager() = default;

// static
void PluginRegistrarManager::OnRegistrarDestroyed(
    FlutterDesktopPluginRegistrarRef registrar) {
  GetInstance()->registrars()->erase(registrar);
}

}  // namespace flutter
