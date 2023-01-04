// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.28.1
// 	protoc        v3.20.2
// source: lobbies.proto

package lobbies

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

// types
type Lobby struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	LobbyId   string  `protobuf:"bytes,1,opt,name=lobby_id,json=lobbyId,proto3" json:"lobby_id,omitempty"`
	LobbyName string  `protobuf:"bytes,2,opt,name=lobby_name,json=lobbyName,proto3" json:"lobby_name,omitempty"`
	OwnerId   string  `protobuf:"bytes,3,opt,name=owner_id,json=ownerId,proto3" json:"owner_id,omitempty"`
	Users     []*User `protobuf:"bytes,4,rep,name=users,proto3" json:"users,omitempty"`
}

func (x *Lobby) Reset() {
	*x = Lobby{}
	if protoimpl.UnsafeEnabled {
		mi := &file_lobbies_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *Lobby) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*Lobby) ProtoMessage() {}

func (x *Lobby) ProtoReflect() protoreflect.Message {
	mi := &file_lobbies_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use Lobby.ProtoReflect.Descriptor instead.
func (*Lobby) Descriptor() ([]byte, []int) {
	return file_lobbies_proto_rawDescGZIP(), []int{0}
}

func (x *Lobby) GetLobbyId() string {
	if x != nil {
		return x.LobbyId
	}
	return ""
}

func (x *Lobby) GetLobbyName() string {
	if x != nil {
		return x.LobbyName
	}
	return ""
}

func (x *Lobby) GetOwnerId() string {
	if x != nil {
		return x.OwnerId
	}
	return ""
}

func (x *Lobby) GetUsers() []*User {
	if x != nil {
		return x.Users
	}
	return nil
}

type User struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	UserId   string `protobuf:"bytes,1,opt,name=user_id,json=userId,proto3" json:"user_id,omitempty"`
	UserName string `protobuf:"bytes,2,opt,name=user_name,json=userName,proto3" json:"user_name,omitempty"`
}

func (x *User) Reset() {
	*x = User{}
	if protoimpl.UnsafeEnabled {
		mi := &file_lobbies_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *User) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*User) ProtoMessage() {}

func (x *User) ProtoReflect() protoreflect.Message {
	mi := &file_lobbies_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use User.ProtoReflect.Descriptor instead.
func (*User) Descriptor() ([]byte, []int) {
	return file_lobbies_proto_rawDescGZIP(), []int{1}
}

func (x *User) GetUserId() string {
	if x != nil {
		return x.UserId
	}
	return ""
}

func (x *User) GetUserName() string {
	if x != nil {
		return x.UserName
	}
	return ""
}

// requests/responses
type CreateLobbyRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	UserId    string `protobuf:"bytes,1,opt,name=user_id,json=userId,proto3" json:"user_id,omitempty"`
	LobbyName string `protobuf:"bytes,2,opt,name=lobby_name,json=lobbyName,proto3" json:"lobby_name,omitempty"`
}

func (x *CreateLobbyRequest) Reset() {
	*x = CreateLobbyRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_lobbies_proto_msgTypes[2]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *CreateLobbyRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*CreateLobbyRequest) ProtoMessage() {}

func (x *CreateLobbyRequest) ProtoReflect() protoreflect.Message {
	mi := &file_lobbies_proto_msgTypes[2]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use CreateLobbyRequest.ProtoReflect.Descriptor instead.
func (*CreateLobbyRequest) Descriptor() ([]byte, []int) {
	return file_lobbies_proto_rawDescGZIP(), []int{2}
}

func (x *CreateLobbyRequest) GetUserId() string {
	if x != nil {
		return x.UserId
	}
	return ""
}

func (x *CreateLobbyRequest) GetLobbyName() string {
	if x != nil {
		return x.LobbyName
	}
	return ""
}

type JoinLobbyRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	UserId  string `protobuf:"bytes,1,opt,name=user_id,json=userId,proto3" json:"user_id,omitempty"`
	LobbyId string `protobuf:"bytes,2,opt,name=lobby_id,json=lobbyId,proto3" json:"lobby_id,omitempty"`
}

func (x *JoinLobbyRequest) Reset() {
	*x = JoinLobbyRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_lobbies_proto_msgTypes[3]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *JoinLobbyRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*JoinLobbyRequest) ProtoMessage() {}

func (x *JoinLobbyRequest) ProtoReflect() protoreflect.Message {
	mi := &file_lobbies_proto_msgTypes[3]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use JoinLobbyRequest.ProtoReflect.Descriptor instead.
func (*JoinLobbyRequest) Descriptor() ([]byte, []int) {
	return file_lobbies_proto_rawDescGZIP(), []int{3}
}

func (x *JoinLobbyRequest) GetUserId() string {
	if x != nil {
		return x.UserId
	}
	return ""
}

func (x *JoinLobbyRequest) GetLobbyId() string {
	if x != nil {
		return x.LobbyId
	}
	return ""
}

type GetLobbyRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	LobbyId string `protobuf:"bytes,1,opt,name=lobby_id,json=lobbyId,proto3" json:"lobby_id,omitempty"`
}

func (x *GetLobbyRequest) Reset() {
	*x = GetLobbyRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_lobbies_proto_msgTypes[4]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *GetLobbyRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*GetLobbyRequest) ProtoMessage() {}

func (x *GetLobbyRequest) ProtoReflect() protoreflect.Message {
	mi := &file_lobbies_proto_msgTypes[4]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use GetLobbyRequest.ProtoReflect.Descriptor instead.
func (*GetLobbyRequest) Descriptor() ([]byte, []int) {
	return file_lobbies_proto_rawDescGZIP(), []int{4}
}

func (x *GetLobbyRequest) GetLobbyId() string {
	if x != nil {
		return x.LobbyId
	}
	return ""
}

type GetAllLobbiesRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields
}

func (x *GetAllLobbiesRequest) Reset() {
	*x = GetAllLobbiesRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_lobbies_proto_msgTypes[5]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *GetAllLobbiesRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*GetAllLobbiesRequest) ProtoMessage() {}

func (x *GetAllLobbiesRequest) ProtoReflect() protoreflect.Message {
	mi := &file_lobbies_proto_msgTypes[5]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use GetAllLobbiesRequest.ProtoReflect.Descriptor instead.
func (*GetAllLobbiesRequest) Descriptor() ([]byte, []int) {
	return file_lobbies_proto_rawDescGZIP(), []int{5}
}

type GetAllLobbiesResponse struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Lobbies []*Lobby `protobuf:"bytes,1,rep,name=lobbies,proto3" json:"lobbies,omitempty"`
}

func (x *GetAllLobbiesResponse) Reset() {
	*x = GetAllLobbiesResponse{}
	if protoimpl.UnsafeEnabled {
		mi := &file_lobbies_proto_msgTypes[6]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *GetAllLobbiesResponse) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*GetAllLobbiesResponse) ProtoMessage() {}

func (x *GetAllLobbiesResponse) ProtoReflect() protoreflect.Message {
	mi := &file_lobbies_proto_msgTypes[6]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use GetAllLobbiesResponse.ProtoReflect.Descriptor instead.
func (*GetAllLobbiesResponse) Descriptor() ([]byte, []int) {
	return file_lobbies_proto_rawDescGZIP(), []int{6}
}

func (x *GetAllLobbiesResponse) GetLobbies() []*Lobby {
	if x != nil {
		return x.Lobbies
	}
	return nil
}

var File_lobbies_proto protoreflect.FileDescriptor

var file_lobbies_proto_rawDesc = []byte{
	0x0a, 0x0d, 0x6c, 0x6f, 0x62, 0x62, 0x69, 0x65, 0x73, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x22,
	0x79, 0x0a, 0x05, 0x4c, 0x6f, 0x62, 0x62, 0x79, 0x12, 0x19, 0x0a, 0x08, 0x6c, 0x6f, 0x62, 0x62,
	0x79, 0x5f, 0x69, 0x64, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x07, 0x6c, 0x6f, 0x62, 0x62,
	0x79, 0x49, 0x64, 0x12, 0x1d, 0x0a, 0x0a, 0x6c, 0x6f, 0x62, 0x62, 0x79, 0x5f, 0x6e, 0x61, 0x6d,
	0x65, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x09, 0x6c, 0x6f, 0x62, 0x62, 0x79, 0x4e, 0x61,
	0x6d, 0x65, 0x12, 0x19, 0x0a, 0x08, 0x6f, 0x77, 0x6e, 0x65, 0x72, 0x5f, 0x69, 0x64, 0x18, 0x03,
	0x20, 0x01, 0x28, 0x09, 0x52, 0x07, 0x6f, 0x77, 0x6e, 0x65, 0x72, 0x49, 0x64, 0x12, 0x1b, 0x0a,
	0x05, 0x75, 0x73, 0x65, 0x72, 0x73, 0x18, 0x04, 0x20, 0x03, 0x28, 0x0b, 0x32, 0x05, 0x2e, 0x55,
	0x73, 0x65, 0x72, 0x52, 0x05, 0x75, 0x73, 0x65, 0x72, 0x73, 0x22, 0x3c, 0x0a, 0x04, 0x55, 0x73,
	0x65, 0x72, 0x12, 0x17, 0x0a, 0x07, 0x75, 0x73, 0x65, 0x72, 0x5f, 0x69, 0x64, 0x18, 0x01, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x06, 0x75, 0x73, 0x65, 0x72, 0x49, 0x64, 0x12, 0x1b, 0x0a, 0x09, 0x75,
	0x73, 0x65, 0x72, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x08,
	0x75, 0x73, 0x65, 0x72, 0x4e, 0x61, 0x6d, 0x65, 0x22, 0x4c, 0x0a, 0x12, 0x43, 0x72, 0x65, 0x61,
	0x74, 0x65, 0x4c, 0x6f, 0x62, 0x62, 0x79, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x12, 0x17,
	0x0a, 0x07, 0x75, 0x73, 0x65, 0x72, 0x5f, 0x69, 0x64, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52,
	0x06, 0x75, 0x73, 0x65, 0x72, 0x49, 0x64, 0x12, 0x1d, 0x0a, 0x0a, 0x6c, 0x6f, 0x62, 0x62, 0x79,
	0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x09, 0x6c, 0x6f, 0x62,
	0x62, 0x79, 0x4e, 0x61, 0x6d, 0x65, 0x22, 0x46, 0x0a, 0x10, 0x4a, 0x6f, 0x69, 0x6e, 0x4c, 0x6f,
	0x62, 0x62, 0x79, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x12, 0x17, 0x0a, 0x07, 0x75, 0x73,
	0x65, 0x72, 0x5f, 0x69, 0x64, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x06, 0x75, 0x73, 0x65,
	0x72, 0x49, 0x64, 0x12, 0x19, 0x0a, 0x08, 0x6c, 0x6f, 0x62, 0x62, 0x79, 0x5f, 0x69, 0x64, 0x18,
	0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x07, 0x6c, 0x6f, 0x62, 0x62, 0x79, 0x49, 0x64, 0x22, 0x2c,
	0x0a, 0x0f, 0x47, 0x65, 0x74, 0x4c, 0x6f, 0x62, 0x62, 0x79, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73,
	0x74, 0x12, 0x19, 0x0a, 0x08, 0x6c, 0x6f, 0x62, 0x62, 0x79, 0x5f, 0x69, 0x64, 0x18, 0x01, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x07, 0x6c, 0x6f, 0x62, 0x62, 0x79, 0x49, 0x64, 0x22, 0x16, 0x0a, 0x14,
	0x47, 0x65, 0x74, 0x41, 0x6c, 0x6c, 0x4c, 0x6f, 0x62, 0x62, 0x69, 0x65, 0x73, 0x52, 0x65, 0x71,
	0x75, 0x65, 0x73, 0x74, 0x22, 0x39, 0x0a, 0x15, 0x47, 0x65, 0x74, 0x41, 0x6c, 0x6c, 0x4c, 0x6f,
	0x62, 0x62, 0x69, 0x65, 0x73, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x12, 0x20, 0x0a,
	0x07, 0x6c, 0x6f, 0x62, 0x62, 0x69, 0x65, 0x73, 0x18, 0x01, 0x20, 0x03, 0x28, 0x0b, 0x32, 0x06,
	0x2e, 0x4c, 0x6f, 0x62, 0x62, 0x79, 0x52, 0x07, 0x6c, 0x6f, 0x62, 0x62, 0x69, 0x65, 0x73, 0x32,
	0xb9, 0x01, 0x0a, 0x07, 0x4c, 0x6f, 0x62, 0x62, 0x69, 0x65, 0x73, 0x12, 0x25, 0x0a, 0x06, 0x43,
	0x72, 0x65, 0x61, 0x74, 0x65, 0x12, 0x13, 0x2e, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x4c, 0x6f,
	0x62, 0x62, 0x79, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x1a, 0x06, 0x2e, 0x4c, 0x6f, 0x62,
	0x62, 0x79, 0x12, 0x21, 0x0a, 0x04, 0x4a, 0x6f, 0x69, 0x6e, 0x12, 0x11, 0x2e, 0x4a, 0x6f, 0x69,
	0x6e, 0x4c, 0x6f, 0x62, 0x62, 0x79, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x1a, 0x06, 0x2e,
	0x4c, 0x6f, 0x62, 0x62, 0x79, 0x12, 0x24, 0x0a, 0x08, 0x47, 0x65, 0x74, 0x4c, 0x6f, 0x62, 0x62,
	0x79, 0x12, 0x10, 0x2e, 0x47, 0x65, 0x74, 0x4c, 0x6f, 0x62, 0x62, 0x79, 0x52, 0x65, 0x71, 0x75,
	0x65, 0x73, 0x74, 0x1a, 0x06, 0x2e, 0x4c, 0x6f, 0x62, 0x62, 0x79, 0x12, 0x3e, 0x0a, 0x0d, 0x47,
	0x65, 0x74, 0x41, 0x6c, 0x6c, 0x4c, 0x6f, 0x62, 0x62, 0x69, 0x65, 0x73, 0x12, 0x15, 0x2e, 0x47,
	0x65, 0x74, 0x41, 0x6c, 0x6c, 0x4c, 0x6f, 0x62, 0x62, 0x69, 0x65, 0x73, 0x52, 0x65, 0x71, 0x75,
	0x65, 0x73, 0x74, 0x1a, 0x16, 0x2e, 0x47, 0x65, 0x74, 0x41, 0x6c, 0x6c, 0x4c, 0x6f, 0x62, 0x62,
	0x69, 0x65, 0x73, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x42, 0x0a, 0x5a, 0x08, 0x2f,
	0x6c, 0x6f, 0x62, 0x62, 0x69, 0x65, 0x73, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_lobbies_proto_rawDescOnce sync.Once
	file_lobbies_proto_rawDescData = file_lobbies_proto_rawDesc
)

func file_lobbies_proto_rawDescGZIP() []byte {
	file_lobbies_proto_rawDescOnce.Do(func() {
		file_lobbies_proto_rawDescData = protoimpl.X.CompressGZIP(file_lobbies_proto_rawDescData)
	})
	return file_lobbies_proto_rawDescData
}

var file_lobbies_proto_msgTypes = make([]protoimpl.MessageInfo, 7)
var file_lobbies_proto_goTypes = []interface{}{
	(*Lobby)(nil),                 // 0: Lobby
	(*User)(nil),                  // 1: User
	(*CreateLobbyRequest)(nil),    // 2: CreateLobbyRequest
	(*JoinLobbyRequest)(nil),      // 3: JoinLobbyRequest
	(*GetLobbyRequest)(nil),       // 4: GetLobbyRequest
	(*GetAllLobbiesRequest)(nil),  // 5: GetAllLobbiesRequest
	(*GetAllLobbiesResponse)(nil), // 6: GetAllLobbiesResponse
}
var file_lobbies_proto_depIdxs = []int32{
	1, // 0: Lobby.users:type_name -> User
	0, // 1: GetAllLobbiesResponse.lobbies:type_name -> Lobby
	2, // 2: Lobbies.Create:input_type -> CreateLobbyRequest
	3, // 3: Lobbies.Join:input_type -> JoinLobbyRequest
	4, // 4: Lobbies.GetLobby:input_type -> GetLobbyRequest
	5, // 5: Lobbies.GetAllLobbies:input_type -> GetAllLobbiesRequest
	0, // 6: Lobbies.Create:output_type -> Lobby
	0, // 7: Lobbies.Join:output_type -> Lobby
	0, // 8: Lobbies.GetLobby:output_type -> Lobby
	6, // 9: Lobbies.GetAllLobbies:output_type -> GetAllLobbiesResponse
	6, // [6:10] is the sub-list for method output_type
	2, // [2:6] is the sub-list for method input_type
	2, // [2:2] is the sub-list for extension type_name
	2, // [2:2] is the sub-list for extension extendee
	0, // [0:2] is the sub-list for field type_name
}

func init() { file_lobbies_proto_init() }
func file_lobbies_proto_init() {
	if File_lobbies_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_lobbies_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*Lobby); i {
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
		file_lobbies_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*User); i {
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
		file_lobbies_proto_msgTypes[2].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*CreateLobbyRequest); i {
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
		file_lobbies_proto_msgTypes[3].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*JoinLobbyRequest); i {
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
		file_lobbies_proto_msgTypes[4].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*GetLobbyRequest); i {
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
		file_lobbies_proto_msgTypes[5].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*GetAllLobbiesRequest); i {
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
		file_lobbies_proto_msgTypes[6].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*GetAllLobbiesResponse); i {
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
			RawDescriptor: file_lobbies_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   7,
			NumExtensions: 0,
			NumServices:   1,
		},
		GoTypes:           file_lobbies_proto_goTypes,
		DependencyIndexes: file_lobbies_proto_depIdxs,
		MessageInfos:      file_lobbies_proto_msgTypes,
	}.Build()
	File_lobbies_proto = out.File
	file_lobbies_proto_rawDesc = nil
	file_lobbies_proto_goTypes = nil
	file_lobbies_proto_depIdxs = nil
}
