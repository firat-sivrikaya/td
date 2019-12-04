//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2019
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/utils/common.h"

#include <functional>
#include <type_traits>

namespace td {

class ScheduledServerMessageId {
  int32 id = 0;

 public:
  ScheduledServerMessageId() = default;

  explicit ScheduledServerMessageId(int32 message_id) : id(message_id) {
  }
  template <class T, typename = std::enable_if_t<std::is_convertible<T, int32>::value>>
  ScheduledServerMessageId(T message_id) = delete;

  bool is_valid() const {
    return id > 0 && id < (1 << 18);
  }

  int32 get() const {
    return id;
  }

  bool operator==(const ScheduledServerMessageId &other) const {
    return id == other.id;
  }

  bool operator!=(const ScheduledServerMessageId &other) const {
    return id != other.id;
  }

  template <class StorerT>
  void store(StorerT &storer) const {
    storer.store_int(id);
  }

  template <class ParserT>
  void parse(ParserT &parser) {
    id = parser.fetch_int();
  }
};

struct ScheduledServerMessageIdHash {
  std::size_t operator()(ScheduledServerMessageId message_id) const {
    return std::hash<int32>()(message_id.get());
  }
};

}  // namespace td