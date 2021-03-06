// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_LOCATIONMESSAGE_LOCATIONSTREAM_H_
#define FLATBUFFERS_GENERATED_LOCATIONMESSAGE_LOCATIONSTREAM_H_

#include "flatbuffers/flatbuffers.h"


namespace LocationStream {

struct Position;
struct PositionMessage;

MANUALLY_ALIGNED_STRUCT(8) Position FLATBUFFERS_FINAL_CLASS {
 private:
  double lon_;
  double lat_;

 public:
  Position(double lon, double lat)
    : lon_(flatbuffers::EndianScalar(lon)), lat_(flatbuffers::EndianScalar(lat)) { }

  double lon() const { return flatbuffers::EndianScalar(lon_); }
  double lat() const { return flatbuffers::EndianScalar(lat_); }
};
STRUCT_END(Position, 16);

struct PositionMessage FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const Position *pos() const { return GetStruct<const Position *>(4); }
  const flatbuffers::String *phone() const { return GetPointer<const flatbuffers::String *>(6); }
  int64_t timestamp() const { return GetField<int64_t>(8, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<Position>(verifier, 4 /* pos */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* phone */) &&
           verifier.Verify(phone()) &&
           VerifyField<int64_t>(verifier, 8 /* timestamp */) &&
           verifier.EndTable();
  }
};

struct PositionMessageBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_pos(const Position *pos) { fbb_.AddStruct(4, pos); }
  void add_phone(flatbuffers::Offset<flatbuffers::String> phone) { fbb_.AddOffset(6, phone); }
  void add_timestamp(int64_t timestamp) { fbb_.AddElement<int64_t>(8, timestamp, 0); }
  PositionMessageBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  PositionMessageBuilder &operator=(const PositionMessageBuilder &);
  flatbuffers::Offset<PositionMessage> Finish() {
    auto o = flatbuffers::Offset<PositionMessage>(fbb_.EndTable(start_, 3));
    return o;
  }
};

inline flatbuffers::Offset<PositionMessage> CreatePositionMessage(flatbuffers::FlatBufferBuilder &_fbb,
   const Position *pos = 0,
   flatbuffers::Offset<flatbuffers::String> phone = 0,
   int64_t timestamp = 0) {
  PositionMessageBuilder builder_(_fbb);
  builder_.add_timestamp(timestamp);
  builder_.add_phone(phone);
  builder_.add_pos(pos);
  return builder_.Finish();
}

inline const LocationStream::PositionMessage *GetPositionMessage(const void *buf) { return flatbuffers::GetRoot<LocationStream::PositionMessage>(buf); }

inline bool VerifyPositionMessageBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<LocationStream::PositionMessage>(); }

inline void FinishPositionMessageBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<LocationStream::PositionMessage> root) { fbb.Finish(root); }

}  // namespace LocationStream

#endif  // FLATBUFFERS_GENERATED_LOCATIONMESSAGE_LOCATIONSTREAM_H_
