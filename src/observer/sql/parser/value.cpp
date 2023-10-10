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
// Created by WangYunlai on 2023/06/28.
//

#include <sstream>
#include <cmath>
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "dates", "floats", "booleans"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= FLOATS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/)
{
  if (!set_date(s)) {
    set_string(s, len);
  }
}

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_               = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_                 = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_                = length;
    } break;
    case DATES: {
      num_value_.date_value_ = *(int *)data;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_            = INTS;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_              = FLOATS;
  num_value_.float_value_ = val;
  length_                 = sizeof(val);
}
void Value::set_boolean(bool val)
{
  attr_type_             = BOOLEANS;
  num_value_.bool_value_ = val;
  length_                = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

bool check_date(int y, int m, int d)
{
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool       leap  = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

bool Value::set_date(const char *s)
{
  attr_type_ = DATES;
  int y, m, d;
  int result = sscanf(s, "%d-%d-%d", &y, &m, &d);

  if (result == 3) {  // matched successfully
    bool b = check_date(y, m, d);
    if (!b)
      return 0;
    int val                = y * 10000 + m * 100 + d;
    num_value_.date_value_ = val;
    length_                = sizeof(val);
    str_value_.assign("");
    return 1;
  } else {  // not a date, store as a string
    return 0;
  }
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case DATES: {
      // do nothing
      // for reduce the compiler warning
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case DATES: {
      int  y = num_value_.date_value_ / 10000;
      int  m = (num_value_.date_value_ % 10000) / 100;
      int  d = num_value_.date_value_ % 100;
      char date_str[12];
      sprintf(date_str, "%04d-%02d-%02d", y, m, d);
      os << date_str;
    }
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case DATES:
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
    float this_data = this->num_value_.int_value_;
    const char *c_str = other.data();
    float       other_data = 0, digit_val_ = 0;
    int         integer_val = 0, digit_val = 0;
    int         prefixNum = returnPrefixNum(c_str, integer_val);
    if (prefixNum > 0 && c_str[prefixNum] == '.') {
      returnPrefixNum(c_str + prefixNum + 1, digit_val);
      digit_val_ = digit_val;
      while (digit_val_ >= 1) {
        digit_val_ /= 10;
      }
    }
    other_data = integer_val + digit_val_;
    return common::compare_float((void *)&this_data, (void *)&other_data);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    const char *c_str = other.data();
    float       other_data = 0, digit_val_ = 0;
    int         integer_val = 0, digit_val = 0;
    int         prefixNum = returnPrefixNum(c_str, integer_val);
    if (prefixNum > 0 && c_str[prefixNum] == '.') {
      returnPrefixNum(c_str + prefixNum + 1, digit_val);
      digit_val_ = digit_val;
      while (digit_val_ >= 1) {
        digit_val_ /= 10;
      }
    }
    other_data = integer_val + digit_val_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
    const char *c_str = this->data();
    float       this_data = 0, digit_val_ = 0;
    int         integer_val = 0, digit_val = 0;
    int         prefixNum = returnPrefixNum(c_str, integer_val);
    if (prefixNum > 0 && c_str[prefixNum] == '.') {
      returnPrefixNum(c_str + prefixNum + 1, digit_val);
      digit_val_ = digit_val;
      while (digit_val_ >= 1) {
        digit_val_ /= 10;
      }
    }
    this_data = integer_val + digit_val_;
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void*)&this_data, (void *)&other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    const char *c_str = this->data();
    float       this_data = 0, digit_val_ = 0;
    int         integer_val = 0, digit_val = 0;
    int         prefixNum = returnPrefixNum(c_str, integer_val);
    if (prefixNum > 0 && c_str[prefixNum] == '.') {
      returnPrefixNum(c_str + prefixNum + 1, digit_val);
      digit_val_ = digit_val;
      while (digit_val_ >= 1) {
        digit_val_ /= 10;
      }
    }
    this_data = integer_val + digit_val_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  }
  
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

int Value::get_int() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

int returnPrefixNum(const char *str, int &val)
{
  if (str == NULL || *str == '\0') {
    // Handle empty string or NULL pointer as needed.
    return 0;  // Not a number.
  }

  // Iterate through characters in the string until a non-digit character is found.
  int prefixNum = 0;
  val           = 0;
  while (*str != '\0') {
    if (!isdigit(*str)) {
      // If a non-digit character is encountered, it's not a number.
      break;
    }
    val = val * 10 + (*str - '0');
    str++;  // Move to the next character.
    prefixNum++;
  }

  return prefixNum;
}

bool Value::match_field_type(AttrType field_type)
{
  // the field type and attribute type are the same
  if (attr_type_ == field_type) {
    return true;
  }

  /*
   * the two types are not the same, then attempt to
   * convert attr to the type of field
   */
  switch (field_type) {
    case AttrType::CHARS:
      switch (attr_type_) {
        // int to string
        case AttrType::INTS: {
          char val[20];
          sprintf(val, "%d", get_int());
          set_string(val);
          break;
        }
        // float to string
        case AttrType::FLOATS: {
          int char_len = 1;
          float float_val = get_float();
          int integer_part = (int)float_val;
          float fraction_part = float_val - integer_part;
          while(integer_part>=1){
            integer_part /= 10;
            char_len ++;
          }
          while(fraction_part!=0){
            fraction_part *= 10;
            fraction_part = fraction_part - (int)fraction_part;
            char_len++;
          }
          char val[char_len];
          sprintf(val, "%f", float_val);
          set_string(val,char_len);
          break;
        }
      }
      /* code */
      break;
    case AttrType::INTS: {
      switch (attr_type_) {
        // string to int
        case AttrType::CHARS: {
          int val = 0;
          returnPrefixNum(data(), val);
          set_int(val);
          break;
        }
        // float to int
        case AttrType::FLOATS: set_int((int)round(get_float())); break;
      }
      break;
    }
    case AttrType::FLOATS:
      switch (attr_type_) {
        // string to floats
        case AttrType::CHARS: {
          const char *c_str = data();
          float       val = 0, digit_val_ = 0;
          int         integer_val = 0, digit_val = 0;
          int         prefixNum = returnPrefixNum(c_str, integer_val);
          if (prefixNum > 0 && c_str[prefixNum] == '.') {
            returnPrefixNum(c_str + prefixNum + 1, digit_val);
            digit_val_ = digit_val;
            while (digit_val_ >= 1) {
              digit_val_ /= 10;
            }
          }
          val = integer_val + digit_val_;
          set_float(val);
          break;
        }
        case AttrType::INTS: set_float((float)get_int()); break;
      }
      break;
    default:
      // the coversion failed
      return false;
      break;
  }

  // the conversion successed
  return true;
}