// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.28.1
// 	protoc        v3.20.2
// source: accounts.proto

package accounts

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type ExampleEnum int32

const (
	ExampleEnum_ZERO ExampleEnum = 0
	ExampleEnum_ONE  ExampleEnum = 1
)

// Enum value maps for ExampleEnum.
var (
	ExampleEnum_name = map[int32]string{
		0: "ZERO",
		1: "ONE",
	}
	ExampleEnum_value = map[string]int32{
		"ZERO": 0,
		"ONE":  1,
	}
)

func (x ExampleEnum) Enum() *ExampleEnum {
	p := new(ExampleEnum)
	*p = x
	return p
}

func (x ExampleEnum) String() string {
	return protoimpl.X.EnumStringOf(x.Descriptor(), protoreflect.EnumNumber(x))
}

func (ExampleEnum) Descriptor() protoreflect.EnumDescriptor {
	return file_accounts_proto_enumTypes[0].Descriptor()
}

func (ExampleEnum) Type() protoreflect.EnumType {
	return &file_accounts_proto_enumTypes[0]
}

func (x ExampleEnum) Number() protoreflect.EnumNumber {
	return protoreflect.EnumNumber(x)
}

// Deprecated: Use ExampleEnum.Descriptor instead.
func (ExampleEnum) EnumDescriptor() ([]byte, []int) {
	return file_accounts_proto_rawDescGZIP(), []int{0}
}

type ExampleRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	ParamOne ExampleEnum `protobuf:"varint,1,opt,name=ParamOne,proto3,enum=ExampleEnum" json:"ParamOne,omitempty"`
}

func (x *ExampleRequest) Reset() {
	*x = ExampleRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_accounts_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *ExampleRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*ExampleRequest) ProtoMessage() {}

func (x *ExampleRequest) ProtoReflect() protoreflect.Message {
	mi := &file_accounts_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use ExampleRequest.ProtoReflect.Descriptor instead.
func (*ExampleRequest) Descriptor() ([]byte, []int) {
	return file_accounts_proto_rawDescGZIP(), []int{0}
}

func (x *ExampleRequest) GetParamOne() ExampleEnum {
	if x != nil {
		return x.ParamOne
	}
	return ExampleEnum_ZERO
}

type ExampleResponse struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Rate float32 `protobuf:"fixed32,1,opt,name=Rate,proto3" json:"Rate,omitempty"`
}

func (x *ExampleResponse) Reset() {
	*x = ExampleResponse{}
	if protoimpl.UnsafeEnabled {
		mi := &file_accounts_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *ExampleResponse) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*ExampleResponse) ProtoMessage() {}

func (x *ExampleResponse) ProtoReflect() protoreflect.Message {
	mi := &file_accounts_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use ExampleResponse.ProtoReflect.Descriptor instead.
func (*ExampleResponse) Descriptor() ([]byte, []int) {
	return file_accounts_proto_rawDescGZIP(), []int{1}
}

func (x *ExampleResponse) GetRate() float32 {
	if x != nil {
		return x.Rate
	}
	return 0
}

var File_accounts_proto protoreflect.FileDescriptor

var file_accounts_proto_rawDesc = []byte{
	0x0a, 0x0e, 0x61, 0x63, 0x63, 0x6f, 0x75, 0x6e, 0x74, 0x73, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f,
	0x22, 0x3a, 0x0a, 0x0e, 0x45, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x52, 0x65, 0x71, 0x75, 0x65,
	0x73, 0x74, 0x12, 0x28, 0x0a, 0x08, 0x50, 0x61, 0x72, 0x61, 0x6d, 0x4f, 0x6e, 0x65, 0x18, 0x01,
	0x20, 0x01, 0x28, 0x0e, 0x32, 0x0c, 0x2e, 0x45, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x45, 0x6e,
	0x75, 0x6d, 0x52, 0x08, 0x50, 0x61, 0x72, 0x61, 0x6d, 0x4f, 0x6e, 0x65, 0x22, 0x25, 0x0a, 0x0f,
	0x45, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x12,
	0x12, 0x0a, 0x04, 0x52, 0x61, 0x74, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x02, 0x52, 0x04, 0x52,
	0x61, 0x74, 0x65, 0x2a, 0x20, 0x0a, 0x0b, 0x45, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x45, 0x6e,
	0x75, 0x6d, 0x12, 0x08, 0x0a, 0x04, 0x5a, 0x45, 0x52, 0x4f, 0x10, 0x00, 0x12, 0x07, 0x0a, 0x03,
	0x4f, 0x4e, 0x45, 0x10, 0x01, 0x32, 0x3b, 0x0a, 0x08, 0x41, 0x63, 0x63, 0x6f, 0x75, 0x6e, 0x74,
	0x73, 0x12, 0x2f, 0x0a, 0x0a, 0x47, 0x65, 0x74, 0x45, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x12,
	0x0f, 0x2e, 0x45, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
	0x1a, 0x10, 0x2e, 0x45, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e,
	0x73, 0x65, 0x42, 0x0b, 0x5a, 0x09, 0x2f, 0x61, 0x63, 0x63, 0x6f, 0x75, 0x6e, 0x74, 0x73, 0x62,
	0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_accounts_proto_rawDescOnce sync.Once
	file_accounts_proto_rawDescData = file_accounts_proto_rawDesc
)

func file_accounts_proto_rawDescGZIP() []byte {
	file_accounts_proto_rawDescOnce.Do(func() {
		file_accounts_proto_rawDescData = protoimpl.X.CompressGZIP(file_accounts_proto_rawDescData)
	})
	return file_accounts_proto_rawDescData
}

var file_accounts_proto_enumTypes = make([]protoimpl.EnumInfo, 1)
var file_accounts_proto_msgTypes = make([]protoimpl.MessageInfo, 2)
var file_accounts_proto_goTypes = []interface{}{
	(ExampleEnum)(0),        // 0: ExampleEnum
	(*ExampleRequest)(nil),  // 1: ExampleRequest
	(*ExampleResponse)(nil), // 2: ExampleResponse
}
var file_accounts_proto_depIdxs = []int32{
	0, // 0: ExampleRequest.ParamOne:type_name -> ExampleEnum
	1, // 1: Accounts.GetExample:input_type -> ExampleRequest
	2, // 2: Accounts.GetExample:output_type -> ExampleResponse
	2, // [2:3] is the sub-list for method output_type
	1, // [1:2] is the sub-list for method input_type
	1, // [1:1] is the sub-list for extension type_name
	1, // [1:1] is the sub-list for extension extendee
	0, // [0:1] is the sub-list for field type_name
}

func init() { file_accounts_proto_init() }
func file_accounts_proto_init() {
	if File_accounts_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_accounts_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*ExampleRequest); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_accounts_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*ExampleResponse); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_accounts_proto_rawDesc,
			NumEnums:      1,
			NumMessages:   2,
			NumExtensions: 0,
			NumServices:   1,
		},
		GoTypes:           file_accounts_proto_goTypes,
		DependencyIndexes: file_accounts_proto_depIdxs,
		EnumInfos:         file_accounts_proto_enumTypes,
		MessageInfos:      file_accounts_proto_msgTypes,
	}.Build()
	File_accounts_proto = out.File
	file_accounts_proto_rawDesc = nil
	file_accounts_proto_goTypes = nil
	file_accounts_proto_depIdxs = nil
}
