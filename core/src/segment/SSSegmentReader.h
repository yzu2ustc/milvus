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

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "codecs/Codec.h"
#include "db/SnapshotVisitor.h"
#include "segment/Segment.h"
#include "storage/FSHandler.h"
#include "utils/Status.h"

namespace milvus {
namespace segment {

class SSSegmentReader {
 public:
    explicit SSSegmentReader(const std::string& dir_root, const engine::SegmentVisitorPtr& segment_visitor);

    Status
    Load();

    Status
    LoadField(const std::string& field_name, std::vector<uint8_t>& raw);

    Status
    LoadFields();

    Status
    LoadEntities(const std::string& field_name, const std::vector<int64_t>& offsets, std::vector<uint8_t>& raw);

    Status
    LoadFieldsEntities(const std::vector<std::string>& fields_name, const std::vector<int64_t>& offsets,
                       engine::DataChunkPtr& data_chunk);

    Status
    LoadUids(std::vector<int64_t>& uids);

    Status
    LoadVectorIndex(const std::string& field_name, segment::VectorIndexPtr& vector_index_ptr);

    Status
    LoadVectorIndice();

    Status
    LoadBloomFilter(segment::IdBloomFilterPtr& id_bloom_filter_ptr);

    Status
    LoadBloomFilter();

    Status
    LoadDeletedDocs(segment::DeletedDocsPtr& deleted_docs_ptr);

    Status
    LoadDeletedDocs();

    Status
    ReadDeletedDocsSize(size_t& size);

    Status
    GetSegment(engine::SegmentPtr& segment_ptr);

    Status
    GetSegmentID(int64_t& id);

    std::string
    GetSegmentPath();

 private:
    Status
    Initialize();

 private:
    engine::SegmentVisitorPtr segment_visitor_;
    storage::FSHandlerPtr fs_ptr_;
    engine::SegmentPtr segment_ptr_;
    std::string dir_root_;
};

using SSSegmentReaderPtr = std::shared_ptr<SSSegmentReader>;

}  // namespace segment
}  // namespace milvus
