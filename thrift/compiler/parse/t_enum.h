/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef T_ENUM_H
#define T_ENUM_H

#include "thrift/compiler/parse/t_enum_value.h"
#include <folly/Optional.h>
#include <vector>

/**
 * An enumerated type. A list of constant objects with a name for the type.
 *
 */
class t_enum : public t_type {
 public:
  explicit t_enum(t_program* program) :
    t_type(program) {}

  void set_name(const std::string& name) override { name_ = name; }

  void append(t_enum_value* constant) {
    constants_.push_back(constant);
  }

  const std::vector<t_enum_value*>& get_constants() {
    return constants_;
  }

  const t_enum_value* find_value(const int32_t enum_value) {
    for (const auto it : constants_) {
      if (it->get_value() == enum_value) {
        return it;
      }
    }
    return nullptr;
  }

  const folly::Optional<int32_t> find_int_val(const std::string& name) {
    for (const auto it : constants_) {
      if (it->get_name() == name) {
        return it->get_value();
      }
    }
    return folly::none;
  }

  bool is_enum() const override { return true; }

  std::string get_full_name() const override { return make_full_name("enum"); }

  std::string get_impl_full_name() const override {
    return make_full_name("enum");
  }

  TypeValue get_type_value() const override { return t_types::TYPE_ENUM; }

 private:
  std::vector<t_enum_value*> constants_;
};

#endif
