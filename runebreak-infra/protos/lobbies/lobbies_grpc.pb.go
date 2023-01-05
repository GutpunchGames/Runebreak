// Code generated by protoc-gen-go-grpc. DO NOT EDIT.
// versions:
// - protoc-gen-go-grpc v1.2.0
// - protoc             v3.20.2
// source: lobbies.proto

package lobbies

import (
	context "context"
	grpc "google.golang.org/grpc"
	codes "google.golang.org/grpc/codes"
	status "google.golang.org/grpc/status"
)

// This is a compile-time assertion to ensure that this generated file
// is compatible with the grpc package it is being compiled against.
// Requires gRPC-Go v1.32.0 or later.
const _ = grpc.SupportPackageIsVersion7

// LobbiesClient is the client API for Lobbies service.
//
// For semantics around ctx use and closing/ending streaming RPCs, please refer to https://pkg.go.dev/google.golang.org/grpc/?tab=doc#ClientConn.NewStream.
type LobbiesClient interface {
	Create(ctx context.Context, in *CreateLobbyRequest, opts ...grpc.CallOption) (*Lobby, error)
	Join(ctx context.Context, in *JoinLobbyRequest, opts ...grpc.CallOption) (*Lobby, error)
	Leave(ctx context.Context, in *LeaveLobbyRequest, opts ...grpc.CallOption) (*LeaveLobbyResponse, error)
	GetLobby(ctx context.Context, in *GetLobbyRequest, opts ...grpc.CallOption) (*Lobby, error)
	GetAllLobbies(ctx context.Context, in *GetAllLobbiesRequest, opts ...grpc.CallOption) (*GetAllLobbiesResponse, error)
}

type lobbiesClient struct {
	cc grpc.ClientConnInterface
}

func NewLobbiesClient(cc grpc.ClientConnInterface) LobbiesClient {
	return &lobbiesClient{cc}
}

func (c *lobbiesClient) Create(ctx context.Context, in *CreateLobbyRequest, opts ...grpc.CallOption) (*Lobby, error) {
	out := new(Lobby)
	err := c.cc.Invoke(ctx, "/Lobbies/Create", in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *lobbiesClient) Join(ctx context.Context, in *JoinLobbyRequest, opts ...grpc.CallOption) (*Lobby, error) {
	out := new(Lobby)
	err := c.cc.Invoke(ctx, "/Lobbies/Join", in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *lobbiesClient) Leave(ctx context.Context, in *LeaveLobbyRequest, opts ...grpc.CallOption) (*LeaveLobbyResponse, error) {
	out := new(LeaveLobbyResponse)
	err := c.cc.Invoke(ctx, "/Lobbies/Leave", in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *lobbiesClient) GetLobby(ctx context.Context, in *GetLobbyRequest, opts ...grpc.CallOption) (*Lobby, error) {
	out := new(Lobby)
	err := c.cc.Invoke(ctx, "/Lobbies/GetLobby", in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *lobbiesClient) GetAllLobbies(ctx context.Context, in *GetAllLobbiesRequest, opts ...grpc.CallOption) (*GetAllLobbiesResponse, error) {
	out := new(GetAllLobbiesResponse)
	err := c.cc.Invoke(ctx, "/Lobbies/GetAllLobbies", in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

// LobbiesServer is the server API for Lobbies service.
// All implementations must embed UnimplementedLobbiesServer
// for forward compatibility
type LobbiesServer interface {
	Create(context.Context, *CreateLobbyRequest) (*Lobby, error)
	Join(context.Context, *JoinLobbyRequest) (*Lobby, error)
	Leave(context.Context, *LeaveLobbyRequest) (*LeaveLobbyResponse, error)
	GetLobby(context.Context, *GetLobbyRequest) (*Lobby, error)
	GetAllLobbies(context.Context, *GetAllLobbiesRequest) (*GetAllLobbiesResponse, error)
	mustEmbedUnimplementedLobbiesServer()
}

// UnimplementedLobbiesServer must be embedded to have forward compatible implementations.
type UnimplementedLobbiesServer struct {
}

func (UnimplementedLobbiesServer) Create(context.Context, *CreateLobbyRequest) (*Lobby, error) {
	return nil, status.Errorf(codes.Unimplemented, "method Create not implemented")
}
func (UnimplementedLobbiesServer) Join(context.Context, *JoinLobbyRequest) (*Lobby, error) {
	return nil, status.Errorf(codes.Unimplemented, "method Join not implemented")
}
func (UnimplementedLobbiesServer) Leave(context.Context, *LeaveLobbyRequest) (*LeaveLobbyResponse, error) {
	return nil, status.Errorf(codes.Unimplemented, "method Leave not implemented")
}
func (UnimplementedLobbiesServer) GetLobby(context.Context, *GetLobbyRequest) (*Lobby, error) {
	return nil, status.Errorf(codes.Unimplemented, "method GetLobby not implemented")
}
func (UnimplementedLobbiesServer) GetAllLobbies(context.Context, *GetAllLobbiesRequest) (*GetAllLobbiesResponse, error) {
	return nil, status.Errorf(codes.Unimplemented, "method GetAllLobbies not implemented")
}
func (UnimplementedLobbiesServer) mustEmbedUnimplementedLobbiesServer() {}

// UnsafeLobbiesServer may be embedded to opt out of forward compatibility for this service.
// Use of this interface is not recommended, as added methods to LobbiesServer will
// result in compilation errors.
type UnsafeLobbiesServer interface {
	mustEmbedUnimplementedLobbiesServer()
}

func RegisterLobbiesServer(s grpc.ServiceRegistrar, srv LobbiesServer) {
	s.RegisterService(&Lobbies_ServiceDesc, srv)
}

func _Lobbies_Create_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(CreateLobbyRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(LobbiesServer).Create(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: "/Lobbies/Create",
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(LobbiesServer).Create(ctx, req.(*CreateLobbyRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _Lobbies_Join_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(JoinLobbyRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(LobbiesServer).Join(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: "/Lobbies/Join",
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(LobbiesServer).Join(ctx, req.(*JoinLobbyRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _Lobbies_Leave_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(LeaveLobbyRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(LobbiesServer).Leave(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: "/Lobbies/Leave",
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(LobbiesServer).Leave(ctx, req.(*LeaveLobbyRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _Lobbies_GetLobby_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetLobbyRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(LobbiesServer).GetLobby(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: "/Lobbies/GetLobby",
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(LobbiesServer).GetLobby(ctx, req.(*GetLobbyRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _Lobbies_GetAllLobbies_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetAllLobbiesRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(LobbiesServer).GetAllLobbies(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: "/Lobbies/GetAllLobbies",
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(LobbiesServer).GetAllLobbies(ctx, req.(*GetAllLobbiesRequest))
	}
	return interceptor(ctx, in, info, handler)
}

// Lobbies_ServiceDesc is the grpc.ServiceDesc for Lobbies service.
// It's only intended for direct use with grpc.RegisterService,
// and not to be introspected or modified (even as a copy)
var Lobbies_ServiceDesc = grpc.ServiceDesc{
	ServiceName: "Lobbies",
	HandlerType: (*LobbiesServer)(nil),
	Methods: []grpc.MethodDesc{
		{
			MethodName: "Create",
			Handler:    _Lobbies_Create_Handler,
		},
		{
			MethodName: "Join",
			Handler:    _Lobbies_Join_Handler,
		},
		{
			MethodName: "Leave",
			Handler:    _Lobbies_Leave_Handler,
		},
		{
			MethodName: "GetLobby",
			Handler:    _Lobbies_GetLobby_Handler,
		},
		{
			MethodName: "GetAllLobbies",
			Handler:    _Lobbies_GetAllLobbies_Handler,
		},
	},
	Streams:  []grpc.StreamDesc{},
	Metadata: "lobbies.proto",
}
