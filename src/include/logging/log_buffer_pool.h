//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// log_buffer_pool.h
//
// Identification: src/logging/log_buffer_pool.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <vector>

#include "type/types.h"
#include "common/macros.h"
#include "common/platform.h"

#include "logging/log_buffer.h"

namespace peloton {
namespace logging {
  class LogBufferPool {
    LogBufferPool(const LogBufferPool &) = delete;
    LogBufferPool &operator=(const LogBufferPool &) = delete;
    LogBufferPool(const LogBufferPool &&) = delete;
    LogBufferPool &operator=(const LogBufferPool &&) = delete;

  public:
    LogBufferPool(const size_t worker_id) : 
      head_(0), 
      tail_(buffer_queue_size_),
      worker_id_(worker_id),
      local_buffer_queue_(buffer_queue_size_) {}

    std::unique_ptr<LogBuffer> GetBuffer(size_t current_eid);

    void PutBuffer(std::unique_ptr<LogBuffer> buf);

    inline size_t GetWorkerId() { return worker_id_; }


  private:
    static const size_t buffer_queue_size_ = 16;
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;
    
    size_t worker_id_;

    std::vector<std::unique_ptr<LogBuffer>> local_buffer_queue_;
};

}
}