// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_CONTEXT_MEASURE_H_
#define V8_CONTEXT_MEASURE_H_

#include "src/snapshot/serialize.h"

namespace v8 {
namespace internal {

class ContextMeasure : public ObjectVisitor {
 public:
  explicit ContextMeasure(Context* context);

  int Size() { return size_; }
  int Count() { return count_; }

  void VisitPointers(Object** start, Object** end);

 private:
  void MeasureObject(HeapObject* object);
  void MeasureDeferredObjects();
  void MeasureAndRecurse(HeapObject* object);
  bool IsShared(HeapObject* object);

  Context* context_;

  BackReferenceMap back_reference_map_;
  RootIndexMap root_index_map_;

  static const int kMaxRecursion = 16;
  int recursion_depth_;
  List<HeapObject*> deferred_objects_;

  int count_;
  int size_;

  DisallowHeapAllocation no_gc_;

  DISALLOW_COPY_AND_ASSIGN(ContextMeasure);
};
}
}  // namespace v8::internal

#endif  // V8_CONTEXT_MEASURE_H_
