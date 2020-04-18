// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "core.hpp"

// Apache Arrow
#include <arrow/api.h>

#include <arrow/ipc/api.h>
#include <arrow-glib/arrow-glib.h>

#include <arrow-glib/buffer.hpp>
#include <arrow-glib/record-batch.hpp>

using namespace arrow;
using namespace std;


extern "C" GArrowBuffer * 
GSerializeRecordBatchToBuffer(GArrowRecordBatch *record_batch)
{
  const auto arrow_record_batch = garrow_record_batch_get_raw(record_batch);

  std::shared_ptr<arrow::ResizableBuffer> resizable_buffer;
  arrow::AllocateResizableBuffer(arrow::default_memory_pool(), 0, &resizable_buffer);

  std::shared_ptr<arrow::Buffer> buffer = std::dynamic_pointer_cast<arrow::Buffer>(resizable_buffer);
  arrow::ipc::SerializeRecordBatch(*arrow_record_batch, arrow::default_memory_pool(), &buffer);

  return garrow_buffer_new_raw(&buffer);

}


/*
//Main program
int main(int argc, char** argv) {

  return 0;
}*/

