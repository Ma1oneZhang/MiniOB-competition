/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"

#include <json/value.h>

const static Json::StaticString INDEX_NAME("name");
const static Json::StaticString INDEX_FIELD_NAMES("field_names");

RC IndexMeta::init(const char *name, std::vector<const FieldMeta *> field)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  field_.clear();
  for (auto field : field) {
    field_.push_back(field->name());
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[INDEX_NAME] = name_;
  for (auto &name : field_) {
    json_value[INDEX_FIELD_NAMES].append(Json::Value(name));
  }
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value  = json_value[INDEX_NAME];
  const Json::Value &field_value = json_value[INDEX_FIELD_NAMES];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!field_value.isArray()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
        name_value.asCString(),
        field_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  std::vector<const FieldMeta *> fields;
  for (int i = 0; i < field_value.size(); i++) {
    if (!field_value[i].isString()) {
      LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
        field_value[i].asCString(),
        field_value.toStyledString().c_str());
      return RC::INTERNAL;
    }
    const FieldMeta *field = table.field(field_value[i].asCString());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.push_back(field);
  }

  return index.init(name_value.asCString(), fields);
}

const char *IndexMeta::name() const { return name_.c_str(); }

std::vector<std::string> const &IndexMeta::field() const { return field_; }

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=[";
  for (auto &name : field_) {
    os << name << ", ";
  }
  os << "];";
}